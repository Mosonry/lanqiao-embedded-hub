#include "adc_app.h"
uint32_t dma_buff[2][30];
float adc_value[2];
float CCR_L;
float CCR_H;
uint32_t pwm_tick;//PWM计时器
uint16_t freq_val = 4000;//PWM频率值
uint8_t led_s=0;
uint32_t arr;
uint32_t ccr;
void adc_proc(void)
{
	for(uint8_t i=0;i<30;i++)
	{
		adc_value[0]+=(float)dma_buff[0][i];
		adc_value[1]+=(float)dma_buff[1][i];
	}
	adc_value[0]=adc_value[0]/30*3.3f/4096;
	adc_value[1]=adc_value[1]/30*3.3f/4096;
	if(duty_lock_flag==0)
	{
		if(adc_value[0]>0.0f && adc_value[0]<1.0f)
			duty=10;
		if(adc_value[0]>3.0f)
			duty=85;
		if(adc_value[0]>1.0f && adc_value[0]<3.0f)
		{
			duty=(adc_value[0]-1)*37.5f+10;	
		}
		arr=1000000/freq_val-1;
		ccr=(duty*1000000/freq_val)/100;
		__HAL_TIM_SET_AUTORELOAD(&htim2,arr);//设置ARR,pa1
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,ccr);//设置CRR（占空比=CRR/(ARR+1)）（CRR=占空比*（ARR+1） pa1
		//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE);
	}
	if((uint32_t)(uwTick - pwm_tick) >=100)
    {
				if(freq_val !=8000 && lcdmode_data==1)
				{
					led_s=1;
					freq_val += 110;
					arr=1000000/freq_val-1;
					ccr=(duty*1000000/freq_val)/100;
					if(freq_val>=8000)
						freq_val=8000;
					__HAL_TIM_SET_AUTORELOAD(&htim2,arr);//设置ARR
					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,ccr);//设置CRR（占空比=CRR/(ARR+1)）（CRR=占空比*（ARR+1））
					HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE); //
				}
				else if(freq_val !=4000 && lcdmode_data==0)//处于高频转低频
				{
					led_s=1;
					freq_val -= 110;
					arr=1000000/freq_val-1;
					ccr=(duty*1000000/freq_val)/100;
					if(freq_val<=4000)
						freq_val=4000;
					__HAL_TIM_SET_AUTORELOAD(&htim2,arr);//设置ARR
					__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,ccr);//设置CRR（占空比=CRR/(ARR+1)）（CRR=占空比*（ARR+1））
					HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE); 
				}
				else
				{
					led_s=0;
				}
        pwm_tick = uwTick;
				
    }
	
}

