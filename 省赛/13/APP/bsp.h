#ifndef BSP
#define BSP
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdarg.h"

#include "lcd.h"
#include "i2c_hal.h"
#include "key_app.h"
#include "lcd_app.h"
#include "eeprom.h"
#include "uart_app.h"
#include "led_app.h"

extern uint8_t key_old;
extern uint8_t key_up;
extern uint8_t key_down;
extern uint8_t key_val;

extern uint8_t uart_rx_buffer[128];
extern uint16_t uart_rx_index;
extern uint32_t uart_rx_ticks;

extern uint8_t lcdmode;
extern uint8_t shop_X;
extern uint8_t shop_Y;
extern float prise_X;
extern float prise_Y;
extern uint8_t rep_X;
extern uint8_t rep_Y;

extern uint8_t r_shop_X;
extern uint8_t r_shop_Y;
extern float r_prise_X;
extern float r_prise_Y;
extern uint8_t r_rep_X;
extern uint8_t r_rep_Y;
extern char shop_buff[50];
extern float prise_all;
extern uint8_t led1;
extern uint32_t led1_tick;
#endif
