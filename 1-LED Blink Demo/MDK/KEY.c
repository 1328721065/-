#include "headfile.h"
#include "zf_delay.h"
/*
P35:ȷ��
P36:����
P37:����
P70:����
P71:����
*/

uint8 key_choose()
{
	uint8 num=0;
	if(P40==0) {delay_ms(10);while(P40==0);delay_ms(10);num=1;}
	if(P41==0) {delay_ms(10);while(P41==0);delay_ms(10);num=2;}
	if(P42==0) {delay_ms(10);while(P42==0);delay_ms(10);num=3;}
	if(P43==0) {delay_ms(10);while(P43==0);delay_ms(10);num=4;}
	if(P44==0) {delay_ms(10);while(P44==0);delay_ms(10);num=5;}
	if(P45==0) {delay_ms(10);while(P45==0);delay_ms(10);num=6;}
	if(P46==0) {delay_ms(10);while(P46==0);delay_ms(10);num=7;}
	return num;
}