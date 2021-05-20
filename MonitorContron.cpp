#include <Wire.h>
struct Montior
{
	const int MpuAddress = 0x68;
	// I2C address of the MPU-6050
	const double Gravity = 2 * 9.8;
	const double DefaultAngle = 250;
	double Acceleration[3];
	int Tempature;
	double AngularSpeed[3];

	void init()
	{
		Wire.begin();
		Wire.beginTransmission(MpuAddress);
		Wire.write(0x6B);
		// PWR_MGMT_1 register
		Wire.write(0);
		// set to zero (wakes up the MPU-6050)
		Wire.endTransmission(true);
	}

	void Measure()
	{
		Wire.beginTransmission(MpuAddress);
		Wire.write(0x3B);
		// starting with register 0x3B (ACCEL_XOUT_H)
		Wire.endTransmission(false);
		Wire.requestFrom(MpuAddress, 14, true);
		// request a total of 14 registers

		Acceleration[0] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * Gravity;
		// 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
		Acceleration[1] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * Gravity;
		// 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
		Acceleration[2] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * Gravity;
		// 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

		Tempature = (double)(Wire.read() << 8 | Wire.read()) / 340.0 + 36.53;
		// 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

		AngularSpeed[0] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * DefaultAngle;
		// 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
		AngularSpeed[1] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * DefaultAngle;
		// 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
		AngularSpeed[2] = (double)(Wire.read() << 8 | Wire.read()) / 32768.0 * DefaultAngle;
		// 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
	}
};
