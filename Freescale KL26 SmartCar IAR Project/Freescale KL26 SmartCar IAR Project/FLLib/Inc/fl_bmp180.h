#ifndef _FL_Bmp180_
#define _FL_Bmp180_

/* Default I2C pin */
#define Bmp180I2C					I2C1

/* Default I2C speed */
#define Bmp180I2CSpeed				(100 * 1000)

/* Bmp180 I2C address */
#define Bmp180I2CAddress			0xEE

/* Registers */
#define	Bmp180RegisterContral 		0xF4
#define	Bmp180RegisterResult 		0xF6
#define Bmp180RegisterEeprom		0xAA

/* Commands */
#define	Bmp180CommandTemperature 	0x2E
#define	Bmp180CommandPressure0		0x34
#define	Bmp180CommandPressure1		0x74
#define	Bmp180CommandPressure2		0xB4
#define	Bmp180CommandPressure3		0xF4

/* Minimum waiting delay, in microseconds */
#define Bmp180TemperatureDelay		4500
#define Bmp180Pressure0Delay		4500
#define Bmp180Pressure1Delay		7500
#define Bmp180Pressure2Delay		13000
#define Bmp180Pressure3Delay		25000

void Bmp180Init();

uint32 Bmp180Read();

#endif//_FL_Bmp180_