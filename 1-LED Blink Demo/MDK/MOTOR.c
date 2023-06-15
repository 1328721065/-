#include "headfile.h"


void motor_out(int Lpwm,int Rpwm)
{
	if(Lpwm>800) Lpwm=800;
	if(Rpwm>800) Rpwm=800;
	if(Lpwm<-800) Lpwm=-800;
	if(Rpwm<-800) Rpwm=-800;
	
	if(Lpwm>0)
	{
		pwm_duty(PWMA_CH2P_P62, 10*Lpwm);
		pwm_duty(PWMA_CH1P_P60, 0);
	}
	else
	{
	    pwm_duty(PWMA_CH2P_P62, 0);
		pwm_duty(PWMA_CH1P_P60, (-10)*Lpwm);
	}
	
		if(Rpwm>0)
	{
		pwm_duty(PWMA_CH3P_P64, Rpwm*10);
		pwm_duty(PWMA_CH4P_P66, 0);
	}
	else
	{
	    pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, (-10)*Rpwm);
	}
}