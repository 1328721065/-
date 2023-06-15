#include "headfile.h"

uint16 L_out_ei=0,L_in_ei=0,R_out_ei=0,R_in_ei=0,R_ba_ei=0,L_ba_ei=0;//左、右电感采集信号
uint16 sum=0;
int i=0,j=0,temp=0,k=0;
uint16 ei[11],ei1[4],ei_sum=0;
int lastexchange=0,confirm=1,sortborder=9;
/*左外电感采集*/
uint16 EI_L_out_dispose()
{
	/*中值平均滤波*/
	/*左水平电感采集*/
	for(i=0;i<10;i++) 
	{
		for(k=0;k<3;k++)
		{
			ei1[k]=adc_once(ADC_P14, ADC_10BIT);
			ei_sum+=ei1[k];
		}
        ei[i]=ei_sum/3;
		ei_sum=0;
		if(ei[i]>=1023) ei[i]=1023;
		else if(ei[i]<=0)	ei[i]=0;
	}
	for(i=0;i<10;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	L_out_ei=sum/8;
	sum=0;
	return L_out_ei;
}	
/*右外电感采集*/
uint16 EI_R_out_dispose()
{
	for(i=0;i<10;i++) 
	{
		for(k=0;k<3;k++)
		{
			ei1[k]=adc_once(ADC_P01, ADC_10BIT);
			ei_sum+=ei1[k];
		}
        ei[i]=ei_sum/3;
		ei_sum=0;
		if(ei[i]>=1023) ei[i]=1023;
		else if(ei[i]<=0)	ei[i]=0;
	}
	for(i=0;i<10;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	R_out_ei=sum/8;
	sum=0;
	return R_out_ei;
}

/*左内电感采集*/
uint16 EI_L_in_dispose()
{ 
	/*中值平均滤波*/
	/*左八字电感采集*/
	for(i=0;i<10;i++) 
	{
        ei[i]=adc_once(ADC_P11, ADC_10BIT);
		if(ei[i]>1024) ei[i]=1024;
		else if(ei[i]<0)	ei[i]=0;
	}
	for(i=0;i<10;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	L_in_ei=sum/8;
	sum=0;
	return L_in_ei;
}
/*右内字电感采集*/
uint16 EI_R_in_dispose()	
{
	   for(i=0;i<10;i++) 
	{
        ei[i]=adc_once(ADC_P06, ADC_10BIT);
		if(ei[i]>1024) ei[i]=1024;
		else if(ei[i]<0)	ei[i]=0;
	}
	for(i=0;i<9;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	R_in_ei=sum/8;
	sum=0;
	return R_in_ei;
}
/*右八字电感采集*/
uint16 EI_R_ba_dispose()	
{
	   for(i=0;i<10;i++) 
	{
        ei[i]=adc_once(ADC_P05, ADC_10BIT);
		if(ei[i]>1024) ei[i]=1024;
		else if(ei[i]<0)	ei[i]=0;
	}
	for(i=0;i<9;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	R_ba_ei=sum/8;
	sum=0;
	return R_ba_ei;
}
/*左八字电感采集*/
uint16 EI_L_ba_dispose()	
{
	   for(i=0;i<10;i++) 
	{
        ei[i]=adc_once(ADC_P15, ADC_10BIT);
		if(ei[i]>1024) ei[i]=1024;
		else if(ei[i]<0)	ei[i]=0;
	}
	for(i=0;i<9;i++)
	{
		confirm=1;
		for(j=0;j<sortborder;j++)
		{
			if(ei[j]>ei[j+1])
			{
			confirm=0;
  			temp=ei[j];
            ei[j]=ei[j+1];
            ei[j+1]=temp;
            lastexchange=j;	
			}				
		}
		sortborder=lastexchange;
		if(confirm)
		break;
	}
	for(i=1;i<9;i++)
	{
		sum+=ei[i];
	}
	L_ba_ei=sum/8;
	sum=0;
	return L_ba_ei;
}
	