

#include "project.h"
#include "DRF0554.h" 
#include  <stdio.h>
//#include <inttypes.h>
#include <string.h>
#include "ipc_communication.h"



// ==== Link's used for this project ===
// https://iotexpert.com/psoc-6-ble-events/

ipc_msg_t ipc_msg = {
    .client_id  = IPC_CM4_TO_CM0_CLIENT_ID,
    .cpu_status = 0,
    .intr_mask   = USER_IPC_PIPE_INTR_MASK,
    .cmd        = IPC_CMD_STATUS,
    .value      = 0
};

// ==== GLOBAL VARIABLES ====
void cm4p_msg_callback(uint32_t *msg);
volatile bool msg_flag = false;
volatile uint32_t msg_value;
volatile uint8_t msg_cmd = 0;
bool advertising = false;
bool connected = false;
bool starter = false;
uint8 bVal = 0;
// =========================

void handler(void){
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    starter = true;
    if(advertising == false && connected == false){
            advertising = true;
            printf("BLE_EVT_STACK_ON(Ble ON advertisement starting)\r\n");

            if(Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX)==CY_BLE_SUCCESS){
                printf("Sucessful Advertisemnt \r\n");
            }
            else{
                printf("Advertisement failed \r\n");
            }   
    }

}

void Ble_handler(uint32_t event, void *eventParam){
    /* Take an action based on the current event */
        switch (event){
        /* This event is received when the BLE stack is Started */
        case CY_BLE_EVT_STACK_ON: // STACK IS ON
            
            ipc_msg.value = 7u;
            Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
            msg_cmd = 0;
            printf("BLE_EVT_STACK_ON(Ble ON advertisement starting\r\n");
           if(starter == true){ 
                 if(Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX)==CY_BLE_SUCCESS){
                    printf("Sucessful Advertisemnt \r\n");
                }
                else{
                    printf("Advertisement failed \r\n");
                }   
            }   
            break;  
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: // DEVICE DISCONNECTED
            connected = false;
            printf("CY_BLE_EVT_GAP_DEVICE_DISCONNECTED(Device Disconnected): bdHandle=%x, reason=%x, status=%x\r\n-------------\r\n",
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).bdHandle,
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).reason,
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).status);     
            ipc_msg.value = 4u;
            Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
            msg_cmd = 0;
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        case CY_BLE_EVT_GAP_ENHANCE_CONN_COMPLETE: // This event is generated at the GAP Peripheral end after the connection is completed with a peer Central device. 
            connected = true;
            advertising = false;
            ipc_msg.value = 3u;
            Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
            msg_cmd = 0;
            PWM_Green_SetCompare0(1000);
            PWM_Blue_SetCompare0(0);
            printf("CY_BLE_EVT_GAP_ENHANCE_CONN_COMPLETE\r\n");
            break;
        case CY_BLE_EVT_TIMEOUT: // This event is received when there is a timeout and the application must handle the event.
            printf("TIMEOUT\r\n");
            ipc_msg.value = 6u;
            Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
            msg_cmd = 0; 
            //PWM_Green_SetCompare0(1000);
            //PWM_Blue_SetCompare0(1000);
            advertising = false;
            connected = false;
            break;
        case CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ: // This event is triggered on the GATT Server side when the GATT Client sends a read request and when characteristic has the CY_BLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set
            printf("CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ\r\n");
            ipc_msg.value = 5u;
            Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
            msg_cmd = 0;
            bVal++;
            break;
        case CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP: // This event indicates that the GAP Peripheral device has started/stopped advertising
            if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED){ // If Advertising is stopped.
                advertising = false;    
                printf("Advertisement Stopped\r\n");
                PWM_Green_SetCompare0(1000);
                PWM_Blue_SetCompare0(1000);
                ipc_msg.value = 2u;
                Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
                msg_cmd = 0;
            }
           else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADV_INITIATED){ // If Advertising is initiated. 
                advertising = true;    
                printf("Advertisement initiated\r\n");
                PWM_Blue_SetCompare0(1000);
                PWM_Green_SetCompare0(0); 
            }
            else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADVERTISING){ // Currently advertising  
                advertising = true;   
                PWM_Green_SetCompare0(0); 
                PWM_Blue_SetCompare0(1000);
                printf("Advertisement in Progress\r\n");
                ipc_msg.value = 1u;
                Cy_IPC_Pipe_SendMessage(USER_IPC_PIPE_EP_ADDR_CM0, USER_IPC_PIPE_EP_ADDR_CM4, (uint32_t *)&ipc_msg, NULL);
                msg_cmd = 0;
            }
            else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOP_INITIATED){ // if Stop advertising is initiated
                printf("Avertisement stop initiated\r\n");
                advertising = false;
                PWM_Blue_SetCompare0(1000);
                PWM_Green_SetCompare0(1000);
            }
            break;
        default:
            printf("Unknown Event = %X\n",(unsigned int)event);
            break;
    }
}

int main(void){
      setup_ipc_communication_cm4();
    __enable_irq(); /* Enable global interrupts. */
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    NVIC_EnableIRQ(SysInt_switch_cfg.intrSrc);
    Cy_SysInt_Init(&SysInt_switch_cfg,handler);
    
    
    UART_Start();
    I2C_Start();
    LCD_Start(I2C_HW, &I2C_context);
    LCD_SetRGB(52, 152, 219);
    PWM_Blue_Start();
    PWM_Green_Start();
    Cy_BLE_Start(Ble_handler);
    

    printf("CSE121 Lab 4.4 BLE Server\r\n");
 
// =========  PRINT STACK VERSION ===========
    cy_stc_ble_stack_lib_version_t stackVersion;
    Cy_BLE_GetStackLibraryVersion(&stackVersion);
    printf("Stack Version %d.%d.%d.%d.nn\r\n", stackVersion.majorVersion,stackVersion.minorVersion,stackVersion.patch,stackVersion.patch);
    
    
    cy_stc_ble_gatt_handle_value_pair_t  locHandleValuePair;
   locHandleValuePair.attrHandle = CY_BLE_PROXIMITY_DISTANCE_CHAR_HANDLE;
   locHandleValuePair.value.len = 1;
   Cy_IPC_Pipe_RegisterCallback(USER_IPC_PIPE_EP_ADDR, cm4p_msg_callback, IPC_CM0_TO_CM4_CLIENT_ID);
   CyDelay(500);
 
    for(;;){
        
        if (msg_flag){
            msg_flag = false;
            bVal = msg_value;
        }
         
        locHandleValuePair.value.val = &bVal;
        Cy_BLE_ProcessEvents();
        Cy_BLE_GATTS_WriteAttributeValueLocal(&locHandleValuePair); 
    }
    
    
}

void cm4p_msg_callback(uint32_t *msg){
    ipc_msg_t *ipc_recv_msg;

    if (msg != NULL)
    {
        /* Cast the message received to the IPC structure */
        ipc_recv_msg = (ipc_msg_t *) msg;

        /* Extract the command to be processed in the main loop */
        msg_cmd = ipc_recv_msg->cmd;
        
        /* Extract the message value */
        msg_value = ipc_recv_msg->value;

        /* Set message flag */
        msg_flag = true;
    }
}

/* [] END OF FILE */
