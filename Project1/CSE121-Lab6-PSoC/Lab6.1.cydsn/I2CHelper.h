#include "project.h" 



void I2CReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);

void I2CWriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);

/* Following functions are build on top of the functions defined above. */
void I2CReadByte(uint8_t devAddr, uint8_t regAddr, uint8_t *value);

uint8_t I2CSplReadByte(uint8_t devAddr, uint8_t regAddr);

void I2CReadBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, \
                                                uint8_t length, uint8_t *value);

void I2CReadBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *value);
void I2CWriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value);

void I2CWriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, \
                                                  uint8_t length, uint8_t value) ;
void I2CWriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t value);


