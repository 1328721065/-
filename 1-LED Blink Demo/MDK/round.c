#include "headfile.h"
#include "parameter.h"
#include "MOTOR.h"
#include "math.h"
#include "dir_control.h"

int round_err=0;

void round_set()
{	
	if((L_out+R_out)>=1750)
	{
		round_control=1;
		flag1++;
	}
    if(flag1!=0)
	{
        if(p==1)
		{
			if(fabs(L_out-R_out)>=(limit*50))
			{
				DisableGlobalIRQ();
				motor_out(-400,700);
				delay_ms(high);
				EnableGlobalIRQ();
			}
		}
		 if(p==2)
		{
			if(fabs(L_out-R_out)>=(limit*50))
			{
				DisableGlobalIRQ();
				motor_out(700,-400);
				delay_ms(high);
				EnableGlobalIRQ();
			}
		}
	}
	if(fabs(L_out-R_out)>=350&&(L_out+R_out)<=1200)
	{
		flag2++;
		flag1=0;
	}
	if(flag2!=0)
	{		
		heng_control();
	}
	if(p==1)
	{
		if(L_out-R_out>=400)
		{
			P75=1;
			p=0;
			round_control=0;
			P75=0;
		}
	}
	if(p==2)
	{
		if(R_out-L_out>=400)
		{
			P75=1;
			p=0;
			round_control=0;
			P75=0;
		}
	}

}