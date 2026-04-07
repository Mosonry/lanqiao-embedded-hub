#include "lcd_app.h"
char String[21];
void LcdSprintf(uint8_t Line,char * format,...)
{
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	LCD_DisplayStringLine(Line,(u8*)String);
}
uint8_t lcdmode;
uint8_t shop_X=0;
uint8_t shop_Y=0;
float prise_X=1.0;
float prise_Y=1.0;
uint8_t rep_X=10;
uint8_t rep_Y=10;
void lcd_proc(void)
{
	switch(lcdmode)
	{
		case 0:
			LcdSprintf(Line1,"        SHOP     ");
			LcdSprintf(Line3,"     X:%d        ",shop_X);
			LcdSprintf(Line4,"     Y:%d        ",shop_Y);
			LcdSprintf(Line5,"   eeprom(0x00):%d   ",eeprom_read(0x00));
			LcdSprintf(Line6,"   eeprom(0x01):%d   ",eeprom_read(0x01));
			LcdSprintf(Line7,"   eeprom(0x02):%d   ",eeprom_read(0x02));
			LcdSprintf(Line8,"   eeprom(0x03):%d   ",eeprom_read(0x03));
			LcdSprintf(Line9,"   eeprom(0x04):%d   ",eeprom_read(0x04));
		break;
		
		case 1:
			LcdSprintf(Line1,"        PRICE     ");
			LcdSprintf(Line3,"     X:%.1f        ",eeprom_read(0x02)/10.0f);
			LcdSprintf(Line4,"     Y:%.1f        ",eeprom_read(0x03)/10.0f);
		break;
		
		case 2:
			LcdSprintf(Line1,"        REP     ");
			LcdSprintf(Line3,"     X:%d        ",eeprom_read(0x00));
			LcdSprintf(Line4,"     Y:%d        ",eeprom_read(0x01));
		break;
		
	}
}

