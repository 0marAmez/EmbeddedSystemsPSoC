#include "project.h" 
#include "DRF0554.h" 
#include <stdio.h> 
#include <string.h> 
 
int main(void) 
{ 
  UART_Start(); 
  printf("CSE121 Lab 3.3 DFR0554 Library\r\n"); 
 
  I2C_Start(); 
  LCD_Start(I2C_HW, &I2C_context); 
 
  LCD_SetColor(Blue); 
  LCD_Print("Hello CSE121"); 
  LCD_SetRGB(52, 152, 219);
  char c;
  
  char buf[16]; 
  uint16_t cnt = 0; 
 // bool a = false;
  bool b = false;
  bool cur = false;
  bool d = false;
  bool e = false;
  
  setvbuf(stdin,NULL,_IONBF,0);
  for (;;) { 
    scanf(" %c", &c);
    if(c== 'a'){
        
            LCD_Autoscroll(On);
    }
    else if (c == 'b'){
         if(b==false){
            LCD_Blink(On);
            b=true;
        }
        else{
          LCD_Blink(Off);
          b = false;
        }
         
    }
    else if (c == 'c'){
        if(cur==false){
            LCD_Cursor(On);
            cur=true;
        }
        else{
          LCD_Cursor(Off);
          cur = false;
        }
    }
    else if(c=='d'){
        if(d==false){
            LCD_Display(On);
            d=true;
        }
        else{
          LCD_Display(Off);
          d = false;
        }
    }
    else if(c=='e'){
         if(e==false){
             LCD_SetColor(Green);
            e=true;
        }
        else{
          LCD_SetColor(Blue);
          e = false;
        }
    }
    else if(c=='l'){
        LCD_Scroll(Left);
    }
    else if(c=='r'){
        LCD_Scroll(Right);
    }
    else if(c=='z'){
        LCD_Clear();
    }
    else{
        printf("Please, enter a valid option!\r\n");
    }
    LCD_SetCursor(0, 1); 
    sprintf(buf, "%u", cnt++); 
    LCD_Print(buf); 
    CyDelay(1000); 
  } 
} 
