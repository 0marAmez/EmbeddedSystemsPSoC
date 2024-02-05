

#include "project.h"
#include  <stdio.h>
#include <string.h>


float f;
float x,y,z,distance;
int i = 0;
int boolBuff;
int moving,rightSensor,leftSensor,behindSensor;



/* ===   VARIABLES  ===*/

#define TARGET_BDADDR   {{0x8D, 0xE8, 0xD3, 0x6C, 0x97, 0x01}, 0}

uint16_t arrHandlers[] = {0x000C,0x000F,0x0012,0x0015,0x0018,0x001B,0x001E,0x0021};

/*******************************************************************************
* Variables
*******************************************************************************/
cy_en_ble_api_result_t      apiResult = CY_BLE_SUCCESS;
cy_stc_ble_gap_bd_addr_t    remote_addr = TARGET_BDADDR;
bool    targetAddrFound = false;
bool connected = false;


cy_en_ble_api_result_t apiResult;
cy_stc_ble_gattc_find_info_req_t charDescHandleRange;
cy_stc_ble_gattc_read_by_type_req_t attrHandleRange;
cy_stc_ble_gattc_read_req_t readReq;




cy_stc_ble_conn_handle_t     conn_handle;



void BleAssert(void)
{
    CY_ASSERT(0u != 0u);   
}


void Ble_handler(uint32_t event, void *eventParam){
       cy_en_ble_api_result_t apiResult;
       uint8 bdAddrIndex;
       cy_stc_ble_gapc_adv_report_param_t * advReport;
       cy_stc_ble_gattc_read_rsp_param_t * read;
       uint8_t scanState = Cy_BLE_GetScanState();
    
       switch(event){    
        /**********************************************************
        *                     GAP Central Events
        ***********************************************************/
            case CY_BLE_EVT_STACK_ON:
               printf("Stack On and Scanning Starting \r\n");
               Cy_BLE_GAPC_StartScan(CY_BLE_SCANNING_FAST,0);  
                 break;
            /* This event is triggered every time a device is discovered */   
            case CY_BLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
                     advReport = (cy_stc_ble_gapc_adv_report_param_t *)eventParam;
                     /* Process only for Advertisement packets, not on scan response packets */
                     if(advReport->eventType != CY_BLE_GAPC_SCAN_RSP){
                         /* Set address 'found' status temporarily */
                         targetAddrFound = true;  
                         for(bdAddrIndex = 0; bdAddrIndex < CY_BLE_BD_ADDR_SIZE; bdAddrIndex++){
                             /* Set targetAddrFound status to false if BD address bytes don't match */
                             if (advReport->peerBdAddr[bdAddrIndex] != remote_addr.bdAddr[bdAddrIndex]){
                                 targetAddrFound = false;
                             }
                         }
                         if (targetAddrFound){
                             printf("Found target device with address: ");
                             printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n\n",advReport->peerBdAddr[5],\
                             advReport->peerBdAddr[4], advReport->peerBdAddr[3], advReport->peerBdAddr[2],\
                             advReport->peerBdAddr[1], advReport->peerBdAddr[0]);
                             Cy_BLE_GAPC_StopScan();
                         }
                     }
                break;
            case CY_BLE_EVT_GAPC_SCAN_START_STOP:
                    if(Cy_BLE_GetScanState() == CY_BLE_SCAN_STATE_STOPPED){
                        if(targetAddrFound == true){
                           /* Scan stopped manually; do not restart scan */
                            targetAddrFound = false;
                           /* Initiate Connection */
                            apiResult = Cy_BLE_GAPC_ConnectDevice(&remote_addr,CY_BLE_CENTRAL_CONFIGURATION_0_INDEX);
                        }
                    }
                break;           
              case CY_BLE_EVT_GATTC_READ_RSP:{
                read = (cy_stc_ble_gattc_read_rsp_param_t*) eventParam;
                printf("Reading: \r\n"); 
                //printf("Package length: %u \r\n",read->value.len);
                uint8_t buff [read->value.len+1];
                for(uint8 k=0;k<=read->value.len;k++){
                       // printf("\r\n Byte %u: %X",k+1,read->value.val[k]);
                        buff[k] = read->value.val[k];
                        //printf("\r\n Buffer %u: %X",k+1,buff[k]);
                }
                memcpy(&f, &buff, sizeof(f));
                memcpy(&boolBuff, &buff, sizeof(boolBuff));
                //printf("Boolean num: %d \r\n",boolBuff);
                switch(i){
                 case 0:
                    x = f;
                    i++;
                   break;
                 case 1:
                    y = f;
                    i++;
                   break;
                 case 2:
                    z =f;
                    i ++;
                    break;
                 case 3:
                    distance =f;
                    i ++;
                    break;
                 case 4:
                    moving = boolBuff;
                    i++;
                    break;
                 case 5:
                    leftSensor = boolBuff;
                    i++;
                    break;
                 case 6:
                    behindSensor = boolBuff;
                    i++;
                    break;
                 case 7:
                    rightSensor = boolBuff;
                    i=0;
                    break;   
                 default:
                    break;
                }
                printf(" X: %f  Y: %f  Z: %f \r\n",x,y,z);
                printf(" Distance: %f \r\n",distance);
                if(moving == 1){
                    printf(" Arduino and PSoC in motion \r\n");
                }
                else{
                    printf(" Arduino and PSoC not moving \r\n");
                }
                if(leftSensor == 1){
                    printf(" Motion detected in left Sensor \r\n");
                }
                else{
                    printf(" No Motion detected in left Sensor \r\n");
                }
                if(behindSensor == 1){
                    printf(" Motion detected in behind Sensor \r\n");
                }
                else{
                    printf(" No Motion detected in behind Sensor \r\n");
                }
                if(rightSensor == 1){
                    printf(" Motion detected in right Sensor \r\n");
                }
                else{
                    printf(" No Motion detected in right Sensor \r\n");
                }
         
               
               break;
              }           
            case CY_BLE_EVT_GATT_CONNECT_IND:
                printf("Connected as Central (master role) \r\n");    
                conn_handle = *(cy_stc_ble_conn_handle_t *)eventParam;
                connected = true;
                break;
            case CY_BLE_EVT_GATT_DISCONNECT_IND :
                 printf("Disconect, Scanning starting over \r\n");
                 Cy_BLE_GAPC_StartScan(CY_BLE_SCANNING_FAST,0);  
                 break;
            default:
                break;          
       }
}

int main(void){
    
    __enable_irq(); /* Enable global interrupts. */
  
    UART_Start();
    Cy_BLE_Start(Ble_handler);
    
       
    for(;;){
      Cy_BLE_ProcessEvents();
    
      if(connected==true){
         readReq.connHandle = conn_handle;
         readReq.attrHandle = arrHandlers[i] ;
         apiResult = Cy_BLE_GATTC_ReadCharacteristicValue(&readReq);

     // CHECK CONNECTION       
     //   if(apiResult == CY_BLE_SUCCESS){
     //        printf("\n\r Cy_BLE_GATTC_ReadCharacteristicValue SUCCESS \r\n");
     //    }           
      }
    }
    
    
}



/* [] END OF FILE */
