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
#include  <stdio.h>

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Start();
    UART_Start();
    ADC_Start();
    ADC_StartConvert();
    
    printf("CSE121 Lab 2.4 LED Brightness with POT, PWM and ADC \r\n");
    int num;
    
    for(;;)
    {
        num = ADC_GetResult16(0);
        printf("Number: %d \r\n", num); 
        CyDelay(50);
        if(num>=0&&num<900){
            PWM_SetCompare0(num); 
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
