/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h" 
#include "DRF0554.h" 
#include  <stdio.h>
#include <string.h>
int num = 1; // 1 = BLUE, 2 = GREEN,  3 = RED
void handler(void){
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    if(num == 3){
        num = 1;
    }
    else{ 
        num++;
    }
}
int main(void)
{
    int green = 0;
    int blue = 0;
    int red = 0;
    char str[3]; 
  
    __enable_irq(); /* Enable global interrupts. */
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    NVIC_EnableIRQ(SysInt_switch_cfg.intrSrc);
    UART_Start();
    ADC_Start();
    I2C_Start(); 
    LCD_Start(I2C_HW, &I2C_context);
    ADC_StartConvert();
    Cy_SysInt_Init(&SysInt_switch_cfg,handler);
    LCD_SetColor(Green); 
    LCD_Print(" RED GREEN BLUE "); 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //printf("CSE121 Lab 3.1 LED Brightness with different colors \r\n");
    setvbuf(stdin,NULL,_IONBF,0);
    LCD_SetRGB(red,green,blue);
    int bright;    
    for(;;)
    {    
        bright = ADC_GetResult16(0)/8; 
        if(bright ==256){
            bright-=1;
        }
        //CyDelay(50);
        if(num == 1){
           
           blue = bright;           
        }
        else if(num == 2){
          green = bright;
         
        }
        else{
          red = bright;
 
       }
        printf("Bright %d \r\n",bright);

        
           LCD_SetCursor(11, 1);
           sprintf(str, "% 4d", blue);
           LCD_Print(str);
        
        
          LCD_SetCursor(6, 1); 
          sprintf(str, "% 4d", green);
          LCD_Print(str);
        
        
          LCD_SetCursor(1, 1);
          sprintf(str, "% 4d", red);
          LCD_Print(str);
    
    
       LCD_SetRGB(red,green,blue);
       
 
  //  printf("Blue : %s \r\n" ,strBlue);
    //printf("Green : %s \r\n" ,strGreen);
    //printf("Red : %s \r\n" ,strRed);
        

        
        CyDelay(1000); 
        
        
        
        //Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
