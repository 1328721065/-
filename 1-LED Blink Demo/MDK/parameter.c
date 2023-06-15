#include "parameter.h"
#include "headfile.h"

uint16 L_out=0,L_in=0,R_out=0,R_in=0,L_ba=0,R_ba=0;//左、右电感采集信号

float turn_KP_low=45,turn_KD_low=850,turn_KP_high=45,turn_KD_high=900;//转向环
float dir_err_sum=0,dir_last_err=0,dir_in_sum=0,err_sum=0,err_cha=0,dir_err_ba=0,dir_last_ba=0,dir_in_ba=0;//转向误差
uint8 ting=0,flag1=0,flag2=0,m=0,n,p=0,begin=0,count=0,round_control=0;//标志位
uint8 choose_out=0,choose_in=0,choose_turn=0,key_control=0;//按键控制

int L_pluse=0,R_pluse=0;//编码器脉冲数
int real_speed=0;//左右轮真实速度
int duty_high=310,duty_low=340,dutyL=0,dutyR=0,high=500;//电机驱动

float speed_KP=2.0,speed_KI=0.35,speed_KD=0;//速度环

float angle=0;//陀螺仪角度
float angle_KP=0;//角度环
float speed_Integral=0,Integral_max=1000,Integral_min=-1000;//速度积分

uint16 limit=4;//环岛限幅

int speed_max=500;//积分限幅
int	c=0,d=0;//串口标志位
float err=0;//速度误差

int err_speed[3]={0,0};//当前，上次，上上次