#include "fl_MPU6050.h"

static void Mpu6050WriteHmc5883(uint8 reg, uint8 data);
static uint8 Mpu6050ReadHmc5883(uint8 reg);

void Mpu6050Init()
{
	i2c_init(Mpu6050_I2C,Mpu6050_I2C_Rate);
	DELAY_MS(50);//上电等待
	Mpu6050WriteReg(PWR_MGMT_1, 0x00);	//解除休眠状态
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

Mpu6050Data Mpu6050Read()
{
	Mpu6050Data mpudata;
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



float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
Quaternion MpuToQuaternion(Mpu6050Data * mpu6050data)
{
	float gx = mpu6050data->gyro.x / FS_SEL;
	float gy = mpu6050data->gyro.y / FS_SEL;
	float gz = mpu6050data->gyro.z / FS_SEL;
	float az = mpu6050data->accel.z / AFS_SEL;
	float ax = mpu6050data->accel.x / AFS_SEL;
	float ay = mpu6050data->accel.y / AFS_SEL;

	float recipNorm;
    float s0, s1, s2, s3;
    float qDot1, qDot2, qDot3, qDot4;
    float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	volatile Quaternion quaternion = { 1.0f, 0.0f, 0.0f, 0.0f };

    // Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-quaternion.q1 * gx - quaternion.q2 * gy - quaternion.q3 * gz);
	qDot2 = 0.5f * (quaternion.q0 * gx + quaternion.q2 * gz - quaternion.q3 * gy);
	qDot3 = 0.5f * (quaternion.q0 * gy - quaternion.q1 * gz + quaternion.q3 * gx);
	qDot4 = 0.5f * (quaternion.q0 * gz + quaternion.q1 * gy - quaternion.q2 * gx);

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;   

        // Auxiliary variables to avoid repeated arithmetic
        _2q0 = 2.0f * quaternion.q0;
        _2q1 = 2.0f * quaternion.q1;
        _2q2 = 2.0f * quaternion.q2;
        _2q3 = 2.0f * quaternion.q3;
        _4q0 = 4.0f * quaternion.q0;
        _4q1 = 4.0f * quaternion.q1;
        _4q2 = 4.0f * quaternion.q2;
        _8q1 = 8.0f * quaternion.q1;
        _8q2 = 8.0f * quaternion.q2;

        q0q0 = quaternion.q0 * quaternion.q0;
        q1q1 = quaternion.q1 * quaternion.q1;
        q2q2 = quaternion.q2 * quaternion.q2;
        q3q3 = quaternion.q3 * quaternion.q3;

        // Gradient decent algorithm corrective step
        s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * quaternion.q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * quaternion.q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * quaternion.q3 - _2q1 * ax + 4.0f * q2q2 * quaternion.q3 - _2q2 * ay;

        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude

        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        qDot1 -= betaDef * s0;
        qDot2 -= betaDef * s1;
        qDot3 -= betaDef * s2;
        qDot4 -= betaDef * s3;

    }

    // Integrate rate of change of quaternion to yield quaternion
	quaternion.q0 += qDot1 * (1.0f / sampleFreq);
	quaternion.q1 += qDot2 * (1.0f / sampleFreq);
	quaternion.q2 += qDot3 * (1.0f / sampleFreq);
	quaternion.q3 += qDot4 * (1.0f / sampleFreq);

    // Normalise quaternion
	recipNorm = invSqrt(quaternion.q0 * quaternion.q0 
		+ quaternion.q1 * quaternion.q1 
		+ quaternion.q2 * quaternion.q2 
		+ quaternion.q3 * quaternion.q3);

	quaternion.q0 *= recipNorm;
	quaternion.q1 *= recipNorm;
	quaternion.q2 *= recipNorm;
	quaternion.q3 *= recipNorm;


	return quaternion;
}


