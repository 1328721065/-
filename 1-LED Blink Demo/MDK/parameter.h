#include "headfile.h"
#ifndef _parameter_h
#define _parameter_h

extern uint16 L_out,L_in,R_out,R_in,L_ba,R_ba;//���ҵ�вɼ��ź�

extern float turn_KP_low,turn_KD_low,turn_KP_high,turn_KD_high;//ת��
extern float dir_err_sum,dir_last_err,dir_in_sum,err_sum,err_cha,dir_err_ba,dir_last_ba,dir_in_ba;//���
extern uint8 ting,flag1,flag2,m,n,p,begin,count,round_control;//��־λ
extern uint8 choose_out,choose_in,choose_turn,key_control;//��������

extern int L_pluse,R_pluse;//������������
extern int real_speed;//��������ʵ�ٶ�
extern int duty_high,duty_low,dutyL,dutyR,high;//�������

extern float speed_KP,speed_KI,speed_KD;//�ٶȻ�

extern float angle;//�����ǽǶ�
extern float angle_KP;//�ǶȻ�
extern float speed_Integral,Integral_max,Integral_min;//�ٶȻ���

extern uint16 limit,a;//�����޷�
extern int speed_max;//�����޷�
extern int	c,d;//���ڱ�־λ
extern float err;//�ٶ����

extern int err_speed[3];//��ǰ���ϴΣ����ϴ�
#endif