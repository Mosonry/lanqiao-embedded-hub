#include "uart_app.h"
float add;
float uart_X;
float uart_Y;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		if(uart_rx_buffer[0]=='?'&&uart_rx_buffer[1]=='\0')
		{
			uart_X=eeprom_read(0x02)/10.0f;
			uart_Y=eeprom_read(0x03)/10.0f;
			printf("X:%.1f,Y:%.1f",uart_X,uart_Y);
		}	
	}
	HAL_UART_Receive_IT(&huart1,uart_rx_buffer,1);
}

void uart_proc(void)
{
	if(uart_rx_index==0)return;
	if(uwTick-uart_rx_ticks>100)
	{
		
		memset(&uart_rx_buffer,0,uart_rx_index);
		uart_rx_index=0;
		huart1.pRxBuffPtr = uart_rx_buffer;
	
	}

}

