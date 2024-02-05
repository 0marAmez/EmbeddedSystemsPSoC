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
    printf("CSE121 Lab 2.2 LED Brightness with UART and PWM \r\n");
    printf(" Press 'u' to increase brightness and 'd' to descreased. \r\n");
    setvbuf(stdin,NULL,_IONBF,0);
    int bright = 500;
    char c;
    
    for(;;)
    {
        scanf(" %c", &c);
        
        if(c == 'u'){
            if(bright>0){
            bright-=50;
            PWM_SetCompare0(bright);  
            }
        }
        else if ( c == 'd'){
            if(bright < 1000){
               bright+=50;
               PWM_SetCompare0(bright); 
            }
            
        }
        else{
           printf("**ERROR: Please enter a valid option. \r\n");
        }
 
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
