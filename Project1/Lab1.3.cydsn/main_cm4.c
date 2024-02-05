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

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        Cy_GPIO_Write(GREEN_PORT,GREEN_NUM,0); // Starts the oppossite as red to obtain different pattern
        CyDelay(500);
        Cy_GPIO_Write(GREEN_PORT,GREEN_NUM,1);
        CyDelay(500); // Add delay for it to be alternating flashing
    }
}

/* [] END OF FILE */
