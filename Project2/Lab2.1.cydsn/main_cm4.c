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
    UART_Start();
    
    
    printf("CSE121 Lab 2.1 UART printf() and getchar() \r\n");
    setvbuf(stdin,NULL,_IONBF,0);
    char c;
    
    for(;;)
    {
        scanf(" %c", &c);
        printf("Chacrater: %c \r\n",c);
        printf("Number: %d   \r\n",c);
        
        

        //printf("CSE121 Lab 2.1 UART printf() and getchar() \r\n");
        //CyDelay(2000);
        
        /* Place your application code here. */
    }
    
    
}

/* [] END OF FILE */
