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
int num = 500;
bool max = false;
bool min = true;
void handler(void){
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    //0
    // 1000
    if(num == 0){
        max = true;
        min = false;
    }
    if(num == 1000){
        min = true;
        max = false;
    }
    if(max == true){
        num+=50;
    }
    else if (min == true){
        num-=50;
    }
    else{
        num+=50;
    }
    
    PWM_SetCompare0(num);  
    printf("Num: %d  \r\n", num );
    //}
     
    
}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    Cy_GPIO_ClearInterrupt(P0_4_PORT,P0_4_PIN);
    NVIC_ClearPendingIRQ(SysInt_switch_cfg.intrSrc);
    NVIC_EnableIRQ(SysInt_switch_cfg.intrSrc);
    PWM_Start();
    UART_Start();
    Cy_SysInt_Init(&SysInt_switch_cfg,handler);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    printf("CSE121 Lab 2.3 LED Brightness with User Switch and PWM \r\n");
    setvbuf(stdin,NULL,_IONBF,0);
    
    for(;;)
    {
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
      /*  
        scanf(" %c", &c);
        
        if(c == 'u'){
            bright-=50;
            PWM_SetCompare0(bright);  
        }
        else if ( c == 'd'){
            bright+=50;
            PWM_SetCompare0(bright); 
        }
        else{
           printf("**ERROR: Please enter a valid option. \r\n");
        }
 
        */
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
