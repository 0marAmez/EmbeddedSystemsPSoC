#include "I2CHelper.h"

uint8_t temp_value = 0;
void I2CReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value)
{
	
    /******************INSERT CODE HERE******CODE 1.1*********/	
    /* Insert the code to read "length" number of bytes from the device address 
     * "devAddr" and register address "regAddr" passed to the function. Save this to
     * the location pointer by the pointer "value"  */
    
    
        uint8 i = 0;
        I2C_ADXL_MasterSendStart(devAddr,0,10);
        I2C_ADXL_MasterWriteByte(regAddr,10);
        I2C_ADXL_MasterSendReStart(devAddr,1,10);
        while((length - 1))
        {
            I2C_ADXL_MasterReadByte(CY_SCB_I2C_ACK,(value + i),10);
            i++;
            length--;
        }
        I2C_ADXL_MasterReadByte(CY_SCB_I2C_NAK,(value + i),10);
        I2C_ADXL_MasterSendStop(0);
    
    
    /****************END CODE 1.1 HERE*************************/
}

void I2CWriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value) 
{
	
    /******************INSERT CODE HERE******CODE 1.2*********/
    /* Insert the code to write "length" number of bytes to the device address 
     * "devAddr" and register address "regAddr" passed to the function. The data is
     * available from the location pointer by the pointer "value"  */
    

    uint8 i = 0;
    I2C_ADXL_MasterSendStart(devAddr,0,10);
    I2C_ADXL_MasterWriteByte(regAddr,10);
    while(length)
    {
        I2C_ADXL_MasterWriteByte(*(value + i),10);
        i++;
        length--;
    }
    I2C_ADXL_MasterSendStop(0);


    
    
    /****************END CODE 1.2 HERE*************************/
}

/* Following functions are build on top of the functions defined above. */
void I2CReadByte(uint8_t devAddr, uint8_t regAddr, uint8_t *value) {
	I2CReadBytes(devAddr, regAddr, 1, value);
}

uint8_t I2CSplReadByte(uint8_t devAddr, uint8_t regAddr) {
	
    I2CReadBytes(devAddr, regAddr, 1, &temp_value);
    return(temp_value);
}

void I2CReadBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, \
                                                uint8_t length, uint8_t *value) 
{
   	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    I2CReadByte(devAddr, regAddr, value);
    *value &= mask;
    *value >>= (bitStart - length + 1);
}

void I2CReadBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *value)
{
	I2CReadByte(devAddr, regAddr, value);
	*value = *value & (1 << bitNum);
}

void I2CWriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value) 
{
	I2CWriteBytes(devAddr, regAddr, 1, &value);
}

void I2CWriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, \
                                                  uint8_t length, uint8_t value) 
{
	uint8_t b;
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	I2CReadByte(devAddr, regAddr, &b);
	value <<= (bitStart - length + 1);
	value &= mask;
	b &= ~(mask);
	b |= value;
	I2CWriteByte(devAddr, regAddr, b);	
}

void I2CWriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t value)
{
	uint8_t b;
	I2CReadByte(devAddr, regAddr, &b);
	b = (value != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	I2CWriteByte(devAddr, regAddr, b);
}