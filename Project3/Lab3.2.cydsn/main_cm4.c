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
#include "cy_device_headers.h"
#include "project.h"
#include  <stdio.h>


cy_stc_scb_uart_context_t UART_context;
cy_stc_scb_i2c_context_t I2C_context;
// Print the probe table
void probe(){
    uint32_t rval;
    
    // Iterate through the address starting at 0x00
    for(uint32_t i2caddress=0;i2caddress<0x80;i2caddress++){
        rval = Cy_SCB_I2C_MasterSendStart(I2C_HW,i2caddress,CY_SCB_I2C_WRITE_XFER,10,&I2C_context);
        if(rval == CY_SCB_I2C_SUCCESS ){ // If you get ACK then print the address
            printf("Addres Found: 0x%02X \r\n",(unsigned int)i2caddress);
        }
        Cy_SCB_I2C_MasterSendStop(I2C_HW,0,&I2C_context);
    }
    printf("\r\n");
}
int main(void)
{
    /* Set up the device based on configurator selections */
    UART_Start();
    I2C_Start();
    Cy_SCB_UART_Init(UART_HW,&UART_config,&UART_context);
    Cy_SCB_UART_Enable(UART_HW);
    setvbuf( stdin, NULL, _IONBF, 0 ); // Turn off stdin buffering
    Cy_SCB_I2C_Init(I2C_HW,&I2C_config,&I2C_context);
    Cy_SCB_I2C_Enable(I2C_HW);
    __enable_irq();
    printf("\r\n");
    printf("I2C Detect\r\n");
    printf("Press p to show addresses \r\n");
    probe(); // Do an initial probe
    while(1){
            char c = getchar();
            switch(c)
            {
            case 'p':
            probe();
            break;
            case '?':
                printf("------------------\r\n");
            printf("Command\r\n");
                printf("p\tProbe\r\n");
                printf("?\tHelp\r\n");
                break;
            }
    }
    
    
}

/* Code partially copied from function probe and main obtained from https://iotexpert.com/i2c-detect-with-psoc-6/ */

/* [] END OF FILE */

