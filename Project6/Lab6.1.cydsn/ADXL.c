#include "ADXL.h"

uint64 Uint8ArrtoUint64 (uint8* var, uint32 lowest_pos)
{
    return  (((uint64)var[lowest_pos+7]) << 56) | 
            (((uint64)var[lowest_pos+6]) << 48) |
            (((uint64)var[lowest_pos+5]) << 40) | 
            (((uint64)var[lowest_pos+4]) << 32) |
            (((uint64)var[lowest_pos+3]) << 24) | 
            (((uint64)var[lowest_pos+2]) << 16) |
            (((uint64)var[lowest_pos+1]) << 8)  | 
            (((uint64)var[lowest_pos])   << 0);
}

void ADXL343_init(void) {
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_INT_ENABLE, 0);     // Disable interrupts to start
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_THRESH_TAP, 20);    // 62.5 mg/LSB (so 0xFF = 16 g)
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_DUR, 50);           // Max tap duration, 625 µs/LSB
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_LATENT, 0);         // Tap latency, 1.25 ms/LSB, 0=no double tap
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_WINDOW, 0);         // Waiting period,  1.25 ms/LSB, 0=no double tap
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_TAP_AXES, 0x7);     // Enable the XYZ axis for tap
  I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_POWER_CTL, 0x08);   // Enable measurements
}

void ADXL343_setRange(adxl34x_range_t range) {
    uint64_t _b;
    uint64_t _s;
    uint8_t byte[8];

    _s = range;
    
    I2CReadBytes(ADXL343_ADDRESS, ADXL3XX_REG_DATA_FORMAT, 8, byte);
    
    _b = Uint8ArrtoUint64(byte, 0);
	_s |= (_b & 0xB11101100);
	I2CWriteByte(ADXL343_ADDRESS, ADXL3XX_REG_DATA_FORMAT, _s);
}

void ADXL343_readAccel(int *x, int *y, int *z) {
	I2CReadBytes(ADXL343_ADDRESS, ADXL3XX_REG_DATAX0, 6, _buff); // Read Accel Data from ADXL343

	// Each Axis @ All g Ranges: 10 Bit Resolution (2 Bytes)
	*x = (int16_t)((((int)_buff[1]) << 8) | _buff[0]);
	*y = (int16_t)((((int)_buff[3]) << 8) | _buff[2]);
	*z = (int16_t)((((int)_buff[5]) << 8) | _buff[4]);
}

void ADXL343_getEvent(sensors_event_t *event) {
  int x, y, z;
  memset(event, 0, sizeof(sensors_event_t));

  ADXL343_readAccel(&x, &y, &z);

  event->acceleration.x = x * ADXL343_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  event->acceleration.y = y * ADXL343_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  event->acceleration.z = z * ADXL343_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
}