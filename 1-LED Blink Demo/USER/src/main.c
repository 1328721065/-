/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
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
 *�����ں�Ƶ�ʵ��趨�����Բ鿴board.h�ļ�
 *��board_init��,�Ѿ���P54��������Ϊ��λ
 *�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */
//uint16 L_out_max=1024,L_out_min=0; //������м���ֵ
//uint16 R_out_max=1024,R_out_min=0; //�Ҳ����м���ֵ
//uint16 L_in_max=1024,L_in_min=0; //����ڵ�м���ֵ
//uint16 R_in_max=1024,R_in_min=0; //�Ҳ��ڵ�м���ֵ


void motor_out(int Lpwm,int Rpwm);
void oled_zhunbei();
void main()
{
	DisableGlobalIRQ();	//�ر����ж�	
    //sys_clk��ѡֵ:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 30000000;     //����ϵͳƵ��Ϊ30MHz

	board_init();
	/*oled��ʼ��*/
	oled_init();
	
//	gpio_mode(P5_1,GPO_PP);
	
	gpio_mode(P4_0,GPIO);//�����������Ϊ׼˫��ģʽ
	gpio_mode(P4_1,GPIO);
	gpio_mode(P4_2,GPIO);
	gpio_mode(P4_3,GPIO);
	gpio_mode(P4_4,GPIO);
	gpio_mode(P4_5,GPIO);
	gpio_mode(P4_6,GPIO);
	gpio_mode(P7_5,GPO_PP);
	P75=0;
	/*�����ʼ��*/
    pwm_init(PWMA_CH4P_P66, 15000, 0); //PWM1��ʼ�� �������ת
	pwm_init(PWMA_CH1P_P60, 15000, 0); //PMW2��ʼ�� ����ַ�ת
	pwm_init(PWMA_CH3P_P64, 15000, 0); //PWM3��ʼ�� �Һ�����ת
	pwm_init(PWMA_CH2P_P62, 15000, 0); //PWM4��ʼ�� �Һ��ַ�ת
	/*��������ʼ��*/
	ctimer_count_init(CTIM0_P34);
	ctimer_count_init(CTIM3_P04);	
	/*�����ǳ�ʼ��*/
	/*ADC��ʼ��*/
	adc_init(ADC_P14,ADC_SYSclk_DIV_2); //������
//	adc_init(ADC_P11,ADC_SYSclk_DIV_2);	//���ڵ��
//	adc_init(ADC_P06,ADC_SYSclk_DIV_2); //���ڵ��
	adc_init(ADC_P01,ADC_SYSclk_DIV_2); //������
	adc_init(ADC_P15,ADC_SYSclk_DIV_2); //����ֵ��
	adc_init(ADC_P05,ADC_SYSclk_DIV_2); //�Ұ��ֵ��
//	adc_init(ADC_P13,ADC_SYSclk_DIV_2); //�������
//	adc_init(ADC_P10,ADC_SYSclk_DIV_2); //�������
	/*�ֱ�Ѱ�����ҵ�����ֵ*/
//    scan();
    oled_zhunbei();
//	BEE=1;
//	delay_ms(1000);
//	BEE=0;
    //���ߴ��ڳ�ʼ��
	uart_init(UART_4, UART4_RX_P02, UART4_TX_P03, 115200, TIM_2);
	/*��ʱ���������ж����ȼ�����*/
//	NVIC_SetPriority(TIMER1_IRQn, 3);
	pit_timer_ms(TIM_4, 20); //��ʼ����ʱ��1������Ϊ20ms
    pit_timer_ms(TIM_1, 5); // ��ʼ����ʱ��2������Ϊ5ms
//	NVIC_SetPriority(TIMER1_IRQn, 3);
	EnableGlobalIRQ();//�������ж�
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
//	for(i=0;i<1000;i++)  //������
//	{
//	    L_out_ei1=adc_once(ADC_P00, ADC_10BIT);
//		if(L_out_max<=L_out_ei1)
//			L_out_max=L_out_ei1;
//		if(L_out_min>=L_out_ei1)
//			L_out_min=L_out_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //���ڵ��
//	{
//	    L_in_ei1=adc_once(ADC_P01, ADC_10BIT);
//		if(L_in_max<L_in_ei1)
//			L_in_max=L_in_ei1;
//		if(L_in_min>L_in_ei1)
//			L_in_min=L_in_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //������
//	{
//	    R_out_ei1=adc_once(ADC_P06, ADC_10BIT);
//		if(R_out_max<R_out_ei1)
//			R_out_max=R_out_ei1;
//		if(R_out_min>R_out_ei1)
//			R_out_min=R_out_ei1;
//	}
//	
//		for(i=0;i<1000;i++) //���ڵ��
//	{
//	    R_in_ei1=adc_once(ADC_P05, ADC_10BIT);
//		if(R_in_max<R_in_ei1)
//			R_in_max=R_in_ei1;
//		if(R_in_min>R_in_ei1)
//			R_in_min=R_in_ei1;
//	}
//}




