#include "parameter.h"
#include "headfile.h"

uint16 L_out=0,L_in=0,R_out=0,R_in=0,L_ba=0,R_ba=0;//���ҵ�вɼ��ź�

float turn_KP_low=45,turn_KD_low=850,turn_KP_high=45,turn_KD_high=900;//ת��
float dir_err_sum=0,dir_last_err=0,dir_in_sum=0,err_sum=0,err_cha=0,dir_err_ba=0,dir_last_ba=0,dir_in_ba=0;//ת�����
uint8 ting=0,flag1=0,flag2=0,m=0,n,p=0,begin=0,count=0,round_control=0;//��־λ
uint8 choose_out=0,choose_in=0,choose_turn=0,key_control=0;//��������

int L_pluse=0,R_pluse=0;//������������
int real_speed=0;//��������ʵ�ٶ�
int duty_high=310,duty_low=340,dutyL=0,dutyR=0,high=500;//�������

float speed_KP=2.0,speed_KI=0.35,speed_KD=0;//�ٶȻ�

float angle=0;//�����ǽǶ�
float angle_KP=0;//�ǶȻ�
float speed_Integral=0,Integral_max=1000,Integral_min=-1000;//�ٶȻ���

uint16 limit=4;//�����޷�

int speed_max=500;//�����޷�
int	c=0,d=0;//���ڱ�־λ
float err=0;//�ٶ����

int err_speed[3]={0,0};//��ǰ���ϴΣ����ϴ�