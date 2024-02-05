#include<stdio.h>
#include<string.h>
#include "DRF0554.h"



#define LCD_ADDRESS     (0x7c>>1)
#define RGB_ADDRESS     (0xc0>>1)

/*!
 *  @brief color define
 */ 
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

/*!
 *  @brief commands
 */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

/*!
 *  @brief flags for display entry mode
 */
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/*!
 *  @brief flags for display on/off control
 */
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

/*!
 *  @brief flags for display/cursor shift
 */
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

/*!
 *  @brief flags for function set
 */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

uint8_t _showFunction;
uint8_t _showControl;
uint8_t _showMode;
uint8_t _initialized;
uint8_t _numLines,_currLine;
uint8_t _lcdAddr = LCD_ADDRESS;
uint8_t _RGBAddr= RGB_ADDRESS;
uint8_t _cols = 16;
uint8_t _rows = 2;



void send(uint8_t *data, uint8_t len){
    Cy_SCB_I2C_MasterSendStart(I2C_HW,_lcdAddr,CY_SCB_I2C_WRITE_XFER,0,&I2C_context);
    for (int i = 0; i < len; i++) {
        Cy_SCB_I2C_MasterWriteByte(I2C_HW,data[i],0,&I2C_context);
        CyDelay(5);
    }
    Cy_SCB_I2C_MasterSendStop(I2C_HW,0,&I2C_context);  
}

void command(uint8_t value){
    uint8_t data[3] = {0x80, value};
    send(data, 2);
}

void setReg(uint8_t addr, uint8_t data){
    Cy_SCB_I2C_MasterSendStart(I2C_HW,_RGBAddr,CY_SCB_I2C_WRITE_XFER,0,&I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW,addr,0,&I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW,data,0,&I2C_context);
    Cy_SCB_I2C_MasterSendStop(I2C_HW,0,&I2C_context);  
}

void write(uint8_t value){

    uint8_t data[3] = {0x40, value};
    send(data, 2);
}


// Connects PSoC 6 I2C MASTER with associated CONTEXT to a connected DRF0554 
// 16x2 backlight RGB LCD. Text direction will be fixed left-to-right. 
// Initial settings: 
//    Display    On 
//    Color      White 
//    Blink      Off 
//    Cursor     Off 
//    Autoscroll Off 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Start(CySCB_Type *master, cy_stc_scb_i2c_context_t *context){

   cy_en_scb_i2c_status_t init_status;
    cy_en_sysint_status_t sys_status;
  
    init_status = Cy_SCB_I2C_Init(master, &I2C_config, context);
    sys_status = Cy_SysInt_Init(&I2C_SCB_IRQ_cfg, &I2C_Interrupt);
    if(init_status!=CY_SCB_I2C_SUCCESS){
        return false;
    }
    if(sys_status!=CY_SCB_I2C_SUCCESS){
        return false;
    }

    NVIC_EnableIRQ((IRQn_Type) I2C_SCB_IRQ_cfg.intrSrc);
    Cy_SCB_I2C_Enable(master);

    _showFunction |= LCD_2LINE;
    

    CyDelay(50);

    ///< this is according to the hitachi HD44780 datasheet
    ///< page 45 figure 23

    ///< Send function set command sequence
    command(LCD_FUNCTIONSET | _showFunction);
    CyDelay(5);  // wait more than 4.1ms
	
	///< second try
    command(LCD_FUNCTIONSET | _showFunction);
    CyDelay(5);

    ///< third go
    command(LCD_FUNCTIONSET | _showFunction);

    ///< turn the display on with no cursor or blinking default
    _showControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    LCD_Display(On);

    ///< clear it off
    LCD_Clear();

    ///< Initialize to default text direction (for romance languages)
    _showMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    ///< set the entry mode
    command(LCD_ENTRYMODESET | _showMode);
    
    
    ///< backlight init
    setReg(REG_MODE1, 0);
    ///< set LEDs controllable by both PWM and GRPPWM registers
    setReg(REG_OUTPUT, 0xFF);
    ///< set MODE2 values
    ///< 0010 0000 -> 0x20  (DMBLNK to 1, ie blinky mode)
    setReg(REG_MODE2, 0x20);
    
    LCD_SetColor(White);
   return true; 
    
}

// Turns the display on if MODE is On, turns display off otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Display(enum mode state){
    if(state == On){
    _showControl |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _showControl);
    }
    else{
        _showControl &= ~LCD_DISPLAYON;
        command(LCD_DISPLAYCONTROL | _showControl);
    }
    return true;
}

// Sets the display to blink if MODE is On, non-blinking otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Blink(enum mode x){
    if(x == On){
        _showControl |= LCD_BLINKON;
        command(LCD_DISPLAYCONTROL | _showControl);
        return true;
    }
    _showControl &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _showControl);
    return false;
}
 
// Shows the cursor if MODE is On, hides it otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Cursor(enum mode x){
    if(x == On){
        _showControl |= LCD_CURSORON;
        command(LCD_DISPLAYCONTROL | _showControl);
        return true;
    }
    _showControl &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _showControl);
    return false;
}
 
// Sets the display to autoscroll if MODE is On, non-scrolling otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Autoscroll(enum mode x){
    if( x == On){
        _showMode |= LCD_ENTRYSHIFTINCREMENT;
        command(LCD_ENTRYMODESET | _showMode);
        return true;
    }
     _showMode &= ~LCD_ENTRYSHIFTINCREMENT;
     command(LCD_ENTRYMODESET | _showMode);
    return false;
  
}
 
// Scrolls display on char left if DIRECTION is Left, one char right otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Scroll(enum direction x){
    if(x == Left){
        _showMode |= LCD_ENTRYLEFT;
        command(LCD_ENTRYMODESET | _showMode);
        return true;
    }
    else if(x == Right){
        _showMode &= ~LCD_ENTRYLEFT;
        command(LCD_ENTRYMODESET | _showMode);
        return true;
    }
    else{
        return false;
    }
}
 
// Sets display color if COLOR is White, Red, Green, or Blue, no-op otherwise. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_SetColor(enum color x){
    // RED = 255,0,0
    //Green = 0,255,0
    //Blue = 0,0,255
        if(x == White){
          LCD_SetRGB(255,255,255);  
        }
        if(x==Red){
            LCD_SetRGB(255,0,0);  
        }
        if(x==Green){
            LCD_SetRGB(0,255,0);  
        }
        if(x==Blue){
            LCD_SetRGB(0,0,255);  
        }
    return true;    
}
 
// Sets display color according to RED, GREEN, BLUE. 
// Example: LCD_SetRGB(0, 255, 255) for cyan. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_SetRGB(uint8_t red, uint8_t green, uint8_t blue){
    setReg(REG_RED, red);
    setReg(REG_GREEN, green);
    setReg(REG_BLUE, blue);
    return true;
}
 
// Positions the cursor at COL and ROW where 0<=COL<=15 and 0<=ROW<=1 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_SetCursor(uint8_t col, uint8_t row){
    if((col>=0 && col <=15)&&(row>=0&&row<=1)){
        col = (row == 0 ? col|0x80 : col|0xc0);
        uint8_t data[3] = {0x80, col};
        send(data, 2);
    }
    return false;
}

 
// Clears the display. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Clear(){
    command(LCD_CLEARDISPLAY);        // clear display, set cursor position to zero
    CyDelay(2);  
    return false;
}

 
// Prints all characters from zero terminated string STR. 
// If strlen(str) > 16, call LCD_Autoscroll(On) first. 
// Returns FALSE on error, TRUE otherwise. 
bool LCD_Print(char *str){
    uint8_t size = strlen(str);
    uint32_t i;
    if(size>16){
        LCD_Autoscroll(On);
        for (i = 0; i < size; i++){
            write(str[i]);
        }
      return true;
    }
    
       for (i = 0; i < size; i++){
            write(str[i]);
        }
      return false;
    
       
}