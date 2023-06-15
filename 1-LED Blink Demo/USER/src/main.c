/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"
#include "MOTOR.h"
#include "math.h"
#include "dispose.h"
#include "car_direction.h"
#include "KEY.h"
#include "parameter.h"
#include "round.h"
#include "dir_control.h"
/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
//uint16 L_out_max=1024,L_out_min=0; //左侧外电感极限值
//uint16 R_out_max=1024,R_out_min=0; //右侧外电感极限值
//uint16 L_in_max=1024,L_in_min=0; //左侧内电感极限值
//uint16 R_in_max=1024,R_in_min=0; //右侧内电感极限值


void motor_out(int Lpwm,int Rpwm);
void oled_zhunbei();
void main()
{
	DisableGlobalIRQ();	//关闭总中断	
    //sys_clk可选值:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 30000000;     //设置系统频率为30MHz

	board_init();
	/*oled初始化*/
	oled_init();
	
//	gpio_mode(P5_1,GPO_PP);
	
	gpio_mode(P4_0,GPIO);//五个按键设置为准双向模式
	gpio_mode(P4_1,GPIO);
	gpio_mode(P4_2,GPIO);
	gpio_mode(P4_3,GPIO);
	gpio_mode(P4_4,GPIO);
	gpio_mode(P4_5,GPIO);
	gpio_mode(P4_6,GPIO);
	gpio_mode(P7_5,GPO_PP);
	P75=0;
	/*电机初始化*/
    pwm_init(PWMA_CH4P_P66, 15000, 0); //PWM1初始化 左后轮正转
	pwm_init(PWMA_CH1P_P60, 15000, 0); //PMW2初始化 左后轮反转
	pwm_init(PWMA_CH3P_P64, 15000, 0); //PWM3初始化 右后轮正转
	pwm_init(PWMA_CH2P_P62, 15000, 0); //PWM4初始化 右后轮反转
	/*编码器初始化*/
	ctimer_count_init(CTIM0_P34);
	ctimer_count_init(CTIM3_P04);	
	/*陀螺仪初始化*/
	/*ADC初始化*/
	adc_init(ADC_P14,ADC_SYSclk_DIV_2); //左外电感
//	adc_init(ADC_P11,ADC_SYSclk_DIV_2);	//左内电感
//	adc_init(ADC_P06,ADC_SYSclk_DIV_2); //右内电感
	adc_init(ADC_P01,ADC_SYSclk_DIV_2); //右外电感
	adc_init(ADC_P15,ADC_SYSclk_DIV_2); //左八字电感
	adc_init(ADC_P05,ADC_SYSclk_DIV_2); //右八字电感
//	adc_init(ADC_P13,ADC_SYSclk_DIV_2); //左竖电感
//	adc_init(ADC_P10,ADC_SYSclk_DIV_2); //右竖电感
	/*分别寻找左、右电感最大值*/
//    scan();
    oled_zhunbei();
//	BEE=1;
//	delay_ms(1000);
//	BEE=0;
    //无线串口初始化
	uart_init(UART_4, UART4_RX_P02, UART4_TX_P03, 115200, TIM_2);
	/*定时器设置与中断优先级设置*/
//	NVIC_SetPriority(TIMER1_IRQn, 3);
	pit_timer_ms(TIM_4, 20); //初始化定时器1，周期为20ms
    pit_timer_ms(TIM_1, 5); // 初始化定时器2，周期为5ms
//	NVIC_SetPriority(TIMER1_IRQn, 3);
	EnableGlobalIRQ();//开启总中断
    while(1)
	{
	key_control=key_choose();
	if(key_control==1)
	{
	oled_fill(0x00);
	oled_p6x8str(8,2,"L-pluse:");
	oled_p6x8str(8,3,"R-pluse:");
	oled_p6x8str(8,4,"t_speed:");	
	      while(1)
	     {
		   key_control=key_choose();
           oled_uint16(8,0, L_out);
           oled_uint16(8,1, R_out);
		   oled_uint16(60,0, L_ba);
           oled_uint16(60,1, R_ba); 
           oled_int16(60,2,L_pluse);
		   oled_int16(60,3,R_pluse);
		   oled_int16(60,4,real_speed);
		   oled_printf_float(8,5,dir_err_ba,3,2); 
		   oled_printf_float(8,6,err_cha,3,2); 
	       oled_printf_float(8,7,dir_err_sum,3,1);
		   oled_int16(70, 6, dutyL);
		   oled_int16(70, 7, dutyR); 
			if(ting!=0)
	       {
		     motor_out(0,0);
		     DisableGlobalIRQ();	
		     while(1)
		    {
			   key_control=key_choose();
				if(key_control==7)
				{
					ting=0;
					key_control=0;
					EnableGlobalIRQ();
					break;
				}
		     }
	       }
			 if(key_control==3)
				 break;
	     } 
    }
	if(key_control==3)
	{
		oled_fill(0x00);
			while(1)
			{
			key_control=key_choose();
				if(key_control==1)
					break;
			}
	}
	}
}
void TM4_Isr() interrupt 20
{
    motor_direction_control();
}

void TM1_Isr() interrupt 3
{
//	count++;
	L_out=EI_L_out_dispose();
	R_out=EI_R_out_dispose();
	R_ba=EI_R_ba_dispose();
	L_ba=EI_L_ba_dispose();
	if(L_out<=70&&R_out<=70)
	{
		ting++;
	}
	dir_in_sum=(float)(L_out+R_out);
	dir_in_ba=(float)(L_ba+R_ba);
	dir_err_sum=1000*(float)(sqrt((float)L_out)-sqrt((float)R_out))/dir_in_sum;
	dir_err_ba=1000*(float)(sqrt((float)L_ba)-sqrt((float)R_ba))/dir_in_ba;
	if(p!=0)
	{
       round_set();
    }
	if(round_control==0)
	{
	if(L_out+R_out<=700&&fabs(dir_err_sum)<10)
	{
//		   P75=1;
		ba_control();
	}
	else
	{
//		P75=0;
        heng_control();
	}
    }
}
void oled_zhunbei()
{
	while(1)
	{
	oled_p6x8str(0,choose_out,">");
	oled_p6x8str(8,0,"t/s");
	oled_p6x8str(8,1,"round");
	oled_p6x8str(8,2,"fork");
    oled_p6x8str(8,3,"start");
	key_control=key_choose();
	if(key_control==1) {for(n=0;n<=6;n++) {oled_clrpixel(n,choose_out);}if(choose_out>0) choose_out--; }
	else if(key_control==3) {for(n=0;n<=6;n++) {oled_clrpixel(n,choose_out);}if(choose_out<3) choose_out++; }
	if(key_control==5)
	{
		oled_fill(0x00);
		m=0;
		key_control=0;
	switch(choose_out)
	{
		case 0:
			    oled_p6x8str(0,m,">");
				oled_p6x8str(8,0,"sKP:");
	            oled_p6x8str(8,1,"sKI:");
	            oled_p6x8str(8,2,"sKD:");
		        oled_p6x8str(8,3,"LKP:");
		        oled_p6x8str(8,4,"LKD:");
		        oled_p6x8str(8,5,"HKD:");
		        oled_p6x8str(8,6,"HKD:");
		        oled_p6x8str(8,7,"duty:");
		        oled_printf_float(40,0,speed_KP,1,3);
		        oled_printf_float(40,1,speed_KI,1,2);
		        oled_printf_float(40,2,speed_KD,2,1);
		        oled_printf_float(40,3,turn_KP_low,3,1);
		        oled_printf_float(40,4,turn_KD_low,4,1);
		        oled_printf_float(40,5,turn_KP_high,3,1);
		        oled_printf_float(40,6,turn_KD_high,4,1);
		        oled_int16(44,7,duty_high);
			    while(1)
			    {
				  choose_in=key_choose();
				  	if(choose_in!=0)
		           {
			         if(choose_in==1)
			         {
				       for(n=0;n<=6;n++) {oled_clrpixel(n,m);}	
				       if(m!=0) m--;
				       oled_p6x8str(0,m,">");
			         }
			         if(choose_in==3)
			         {
				     for(n=0;n<6;n++){oled_clrpixel(n,m);}
                     if(m<8) m++;
				     oled_p6x8str(0,m,">");
					 }
			         if(choose_in==4)
			         {
				      switch(m)
				     {
					    case 0:speed_KP+=0.1;oled_printf_float(40,0,speed_KP,1,3);break;
						case 1:speed_KI+=0.01;oled_printf_float(40,1,speed_KI,1,2);break; 
					    case 2:speed_KD+=1;oled_printf_float(40,2,speed_KD,3,1);break;
						case 3:turn_KP_low+=1;oled_printf_float(40,3,turn_KP_low,3,1);break;
						case 4:turn_KD_low+=5;oled_printf_float(40,4,turn_KD_low,4,1);break;
						case 5:turn_KP_high+=1;oled_printf_float(40,5,turn_KP_high,3,1);break;
						case 6:turn_KD_high+=5;oled_printf_float(40,6,turn_KD_high,4,1);break;
					    case 7:duty_high+=10;oled_int16(44,7,duty_high);break;
				     }
			         }
			         if(choose_in==2)
			         {
				     switch(m)
				     {
					    case 0:speed_KP-=0.1;oled_printf_float(40,0,speed_KP,1,3);break;
						case 1:speed_KI-=0.01;oled_printf_float(40,1,speed_KI,1,2);break; 
					    case 2:speed_KD-=1;oled_printf_float(40,2,speed_KD,3,1);break;
						case 3:turn_KP_low-=1;oled_printf_float(40,3,turn_KP_low,3,1);break;
						case 4:turn_KD_low-=5;oled_printf_float(40,4,turn_KD_low,4,1);break;
						case 5:turn_KP_high-=1;oled_printf_float(40,5,turn_KP_high,3,1);break;
						case 6:turn_KD_high-=5;oled_printf_float(40,6,turn_KD_high,4,1);break;
					    case 7:duty_high-=10;oled_int16(44,7,duty_high);break;
				     }
			         }
			       if(choose_in==5)
			       {
				   oled_fill(0x00);
				    choose_in=0;
                    m=0;					   
				   break;
			       }
		           }	
			    }
				break;
		 case 1:
			    oled_p6x8str(0,m,">");
				oled_p6x8str(8,0,"on/off:");
	            oled_p6x8str(8,1,"limit:");
		        oled_p6x8str(8,2,"high:");
		        oled_uint16(70,0,p);
		        oled_uint16(70,1,limit);
		        oled_int16(60,2,high);
		         while(1)
			    {
				  choose_in=key_choose();
				  	if(choose_in!=0)
		           {
			         if(choose_in==1)
			         {
				       for(n=0;n<=6;n++) {oled_clrpixel(n,m);}	
				       if(m!=0) m--;
				       oled_p6x8str(0,m,">");
			         }
			         if(choose_in==3)
			         {
				     for(n=0;n<6;n++){oled_clrpixel(n,m);}
                     if(m<4) m++;
				     oled_p6x8str(0,m,">");
					 }
			         if(choose_in==2)
			         {
				     switch(m)
				     {
						 case 0:p-=1;oled_uint16(70,0,p);break;
					     case 1:limit-=1;oled_uint16(70,1,limit);break;
						 case 2:high-=100; oled_int16(60,2,high);break;			     
					 }
			         }
					 if(choose_in==4)
			         {
				     switch(m)
				     {
						 case 0:p+=1;oled_uint16(70,0,p);break;
					     case 1:limit+=1;oled_uint16(70,1,limit);break;
						 case 2:high+=100; oled_int16(60,2,high);break;
				     }
			         }
			       if(choose_in==5)
			       {
				   oled_fill(0x00);
				    choose_in=0;
                    m=0;					   
				   break;
			       }
		           }	
			    }
				break;
		case 3:
			    oled_fill(0x00);
				begin=1;
		        break;
	}
    }
	if(begin!=0) break;
     }
}
	

//void scan()
//{
//	uint16 i,L_out_ei1=0,L_in_ei1=0,R_out_ei1=0,R_in_ei1=0;
//	for(i=0;i<1000;i++)  //左外电感
//	{
//	    L_out_ei1=adc_once(ADC_P00, ADC_10BIT);
//		if(L_out_max<=L_out_ei1)
//			L_out_max=L_out_ei1;
//		if(L_out_min>=L_out_ei1)
//			L_out_min=L_out_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //左内电感
//	{
//	    L_in_ei1=adc_once(ADC_P01, ADC_10BIT);
//		if(L_in_max<L_in_ei1)
//			L_in_max=L_in_ei1;
//		if(L_in_min>L_in_ei1)
//			L_in_min=L_in_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //右外电感
//	{
//	    R_out_ei1=adc_once(ADC_P06, ADC_10BIT);
//		if(R_out_max<R_out_ei1)
//			R_out_max=R_out_ei1;
//		if(R_out_min>R_out_ei1)
//			R_out_min=R_out_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //右内电感
//	{
//	    R_in_ei1=adc_once(ADC_P05, ADC_10BIT);
//		if(R_in_max<R_in_ei1)
//			R_in_max=R_in_ei1;
//		if(R_in_min>R_in_ei1)
//			R_in_min=R_in_ei1;
//	}
//}




