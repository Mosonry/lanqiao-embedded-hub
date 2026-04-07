#include "key_app.h"
uint8_t key_old=0;
uint8_t key_up=0;
uint8_t key_down=0;
uint8_t key_val=0;

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
uint8_t r_shop_X;
uint8_t r_shop_Y;
float r_prise_X;
float r_prise_Y;
uint8_t r_rep_X;
uint8_t r_rep_Y;
char shop_buff[50];
float prise_all;
uint8_t led1=0;
uint32_t led1_tick;
void key_proc(void)
{
	key_val=key_read();
	key_up=key_val&(key_val^key_old);
	key_down=~key_val&(key_val^key_old);
	key_old=key_val;
	switch(key_down)
	{
		case 1:
			if(++lcdmode==3)
				lcdmode=0;
		break;
			
		case 2:
			if(lcdmode==0)
			{
				shop_X+=1;
				if(shop_X>eeprom_read(0x00))
					shop_X=0;
			}
			
			if(lcdmode==1)
			{
				prise_X=eeprom_read(0x02)/10.0f+0.1f;
				eeprom_write(0x02,prise_X*10);
				HAL_Delay(10);
				if(eeprom_read(0x02)>20)
				{
					prise_X=1.0;
					eeprom_write(0x02,prise_X*10);
				}
			}
			
			if(lcdmode==2)
			{
				rep_X=eeprom_read(0x00)+1;
				eeprom_write(0x00,rep_X);
			}
		break;
			
		case 3:
			if(lcdmode==0)
			{
				shop_Y+=1;
				if(shop_Y>eeprom_read(0x01))
					shop_Y=0;
			}
			
			if(lcdmode==1)
			{
				prise_Y=eeprom_read(0x03)/10.0f+0.1f;
				eeprom_write(0x03,prise_Y*10);
				HAL_Delay(10);
				if(eeprom_read(0x03)>20)
				{
					prise_Y=1.0;
					eeprom_write(0x03,prise_Y*10);
				}
			}
			
			if(lcdmode==2)
			{
				rep_Y=eeprom_read(0x01)+1;
				eeprom_write(0x01,rep_Y);
			}
		break;
			
		case 4:
			if(lcdmode==0)
			{
				r_shop_X=shop_X;
				r_shop_Y=shop_Y;
				
				rep_X=eeprom_read(0x00)-r_shop_X;
				rep_Y=eeprom_read(0x01)-r_shop_Y;
				
				shop_X=0;
				shop_Y=0;
				
				eeprom_write(0x01,rep_Y);
				HAL_Delay(10);
				eeprom_write(0x00,rep_X);
				HAL_Delay(10);
				//eeprom_write(0x04,0);
				
				prise_all=r_shop_X*eeprom_read(0x02)/10.0f+r_shop_Y*eeprom_read(0x03)/10.0f;
				sprintf(shop_buff,"X:%d,Y:%d,Z:%.1f",r_shop_X,r_shop_Y,prise_all);//////////
				HAL_UART_Transmit(&huart1,(uint8_t*)shop_buff,strlen(shop_buff),500);///////
				led1=1;
				led1_tick=uwTick;
				
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,150);//设置CRR（占空比=CRR/(ARR+1)）（CRR=占空比*（ARR+1））
				HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE); 
			}
			/*
			r_shop_X=shop_X;
			r_shop_Y=shop_Y;
			r_prise_X=prise_X;
			r_prise_Y=prise_Y;
			rep_X=rep_X-shop_X;
			rep_Y=rep_Y-shop_Y;
			shop_X=0;
			shop_Y=0;
			*/
		break;
		
			
	}
	
}

