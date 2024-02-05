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
// ===LINK USED ===
//https://community.infineon.com/t5/PSoC-6/HOW-TO-INTERFACE-HC-SR04-ULTRASONIC-SENSOR-WITH-PSOC-6/td-p/106576
int duration = 0;
double distance = 0.0 ;
char str[5];

void Timer_Int_Handler(void){
    NVIC_ClearPendingIRQ(Timer_Echo_Int_cfg.intrSrc) ;
    NVIC_DisableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
    duration = Timer_Echo_GetCapture() ;
    Timer_Echo_SetCounter(0) ;
    PWM_Trigger_Disable() ;
}

int main(void)
{
   __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
  //  Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
    UART_Start();
    I2C_Start();
    LCD_Start(I2C_HW, &I2C_context);
    Cy_SysInt_Init(&Timer_Echo_Int_cfg, Timer_Int_Handler) ;
    NVIC_EnableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
    Timer_Echo_Start();
    PWM_Trigger_Start();
    LCD_SetColor(Green); 
    LCD_Print("CSE121 Lab 4.2");
    LCD_SetCursor(0, 1); 
    LCD_Print("Distance:");
    
    for(;;) { 
        distance = ((double)(duration)*346.513)/ 240000.0 ;
        sprintf(str, "%d.%02dcm", (int)distance, (int)(100*distance)%100);
        printf("Distance: %s s\r\n",str);
        LCD_SetCursor(9, 1); 
        LCD_Print(str);
        NVIC_EnableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
        PWM_Trigger_Start();
        CyDelay(500) ;      
    }
}

/* [] END OF FILE */
