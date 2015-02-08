#include "common.h"
#include "fl_bmp180.h"


void Bmp180Init()
{
	i2c_init (BMP180_I2C,  BMP180_I2C_SPEED);
}

uint32 Bmp180Read()
{
#warning This func is programming!
	return 0;
}