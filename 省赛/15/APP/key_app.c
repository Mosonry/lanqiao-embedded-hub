#include "key_app.h"

uint8_t key_val=0;
uint8_t key_down=0;
uint8_t key_up=0;
uint8_t key_old=0;

uint8_t key_read(void)
{
	uint8_t temp=0;
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET)
		temp=1;
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET)
		temp=2;
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==GPIO_PIN_RESET)
		temp=3;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
		temp=4;
	return temp;
}

uint8_t para_index=0;
uint32_t key_tick=0;

void key_proc(void)
{
	key_val=key_read();
	key_down=key_val&(key_old^key_val);
	key_up=~key_val&(key_old^key_val);
	key_old=key_val;
	
	if(lcdmode==2)
	{
		if(key_down==3)
			key_tick=uwTick;
		else if(key_up==3)
		{	
			if(uwTick-key_tick>=1000)
			{
				key_tick=uwTick;
				memset(recd_arr,0,sizeof(recd_arr));
			}
		}
	}
	
	switch(key_down)
	{
		case 1:
			if(lcdmode==1)
			{
				para_arr[para_index]+=100;
				if(para_arr[para_index]>=para_min_max[1][para_index])
				{
					para_arr[para_index]=para_min_max[1][para_index];//限定的最大值
				}
			}
		break;
			
		case 2:
			if(lcdmode==1)
			{
				para_arr[para_index]-=100;
				if(para_arr[para_index]<=para_min_max[0][para_index])
				{
					para_arr[para_index]=para_min_max[0][para_index];//限定的最小值
				}
			}
			break;
			
		case 3:
			if(lcdmode==1)
			{
				if(++para_index==3)
					para_index=0;
			}
			else if(lcdmode==0)
			{
					data_lcdmode^=1;
			}
			break;
			
			case 4:
				if(++lcdmode==3)
				{
					data_lcdmode=para_index=0;
					LCD_DisplayStringLine(Line5,"                 ");
					LCD_DisplayStringLine(Line6,"                 ");
					lcdmode=0;
				}
			
	}
	
}

