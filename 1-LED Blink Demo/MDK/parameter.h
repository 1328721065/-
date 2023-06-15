#include "headfile.h"
#ifndef _parameter_h
#define _parameter_h

extern uint16 L_out,L_in,R_out,R_in,L_ba,R_ba;//左、右电感采集信号

extern float turn_KP_low,turn_KD_low,turn_KP_high,turn_KD_high;//转向环
extern float dir_err_sum,dir_last_err,dir_in_sum,err_sum,err_cha,dir_err_ba,dir_last_ba,dir_in_ba;//误差
extern uint8 ting,flag1,flag2,m,n,p,begin,count,round_control;//标志位
extern uint8 choose_out,choose_in,choose_turn,key_control;//按键控制

extern int L_pluse,R_pluse;//编码器脉冲数
extern int real_speed;//左右轮真实速度
extern int duty_high,duty_low,dutyL,dutyR,high;//电机驱动

extern float speed_KP,speed_KI,speed_KD;//速度环

extern float angle;//陀螺仪角度
extern float angle_KP;//角度环
extern float speed_Integral,Integral_max,Integral_min;//速度积分

extern uint16 limit,a;//环岛限幅
extern int speed_max;//积分限幅
extern int	c,d;//串口标志位
extern float err;//速度误差

extern int err_speed[3];//当前，上次，上上次
#endif