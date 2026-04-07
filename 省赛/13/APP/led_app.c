#include "led_app.h"
void led_proc(void)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15,SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,RESET);
	if(led1==1)
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,SET);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,RESET);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,RESET);
		if(uwTick-led1_tick>=5000)
		{
			led1=0;
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,RESET);
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,25);//设置CRR（占空比=CRR/(ARR+1)）（CRR=占空比*（ARR+1））
				HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE); 
		}
	}
	
	if(eeprom_read(0x00)==0&&eeprom_read(0x01)==0)
	{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,SET);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,RESET);
	}
	
}

