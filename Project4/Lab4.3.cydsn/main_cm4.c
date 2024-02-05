

#include "project.h"
#include "DRF0554.h" 
#include  <stdio.h>
#include <string.h>


// ==== Link's used for this project ===
// https://iotexpert.com/psoc-6-ble-events/

bool advertising = false;
bool connected = false;
bool starter = false;
uint8 bVal = 0;

void handler(void){
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    starter = true;
    if(advertising == false && connected == false){
            advertising = true;
            printf("BLE_EVT_STACK_ON(Ble ON advertisement starting)\r\n");
            LCD_SetCursor(0,0);
            LCD_Print("STACK ON"); 
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
       
            printf("BLE_EVT_STACK_ON(Ble ON advertisement starting\r\n");
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_Print("Lab 4.3 Events:"); 
            LCD_SetCursor(0,1);
            LCD_Print("STACK ON"); 
           if(starter == true){ 
            if(Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX)==CY_BLE_SUCCESS){
                printf("Sucessful Advertisemnt \r\n");
            }
            else{
                printf("Advertisement failed \r\n");
            } 
            printf("STACK ON)\r\n");
        }
            //advertising = true;
            break;  
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: // DEVICE DISCONNECTED
            connected = false;
            printf("CY_BLE_EVT_GAP_DEVICE_DISCONNECTED(Device Disconnected): bdHandle=%x, reason=%x, status=%x\r\n-------------\r\n",
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).bdHandle,
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).reason,
            (unsigned int)(*(cy_stc_ble_gap_disconnect_param_t *)eventParam).status);
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        case CY_BLE_EVT_GATT_CONNECT_IND: // This event is generated at the GAP Peripheral end AFTER A CONNECTION IS COMPLETED with a peer Central device. 
 
            printf("CY_BLE_EVT_GATT_CONNECT_IND bdHandle=%x\r\n",((cy_stc_ble_conn_handle_t *)eventParam)->bdHandle);
            break;
        case CY_BLE_EVT_GAP_ENHANCE_CONN_COMPLETE: // This event is generated at the GAP Peripheral end after the connection is completed with a peer Central device. 
            connected = true;
            advertising = false;
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_Print("Lab 4.3 Events:"); 
            LCD_SetCursor(0,1);
            LCD_Print("Connected"); 
            PWM_Green_SetCompare0(1000);
            PWM_Blue_SetCompare0(0);
            printf("CY_BLE_EVT_GAP_ENHANCE_CONN_COMPLETE\r\n");
            break;
        case CY_BLE_EVT_TIMEOUT: // This event is received when there is a timeout and the application must handle the event.
            printf("TIMEOUT\r\n");
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_Print("Lab 4.3 Events:"); 
            LCD_SetCursor(0,1);
            LCD_Print("TIMEOUT"); 
            //Cy_BLE_GAPP_StopAdvertisement();
            //PWM_Green_SetCompare0(1000);
            //PWM_Blue_SetCompare0(1000);
            advertising = false;
        connected = false;
            break;
        case CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ: // This event is triggered on the GATT Server side when the GATT Client sends a read request and when characteristic has the CY_BLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set
            printf("CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ\r\n");
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_Print("Lab 4.3 Events:"); 
            LCD_SetCursor(0,1);
            LCD_Print("READ REQUEST"); 
            bVal++;
            break;
        case CY_BLE_EVT_GATT_DISCONNECT_IND: // This event indicates that the GATT is disconnected. 
             printf("CY_BLE_EVT_GATT_DISCONNECT_IND\r\n");
             break;
        case CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP: // This event indicates that the GAP Peripheral device has started/stopped advertising
            if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED){ // If Advertising is stopped.
                advertising = false;    
                printf("Advertisement Stopped\r\n");
                PWM_Green_SetCompare0(1000);
                PWM_Blue_SetCompare0(1000);
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_Print("Lab 4.3 Events:"); 
                LCD_SetCursor(0,1);
                LCD_Print("Stopped Adv");
            }
           else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADV_INITIATED){ // If Advertising is initiated. 
                advertising = true;    
                printf("Advertisement initiated\r\n");
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_Print("Lab 4.3 Events:"); 
                LCD_SetCursor(0,1);
                LCD_Print("Adv initiated");    
        }
            else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADVERTISING){ // Currently advertising  
                advertising = true;   
                PWM_Green_SetCompare0(0); 
                PWM_Blue_SetCompare0(1000);
                printf("Advertisement in Progress\r\n");
                
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_Print("Lab 4.3 Events:"); 
                LCD_SetCursor(0,1);
                LCD_Print("Adv in Progress");
            }
            else if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOP_INITIATED){ // if Stop advertising is initiated
                printf("Avertisement stop initiated\r\n");
                advertising = false;
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_Print("Lab 4.3 Events:"); 
                LCD_SetCursor(0,1);
                LCD_Print("Adv stop INT");    
               // printf("\r\n");
            }
            break;
        case CY_BLE_EVT_GATTS_INDICATION_ENABLED: // GATT Server - Indication for GATT Service's "Service Changed" Characteristic was enabled.
            printf("CY_BLE_EVT_GATTS_INDICATION_ENABLED\r\n");
            break;
        case CY_BLE_EVT_GAP_DEVICE_CONNECTED:// This event is generated at the GAP Peripheral end after the connection is completed with a peer Central device. 
            printf("CY_BLE_EVT_GAP_DEVICE_CONNECTED\r\n");
            break;
        default:
            printf("Unknown Event = %X\n",(unsigned int)event);
            break;
    }
}

int main(void){
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
    
   // PWM_Blue_SetCompare0(1000);
    //PWM_Green_SetCompare0(1000);
    printf("CSE121 Lab 4.3 BLE Server\r\n");
    LCD_SetCursor(0,0);
    LCD_Print("CSE121 Lab 4.3");    
    
    Cy_BLE_Start(Ble_handler);
    
    
    cy_stc_ble_stack_lib_version_t stackVersion;
    //cy_en_ble_api_result_t apiResult = 
    Cy_BLE_GetStackLibraryVersion(&stackVersion);
    printf("Stack Version %d.%d.%d.%d.nn\r\n", stackVersion.majorVersion,stackVersion.minorVersion,stackVersion.patch,stackVersion.patch);
    
    
    cy_stc_ble_gatt_handle_value_pair_t  locHandleValuePair;
   locHandleValuePair.attrHandle = CY_BLE_PROXIMITY_DISTANCE_CHAR_HANDLE;
    locHandleValuePair.value.len = 1;
   
    
    for(;;){
         
        locHandleValuePair.value.val = &bVal;
        Cy_BLE_ProcessEvents();
        Cy_BLE_GATTS_WriteAttributeValueLocal(&locHandleValuePair); 
    }
    
    
}

/* [] END OF FILE */
