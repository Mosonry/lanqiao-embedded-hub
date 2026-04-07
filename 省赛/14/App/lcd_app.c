#include "lcd_app.h"
void LcdSprintf(uint8_t Line,char * format,...)
{
	char String[21];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	LCD_DisplayStringLine(Line,(u8*)String);
}
uint8_t lcdmode;
uint8_t lcdmode_data=0;
uint32_t vv;
uint32_t pa1_L_hz=4000;
uint32_t pa1_H_hz=8000;
uint8_t duty;
float max_high;
float max_low;
void lcd_proc(void)
{
	switch(lcdmode)
	{
		case 0://数据界面
			if(lcdmode_data==0)
			{
			LcdSprintf(Line1,"        DATA        ");
			LcdSprintf(Line3,"     M=L            ");
			LcdSprintf(Line4,"     P=%d%%         ",duty);
			LcdSprintf(Line5,"     V=%.1f         ",data_v);//pa7
			}
			else
			{
			LcdSprintf(Line1,"        DATA        ");
			LcdSprintf(Line3,"     M=H            ");
			LcdSprintf(Line4,"     P=%d%%         ",duty);
			LcdSprintf(Line5,"     V=%.1f         ",data_v);
			}
			
		break;
		case 1://参数界面
			LcdSprintf(Line1,"        PARA        ");
			LcdSprintf(Line3,"     R=%d           ",para[0]);
			LcdSprintf(Line4,"     K=%d           ",para[1]);
			LcdSprintf(Line5,"                    ");
		break;
		case 2://记录界面
			LcdSprintf(Line1,"        RECD        ");
			LcdSprintf(Line3,"     N=%d           ",recd_N);
			LcdSprintf(Line4,"     MH=%.1f        ",max_high);
			LcdSprintf(Line5,"     ML=%.1f        ",max_low);
		break;
	}
}
