#ifndef BSP_H
#define BSP_H
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"

#include "lcd.h"

#include "key_app.h"
#include "lcd_app.h"
#include "adc_app.h"
#include "tim_app.h"

#include "led_app.h"
extern uint32_t dma_buff[2][30];
extern float adc_value[2];
extern uint8_t lcdmode;
extern int tim_ic_buffer[2][64];
extern int tim_ic_temp[2];
extern int tim_ic_val[2];
extern uint8_t para[2];
extern uint8_t index;
extern uint8_t lcdmode_data;
extern uint32_t pa1_L_hz;
extern uint32_t pa1_H_hz;
extern float CCR_L;
extern float CCR_H;
extern uint8_t recd_N;
extern float recd_MH;
extern float recd_ML;
extern float recd_MH_max;
extern float recd_ML_max;
extern uint8_t duty;
extern uint8_t duty_lock_flag;
extern uint32_t key_tick;
extern float max_high;
extern float max_low;
extern uint32_t pwm_tick;//PWM计时器
extern uint16_t freq_val;//PWM频率值
extern float data_v;
extern float last_v;
extern uint8_t speed_valid;// 速度更新标志
extern uint8_t led_s;
extern uint32_t arr;
extern uint32_t ccr;
#endif
