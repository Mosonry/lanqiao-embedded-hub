#ifndef BSP_H
#define BSP_H

#include "main.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "lcd.h"


#include "stdarg.h"
#include "string.h"
#include "stdio.h"



#include "lcd_app.h"
#include "key_app.h"
#include "tim_app.h"
#include "led_app.h"

extern int tim_ic_buffer[2][64];
extern int tim_ic_temp[2];
extern int tim_ic_val[2];
extern uint8_t lcdmode;
extern uint8_t data_lcdmode;

extern int para_arr[3];//参数数组 0-PD 1-PH 2-PH
extern uint8_t recd_arr[4];//数据统计数组 0-NDA 1-NDB 2-NHA 3-NHB
extern const int para_min_max[2][3];

#endif


