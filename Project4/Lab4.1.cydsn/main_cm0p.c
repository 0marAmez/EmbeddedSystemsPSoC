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

int value_counter;
float distance;
int duration;


int main(void)
{
   __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
  //  Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
    UART_Start();
    I2C_Start();
    Counter_1_Start();
    LCD_Start(I2C_HW, &I2C_context);
    LCD_SetColor(Blue); 
    LCD_Print("CSE121 Lab 4.1"); 
    LCD_SetCursor(0, 1); 
    LCD_Print("Distance:");
    
    LCD_SetRGB(52, 152, 219);
   // Counter_1_Start();
    char str [5];
    //uint32_t x;
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;) {        
       Cy_GPIO_Write(Trigger_PORT,Trigger_NUM,1);        //Set the trigger pin high 
       CyDelayUs(10);                                     //Wait 10us     
       Cy_GPIO_Write(Trigger_PORT,Trigger_NUM,0);       //Set the trigger pin low 
       
       while(Cy_GPIO_Read(Echo_PORT,Echo_NUM)==0);     // when the echo pien goes low restart
       Counter_1_SetCounter(0);                        // Reset timer for next scan 
       while(Cy_GPIO_Read(Echo_PORT,Echo_NUM)==1);     // When the echo pin goes high (not object detected)
       duration = Counter_1_GetCounter();              // Get count 
       distance = ((Counter_1_GetCounter()) * 346.513)/ 240000.0; // Calculate distance
       sprintf(str, "%d.%02dcm", (int)distance, (int)(100 * distance)%100) ; // Convert to string
    
       
       //printf("Distance: %f cm \r\n",distance);
       //printf(" String form: %s \r\n",str);
       LCD_SetCursor(9, 1); 
       LCD_Print(str);
           
    }
}

/* [] END OF FILE */
