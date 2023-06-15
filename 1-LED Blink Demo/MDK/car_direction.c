#include "headfile.h"
#include "MOTOR.h"
#include "KEY.h"
#include "math.h"
#include "parameter.h"


#define DIR1 P35 //左
#define DIR2 P07 //右

void motor_direction_control()
{
	   /*速度环*/
	if(DIR1==1)//左
	{
		L_pluse=ctimer_count_read(CTIM0_P34);

	}
	else
	{
		L_pluse=-1*ctimer_count_read(CTIM0_P34);

	}
	ctimer_count_clean(CTIM0_P34);
	if(DIR2==1)//右
	{
		R_pluse=-1*ctimer_count_read(CTIM3_P04);

	}
	else
	{
		R_pluse=ctimer_count_read(CTIM3_P04);

	}
	ctimer_count_clean(CTIM3_P04);
	if(L_out+R_out>=700&&fabs(dir_err_sum)<10)
	{
	err_speed[0]=duty_high-(L_pluse+R_pluse)/4;
	}	
	else
	{
	err_speed[0]=duty_low-(L_pluse+R_pluse)/4;
	}
    //积分分离
	//抗积分饱和
	if(speed_Integral>=Integral_max)
		if(err_speed[0]<0)
	       speed_Integral+=err_speed[0];
	if(speed_Integral<=Integral_min)
		if(err_speed[0]>0)
	       speed_Integral+=err_speed[0];
	real_speed=err_speed[0]*speed_KP+speed_KI*speed_Integral;
	if(speed_Integral>Integral_max)
		speed_Integral=Integral_max;
	if(speed_Integral<Integral_min)
		speed_Integral=Integral_min;
	if(real_speed>speed_max)
	{
		real_speed=speed_max;
	}
    err_speed[1]=err_speed[0];
	c=real_speed;
//  b1=R_real_speed;	
    printf("c=%d\r\n",c);
}
//void steering_direction_control(float err)
//{   
//	err_end=(int)(steer_KP*err+steer_KD*(err-last_err));		
//	steering_angle(err_end);
//	last_err=err;
//}