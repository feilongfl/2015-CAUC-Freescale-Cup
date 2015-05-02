
#include "common.h"

#ifdef MK60F15
#include "MK60_i2c.h"
#else
#include "MKL_i2c.h"
#endif


#ifndef _MPU6050_H_
#define _MPU6050_H_

#define Mpu6050_I2C I2C0//定义mpu6050i2c接口
#define Mpu6050_I2C_Rate (100 * 1000)//定义I2C速度

#define AD0_HIGH 1
#define AD0_LOW  0

#define AD0_VOLTAGE AD0_LOW//AD0电压状态设置

//mpu6050器件地址设置
#if (AD0_VOLTAGE == AD0_LOW)
#define MpuAddress 0x68//i2caddress
#elif (AD0_VOLTAGE == AD0_HIGH)
#define MpuAddress 0x69//i2caddress
#else
#error please set your AD0 Voltage 
#endif

//MPU6050寄存器地址声明
#define	SELF_TEST_X			0x0D		//R / W			XA_TEST[4-2]
										//				XG_TEST[4-0]
#define	SELF_TEST_Y			0x0E		//R / W			YA_TEST[4-2]
										//				YG_TEST[4-0]
#define	SELF_TEST_Z			0x0F		//R / W			ZA_TEST[4-2]
										//				ZG_TEST[4-0]
#define	SELF_TEST_A			0x10		//R / W			RESERVED
										//				XA_TEST[1-0]
										//				YA_TEST[1-0]
										//				ZA_TEST[1-0]
#define	SMPLRT_DIV			0x19		//R / W			SMPLRT_DIV[7:0]
										//采样率=陀螺输出率/（1 + smplrt_div）
#define	CONFIG				0x1A		//R / W			（保留）
										//				（保留）
										//				EXT_SYNC_SET[2:0]
										//				DLPF_CFG[2:0]
#define	GYRO_CONFIG			0x1B		//R / W			（保留）
										//				（保留）
										//				（保留）
										//				FS_SEL [1:0]
										//				（保留）
										//				（保留）
										//				（保留）
#define	ACCEL_CONFIG		0x1C		//R / W			XA_ST
										//				YA_ST
										//				ZA_ST
										//				AFS_SEL[1:0]
#define	MOT_THR				0x1F		//R / W			MOT_THR[7:0]
#define	FIFO_EN				0x23		//R / W			TEMP_FIFO_EN
										//				XG_FIFO_EN
										//				YG_FIFO_EN
										//				ZG_FIFO_EN
										//				ACCEL_FIFO_EN
										//				SLV2_FIFO_EN
										//				SLV1_FIFO_EN
										//				SLV0_FIFO_EN
#define	I2C_MST_CTRL		0x24		//R / W			MULT_MST_EN
										//				WAIT_FOR_ES
										//				SLV_3_FIFO_EN
										//				I2C_MST_P_NSR
										//				I2C_MST_CLK[3:0]
#define	I2C_SLV0_ADDR		0x25		//R / W			I2C_SLV0_RW
										//				I2C_SLV0_ADDR[6:0]
#define	I2C_SLV0_REG		0x26		//R / W			I2C_SLV0_REG[7:0]
#define	I2C_SLV0_CTRL		0x27		//R / W			I2C_SLV0_EN
										//				I2C_SLV0_BYTE_SW
										//				I2C_SLV0_REG_DIS
										//				I2C_SLV0_GRP
										//				I2C_SLV0_LEN[3:0]
#define	I2C_SLV1_ADDR		0x28		//R / W			I2C_SLV1_RW
										//				I2C_SLV1_ADDR[6:0]
#define	I2C_SLV1_REG		0x29		//R / W			I2C_SLV1_REG[7:0]
#define	I2C_SLV1_CTRL		0x2A		//R / W			I2C_SLV1_EN
										//				I2C_SLV1_BYTE_SW
										//				I2C_SLV1_REG_DIS
										//				I2C_SLV1_GRP
										//				I2C_SLV1_LEN[3:0]
#define	I2C_SLV2_ADDR		0x2B		//R / W			I2C_SLV2_RW
										//				I2C_SLV2_ADDR[6:0]
#define	I2C_SLV2_REG		0x2C		//R / W			I2C_SLV2_REG[7:0]
#define	I2C_SLV2_CTRL		0x2D		//R / W			I2C_SLV2_EN
										//				I2C_SLV2_BYTE_SW
										//				I2C_SLV2_REG_DIS
										//				I2C_SLV2_GRP
										//				I2C_SLV2_LEN[3:0]
#define	I2C_SLV3_ADDR		0x2E		//R / W			I2C_SLV3_RW
										//				I2C_SLV3_ADDR[6:0]
#define	I2C_SLV3_REG		0x2F		//R / W			I2C_SLV3_REG[7:0]
#define	I2C_SLV3_CTRL		0x30		//R / W			I2C_SLV3_EN
										//				I2C_SLV3_BYTE_SW
										//				I2C_SLV3_REG_DIS
										//				I2C_SLV3_GRP
										//				I2C_SLV3_LEN[3:0]
#define	I2C_SLV4_ADDR		0x31		//R / W			I2C_SLV4_RW
										//				I2C_SLV4_ADDR[6:0]
#define	I2C_SLV4_REG		0x32		//R / W			I2C_SLV4_REG[7:0]
#define	I2C_SLV4_DO			0x33		//R / W			I2C_SLV4_DO[7:0]
#define	I2C_SLV4_CTRL		0x34		//R / W			I2C_SLV4_EN
										//				I2C_SLV4_INT_EN
										//				I2C_SLV4_REG_DIS
										//				I2C_MST_DLY[4:0]
#define	I2C_SLV4_DI			0x35		//				I2C_SLV4_DI[7:0]
#define	I2C_MST_STATUS		0x36		//				PASS_THROUGH
										//				I2C_SLV4_DONE
										//				I2C_LOST_ARB
										//				I2C_SLV4_NACK
										//				I2C_SLV3_NACK
										//				I2C_SLV2_NACK
										//				I2C_SLV1_NACK
										//				I2C_SLV0_NACK
#define	INT_PIN_CFG			0x37		//R / W			INT_LEVEL
										//				INT_OPEN
										//				LATCH_INT_EN
										//				INT_RD_CLEAR
										//				FSYNC_INT_LEVEL
										//				FSYNC_INT_EN
										//				I2C_BYPASS_EN
										//				（保留）
#define	INT_ENABLE			0x38		//R / W			（保留）
										//				MOT_EN
										//				（保留）
										//				FIFO_OFLOW_EN
										//				I2C_MST_INT_EN
										//				（保留）
										//				（保留）
										//				DATA_RDY_EN
#define	INT_STATUS			0x3A		//R				（保留）
										//				MOT_INT
										//				（保留）
										//				FIFO_OFLOW_INT
										//				I2C_MST_INT
										//				（保留）
										//				（保留）
										//				DATA_RDY_INT
#define	ACCEL_XOUT_H		0x3B		//R				ACCEL_XOUT[15:8]
#define	ACCEL_XOUT_L		0x3C		//R				ACCEL_XOUT[7:0]
#define	ACCEL_YOUT_H		0x3D		//R				ACCEL_YOUT[15:8]
#define	ACCEL_YOUT_L		0x3E		//R				ACCEL_YOUT[7:0]
#define	ACCEL_ZOUT_H		0x3F		//R				ACCEL_ZOUT[15:8]
#define	ACCEL_ZOUT_L		0x40		//R				ACCEL_ZOUT[7:0]
#define	TEMP_OUT_H			0x41		//R				TEMP_OUT[15:8]
#define	TEMP_OUT_L			0x42		//R				TEMP_OUT[7:0]
										//Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
#define	GYRO_XOUT_H			0x43		//R				GYRO_XOUT[15:8]
#define	GYRO_XOUT_L			0x44		//R				GYRO_XOUT[7:0]
#define	GYRO_YOUT_H			0x45		//R				GYRO_YOUT[15:8]
#define	GYRO_YOUT_L			0x46		//R				GYRO_YOUT[7:0]
#define	GYRO_ZOUT_H			0x47		//R				GYRO_ZOUT[15:8]
#define	GYRO_ZOUT_L			0x48		//R				GYRO_ZOUT[7:0]
#define	EXT_SENS_DATA_00	0x49		//R				EXT_SENS_DATA_00[7:0]
#define	EXT_SENS_DATA_01	0x4A		//R				EXT_SENS_DATA_01[7:0]
#define	EXT_SENS_DATA_02	0x4B		//R				EXT_SENS_DATA_02[7:0]
#define	EXT_SENS_DATA_03	0x4C		//R				EXT_SENS_DATA_03[7:0]
#define	EXT_SENS_DATA_04	0x4D		//R				EXT_SENS_DATA_04[7:0]
#define	EXT_SENS_DATA_05	0x4E		//R				EXT_SENS_DATA_05[7:0]
#define	EXT_SENS_DATA_06	0x4F		//R				EXT_SENS_DATA_06[7:0]
#define	EXT_SENS_DATA_07	0x50		//R				EXT_SENS_DATA_07[7:0]
#define	EXT_SENS_DATA_08	0x51		//R				EXT_SENS_DATA_08[7:0]
#define	EXT_SENS_DATA_09	0x52		//R				EXT_SENS_DATA_09[7:0]
#define	EXT_SENS_DATA_10	0x53		//R				EXT_SENS_DATA_10[7:0]
#define	EXT_SENS_DATA_11	0x54		//R				EXT_SENS_DATA_11[7:0]
#define	EXT_SENS_DATA_12	0x55		//R				EXT_SENS_DATA_12[7:0]
#define	EXT_SENS_DATA_13	0x56		//R				EXT_SENS_DATA_13[7:0]
#define	EXT_SENS_DATA_14	0x57		//R				EXT_SENS_DATA_14[7:0]
#define	EXT_SENS_DATA_15	0x58		//R				EXT_SENS_DATA_15[7:0]
#define	EXT_SENS_DATA_16	0x59		//R				EXT_SENS_DATA_16[7:0]
#define	EXT_SENS_DATA_17	0x5A		//R				EXT_SENS_DATA_17[7:0]
#define	EXT_SENS_DATA_18	0x5B		//R				EXT_SENS_DATA_18[7:0]
#define	EXT_SENS_DATA_19	0x5C		//R				EXT_SENS_DATA_19[7:0]
#define	EXT_SENS_DATA_20	0x5D		//R				EXT_SENS_DATA_20[7:0]
#define	EXT_SENS_DATA_21	0x5E		//R				EXT_SENS_DATA_21[7:0]
#define	EXT_SENS_DATA_22	0x5F		//R				EXT_SENS_DATA_22[7:0]
#define	EXT_SENS_DATA_23	0x60		//R				EXT_SENS_DATA_23[7:0]
#define	I2C_SLV0_DO			0x63		//R / W			I2C_SLV0_DO[7:0]
#define	I2C_SLV1_DO			0x64		//R / W			I2C_SLV1_DO[7:0]
#define	I2C_SLV2_DO			0x65		//R / W			I2C_SLV2_DO[7:0]
#define	I2C_SLV3_DO			0x66		//R / W			I2C_SLV3_DO[7:0]
#define	I2C_MST_DELAY_CTRL	0x67		//R / W			DELAY_ES_SHADOW
										//				（保留）
										//				（保留）
										//				I2C_SLV4_DLY_EN
										//				I2C_SLV3_DLY_EN
										//				I2C_SLV2_DLY_EN
										//				I2C_SLV1_DLY_EN
										//				I2C_SLV0_DLY_EN
#define	SIGNAL_PATH_RESET	0x68		//R / W			（保留）
										//				（保留）
										//				（保留）
										//				（保留）
										//				（保留）
										//				GYRO_RESET
										//				ACCEL_RESET
										//				TEMP_RESET
#define	MOT_DETECT_CTRL		0x69		//R / W			（保留）
										//				（保留）
										//				ACCEL_ON_DELAY[1:0]
										//				（保留）
										//				（保留）
#define	USER_CTRL			0x6A		//R / W			（保留）
										//				FIFO_EN
										//				I2C_MST_EN
										//				I2C_IF_DIS
										//				（保留）
										//				FIFO_RESET
										//				I2C_MST_RESET
										//				SIG_COND_RESET
#define	PWR_MGMT_1			0x6B		//R / W			电源管理，上电应写入0x00,默认0x40
										//				DEVICE_RESET
										//				SLEEP
										//				CYCLE
										//				（保留）
										//				TEMP_DIS
										//				CLKSEL[2:0]
#define	PWR_MGMT_2			0x6C		//R / W			LP_WAKE_CTRL[1:0]
										//				STBY_XA
										//				STBY_YA
										//				STBY_ZA
										//				STBY_XG
										//				STBY_YG
										//				STBY_ZG
#define	FIFO_COUNTH			0x72		//R / W			FIFO_COUNT[15:8]
#define	FIFO_COUNTL			0x73		//R / W			FIFO_COUNT[7:0]
#define	FIFO_R_W			0x74		//R / W			FIFO_DATA[7:0]
#define	WHO_AM_I			0x75		//R				（保留）
										//W				HO_AM_I[6:1]
										//				（保留）


#define FS_SEL_250 131
#define FS_SEL_500 65.5
#define FS_SEL_1000 32.8
#define FS_SEL_2000 16.4

#define FS_SEL FS_SEL_2000//陀螺仪精度

#define AFS_SEL_2 16384
#define AFS_SEL_4 8192
#define AFS_SEL_8 4096
#define AFS_SEL_16 2048

#define AFS_SEL AFS_SEL_16


//////////////////////////////////////////////////////////////////////////
//		/*正则*/
//		
//		//\b(\w+)\r\n(\d+)\r\n(\w+)\r\n(R / W|R/W|R|W|-)\r\n
//		//#define\t$3\t0x$1\t\t//$4\t
//////////////////////////////////////////////////////////////////////////

#define Mpu6050WriteReg(reg,data)  i2c_write_reg(Mpu6050_I2C,MpuAddress,reg,data)
#define Mpu6050ReadReg(reg)  i2c_read_reg(Mpu6050_I2C,MpuAddress,reg)


#define Mpu6050I2cMasterRead (1 << 7)
#define Mpu6050I2cMasterWrite (0 << 7)

struct Accel
{
	int16 x, y, z;
};

struct Gyro
{
	int16 x, y, z;
};

struct Mpu6050Data 
{
	struct Accel accel;
	int16 Temp;
	struct Gyro gyro;
};


#define sampleFreq    512.0f        // sample frequency in Hz
#define betaDef        0.1f        // 2 * proportional gain

typedef struct
{
	volatile float q0;
	volatile float q1;
	volatile float q2;
	volatile float q3;
}Quaternion;

Quaternion MpuToQuaternion(struct Mpu6050Data * mpu6050data);

#endif//_MPU6050_H_