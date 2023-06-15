#include "SEEKFREE_MPU6050.h"
#include "parameter.h"


void MPU_angle(void)
{
	angle=angle_KP*mpu_gyro_z+(1-angle_KP)*(angle+mpu_acc_z);
}