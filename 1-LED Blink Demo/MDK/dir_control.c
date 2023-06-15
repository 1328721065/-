#include "headfile.h"
#include "parameter.h"
#include "MOTOR.h"


void heng_control()
{
	err_cha=dir_err_sum-dir_last_err;
	err_sum=dir_err_sum*turn_KP_low+err_cha*turn_KD_low;
	dir_last_err=dir_err_sum;
	dutyL=real_speed-err_sum;
	dutyR=real_speed+err_sum;
	motor_out(dutyL,dutyR);
}

void ba_control()
{
    err_cha=dir_err_ba-dir_last_ba;
	err_sum=dir_err_ba*turn_KP_high+err_cha*turn_KD_high;
    dir_last_ba=dir_err_ba;
	dutyL=real_speed-err_sum;					
	dutyR=real_speed+err_sum;
    motor_out(dutyL,dutyR);
}