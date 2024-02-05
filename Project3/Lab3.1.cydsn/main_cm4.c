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
int num = 1; // 1 = BLUE, 2 = GREEN,  3 = RED
void handler(void){
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    if(num == 3){
        num = 1;
    }
    else{ 
        num++;
    }
}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    NVIC_EnableIRQ(SysInt_switch_cfg.intrSrc);
    PWM_Start();
    PWM_1_Start();
    PWM_2_Start();
    UART_Start();
    ADC_Start();
    ADC_StartConvert();
    Cy_SysInt_Init(&SysInt_switch_cfg,handler);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    printf("CSE121 Lab 3.1 LED Brightness with different colors \r\n");
    setvbuf(stdin,NULL,_IONBF,0);
    int bright;    
    for(;;)
    {  
        bright = ADC_GetResult16(0)/2;      
        CyDelay(50);
     if(num == 1){
        printf("Current Brightness: %d \r\n", bright); 
        printf("Color on display BLUE.\r\n");
        PWM_SetCompare0(bright); 
               
     }
       else if(num == 2){
          printf("Current Brightness: %d \r\n", bright); 
          printf("Color on display GREEN.\r\n");
          PWM_1_SetCompare0(bright);       
     }
       else{
          printf("Current Brightness: %d \r\n", bright); 
          printf("Color on display RED.\r\n");
          PWM_2_SetCompare0(bright);        
       }
        
        //Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
