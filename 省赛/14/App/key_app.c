#include "key_app.h"
uint8_t key_down=0;
uint8_t key_up=0;
uint8_t key_old=0;
uint8_t key_val=0;
uint8_t para[2]={1,1};
uint8_t index=0;
uint8_t recd_N=0;
float recd_MH=0;
float recd_ML=0;
//float recd_MH_max=0;
//float recd_ML_max=0;
uint8_t duty_lock_flag=0;
uint32_t key_tick=0;
uint32_t output_tick=0;
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
uint8_t keymode;
void key_proc(void)
{
	key_val=key_read();
	key_down=key_val&(key_val^key_old);
	key_up=~key_val&(key_val^key_old);
	key_old=key_val;

	switch(key_down)
	{
		case 1:
			index=0;
			if(++lcdmode==3)
				lcdmode=0;
		break;
			
		case 2:
			if(lcdmode==0)
			{
				if(uwTick - output_tick >= 5000 || output_tick == 0)
        {
          lcdmode_data ^= 1;
          max_high=max_low;
          output_tick = uwTick;
          recd_N++;
        }
			}

			if(lcdmode==1)
			{
				index^=1;
			}
		break;
			
		case 3://¼Ó
			if(lcdmode==1)
			{
				if(++para[index]==11)
					para[index]=1;
			}
		break;
			
		case 4://¼õ
			if(lcdmode==0)
				key_tick = uwTick;

			if(lcdmode==1)
			{
				if(--para[index]==0)
					para[index]=10;
			}
		break;
	}
	
	if(lcdmode==0)
	{
		if(key_up==4)
		{
			if(uwTick-key_tick>2000)
			{
				if(lcdmode==0 && duty_lock_flag==0)
					duty_lock_flag=1;
			}
			else
			{
				if(lcdmode==0 && duty_lock_flag==1)
					duty_lock_flag=0;
			}
		}
	}
}
