#include "fl_MPU6050.h"

static void Mpu6050WriteHmc5883(uint8 reg, uint8 data);
static uint8 Mpu6050ReadHmc5883(uint8 reg);

void Mpu6050Init()
{
	i2c_init(Mpu6050_I2C,Mpu6050_I2C_Rate);
	DELAY_MS(50);//�ϵ�ȴ�
	Mpu6050WriteReg(PWR_MGMT_1, 0x00);	//�������״̬
	DELAY_MS(50);//
	Mpu6050WriteReg( SMPLRT_DIV, 0x07);
	Mpu6050WriteReg( CONFIG, 0x06);
	Mpu6050WriteReg( GYRO_CONFIG, 0x18);
	Mpu6050WriteReg( ACCEL_CONFIG, 0x18);
	Mpu6050WriteReg(USER_CTRL, 0x20);
	//Mpu6050WriteReg(I2C_MST_CTRL, 0x82);
	Mpu6050WriteReg(I2C_MST_CTRL, 0x0d);


	//Mpu6050WriteHmc5883(Mode_Register, 0x00);
}

static int16 Mpu6050Read16bitsReg(uint8 reg_h)
{
	uint8 h, l;

	h = Mpu6050ReadReg(reg_h);
	l = Mpu6050ReadReg(reg_h + 1);

	return (int16)((h << 8) | l);
}

struct Mpu6050Data Mpu6050Read()
{
	struct Mpu6050Data mpudata;
	int16 *mpudata_p = (int16*)&mpudata;

	//mpudata.accel.x = Mpu6050Read16bitsReg(ACCEL_XOUT_H);
	for (int8 i = 0; i < 7; i++)
	{
		*mpudata_p++ = Mpu6050Read16bitsReg(ACCEL_XOUT_H + 2 * i);
	}

	mpudata_p = (int16*)&mpudata;
	for (int8 i = 0; i < 3; i++)
	{
		*mpudata_p = *mpudata_p++ * 100 / AFS_SEL;
	}

	*mpudata_p = (*mpudata_p++ / 340 + 36.53) * 100;

	for (int8 i = 4; i<7; i++)
	{
		*mpudata_p = *mpudata_p++ * 100 / FS_SEL ;
	}

	return mpudata;
}
// 
// static void Mpu6050WriteHmc5883(uint8 reg, uint8 data)
// {
// 	Mpu6050WriteReg(I2C_SLV0_ADDR, Mpu6050I2cMasterWrite/*|Mpu6050I2cMasterRead*/ | Hmc5883L_Add);//����hmc5883l������ַ,д��ģʽ
// 	Mpu6050WriteReg(I2C_SLV0_REG, reg);//���ͼĴ�����ַ
// 	Mpu6050WriteReg(I2C_SLV0_DO, data);//��������
// 	Mpu6050WriteReg(I2C_SLV0_CTRL, 0x81);//��ʼ
// 	DELAY_MS(10);
// }



// static uint8 Mpu6050ReadHmc5883(uint8 reg)
// {
// 	Mpu6050WriteReg(I2C_SLV0_ADDR, /*Mpu6050I2cMasterWrite|*/Mpu6050I2cMasterRead | Hmc5883L_Add);//����hmc5883l������ַ,д��ģʽ
// 	Mpu6050WriteReg(I2C_SLV0_REG, reg);//���ͼĴ�����ַ
// 	Mpu6050WriteReg(I2C_SLV0_CTRL, 0x81);//��ʼ
// 	DELAY_MS(10); 
// 	return Mpu6050ReadReg(EXT_SENS_DATA_00);
// }


/*
static int16 Mpu6050ReadHmc16bitsReg(uint8 reg_h)
{
	uint8 h, l;

	h = Mpu6050ReadHmc5883(reg_h);
	l = Mpu6050ReadHmc5883(reg_h + 1);

	return (int16)((h << 8) | l);
}
*/

/*
struct Hmc5883LData MpuReadHcmData()
{
	struct Hmc5883LData data;
	int16 * p = (int16 *)&data;
	for (int8 i = 0; i < 3; i++)
	{
		*p++ = Mpu6050ReadHmc16bitsReg(Data_Output_X_MSB + 2 * i);
	}
	return data;
}
*/