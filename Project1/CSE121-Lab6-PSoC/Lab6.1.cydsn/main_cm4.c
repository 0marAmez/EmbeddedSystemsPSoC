#include "project.h"
#include "ADXL.h"
#include "DRF0554.h"
#include <stdio.h>

float x,y,z;

int main(void)
{    
    __enable_irq(); /* Enable global interrupts. */
    
    UART_Start();
    I2C_ADXL_Start();
    ADXL343_init();
    LCD_Start(I2C_ADXL_HW, &I2C_ADXL_context);
    
    LCD_SetColor(Blue); 
    ADXL343_setRange(ADXL343_RANGE_16_G);
    sensors_event_t event;
    char buf1[5];
    //char buf2[5];
    //char buf3[5];

    
    for(;;){
        ADXL343_getEvent(&event);
        
        x=event.acceleration.x;
        y=event.acceleration.y;
        z=event.acceleration.z;
    
        printf("X: %f\r\n",event.acceleration.x);
        printf("Y: %f\r\n",event.acceleration.y);
        printf("Z: %f\r\n",event.acceleration.z);
        
        LCD_SetCursor(0,0);
        sprintf(buf1, "X:%.2f", x) ; // Convert to string
        LCD_Print(buf1);    
        sprintf(buf1, "Y:%.2f", y) ; // Convert to string
        LCD_SetCursor(8,0);
        LCD_Print(buf1);
        sprintf(buf1, "Z:%.2f", z) ; // Convert to string
        LCD_SetCursor(0,1);
        LCD_Print(buf1);
        
        CyDelay(50) ;      
    }
}
