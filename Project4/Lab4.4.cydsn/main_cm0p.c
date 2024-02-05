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
#include "ipc_communication.h"

// ===LINK USED ===
//https://community.infineon.com/t5/PSoC-6/HOW-TO-INTERFACE-HC-SR04-ULTRASONIC-SENSOR-WITH-PSOC-6/td-p/106576
//https://github.com/Infineon/mtb-example-psoc6-dual-cpu-ipc-pipes


#define SEND_IPC_MSG(x) ipc_msg.cmd = x; \
                        Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM4, \
                                                USER_IPC_PIPE_EP_ADDR_CM0, \
                                                (void *) &ipc_msg, 0);
                                                
void cm0_msg_callback(uint32_t *msg);


ipc_msg_t ipc_msg = {               
    .client_id  = IPC_CM0_TO_CM4_CLIENT_ID,
    .cpu_status = 0,
    .intr_mask  = USER_IPC_PIPE_INTR_MASK,
    .cmd        = IPC_CMD_INIT,
};

volatile bool msg_flag = false;
volatile uint32_t msg_value;

//int echo_flag = 0;
double distance = 0.0;
uint16_t duration = 0;
char str[5];

void Timer_Int_Handler(void){
    NVIC_ClearPendingIRQ(Timer_Echo_Int_cfg.intrSrc) ;
    NVIC_DisableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
    duration = Timer_Echo_GetCapture() ;
    Timer_Echo_SetCounter(0) ;
    PWM_Trigger_Disable() ;
    //echo_flag = 1;

}

int main(void)
{
   __enable_irq(); /* Enable global interrupts. */
    setup_ipc_communication_cm0();
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    Cy_SysInt_Init(&Timer_Echo_Int_cfg, Timer_Int_Handler) ;
    NVIC_EnableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
    
    UART_Start();
    I2C_Start();
    LCD_Start(I2C_HW, &I2C_context);
    Timer_Echo_Start();
    PWM_Trigger_Start();
    LCD_SetColor(Green);
    
    Cy_IPC_Pipe_RegisterCallback(USER_IPC_PIPE_EP_ADDR, cm0_msg_callback, IPC_CM4_TO_CM0_CLIENT_ID); 
    SEND_IPC_MSG(IPC_CMD_INIT);
    
  //  LCD_Print("CSE121 Lab 4.2");

    
    for(;;) { 
        
        if(msg_flag){
            msg_flag = false;
            if((unsigned int) msg_value == 1u){
                  LCD_Clear();
                  LCD_Print("ADV MODE");
            }
            else if((unsigned int) msg_value == 2u){
                    LCD_Clear();
                    LCD_Print("STOP AVD MODE");
            }
            else if((unsigned int) msg_value == 3u){
                     LCD_Clear();
                      LCD_Print("CONNECTED");
            }
            else if((unsigned int) msg_value == 4u){
                    LCD_Clear();
                    LCD_Print("DISCONNECTED");
            }
            else if((unsigned int) msg_value == 5u){
                      LCD_Clear();
                      LCD_Print("READING");
            }
            else if((unsigned int) msg_value == 6u){
                    LCD_Clear();
                    LCD_Print("TIMEOUT");
            }
            else if((unsigned int) msg_value == 7u){
                     LCD_Clear();
                    LCD_Print("STACK ON");
            }
        }
        
       // if(echo_flag==1){
             distance = ((double)(duration)*346.513)/ 240000.0 ;
             sprintf(str, "%d.%02dcm", (int)distance, (int)(100*distance)%100);
             printf("Distance: %s s\r\n",str);
             LCD_SetCursor(0, 1); 
             LCD_Print("Distance:");
             LCD_SetCursor(9, 1); 
             LCD_Print(str);
             ipc_msg.value = (uint8_t)distance;
             Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM4, USER_IPC_PIPE_EP_ADDR_CM0, (uint32_t *)&ipc_msg, NULL);
             //echo_flag = 0;
             NVIC_EnableIRQ((IRQn_Type)Timer_Echo_Int_cfg.intrSrc) ;
             PWM_Trigger_Start();
       // }
        CyDelay(500) ;      
    }
}

void cm0_msg_callback(uint32_t *msg)
{
    ipc_msg_t *ipc_recv_msg;

    if (msg != NULL)
    {
        /* Cast received message to the IPC message structure */
        ipc_recv_msg = (ipc_msg_t *) msg;

        /* Extract the message value */
        msg_value = ipc_recv_msg->value;

        /* Set message flag */
        msg_flag = true;
    }
    
}

/* [] END OF FILE */

