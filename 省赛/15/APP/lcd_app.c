#include "lcd_app.h"

void LcdSprintf(uint8_t Line,char *format,...)
{
	char String[21];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	LCD_DisplayStringLine(Line,(u8*)String);
}
uint8_t lcdmode;
uint8_t data_lcdmode;
int para_arr[3]={1000,5000,0};//参数数组 0-PD 1-PH 2-PX
uint8_t recd_arr[4]={0,0,0,0};//数据统计数组 0-NDA 1-NDB 2-NHA 3-NHB
const int para_min_max[2][3]={{100,1000,-1000},{1000,10000,1000}};

//int sum=tim_ic_val[0]+para_arr[2];

void lcd_proc(void)
{
	uint16_t temp[2]={0,0};
	switch(lcdmode)
	{
		case 0:
			if(data_lcdmode==0)
			{
				LcdSprintf(Line1,"        DATA     ");
				if(tim_ic_val[0]+para_arr[2]>1000)
					LcdSprintf(Line3,"     A=%.2fKHz       ",(tim_ic_val[0]+para_arr[2])/1000.0f);
				else if(tim_ic_val[0]+para_arr[2]>0 && tim_ic_val[0]+para_arr[2]<1000)
				{
					LcdSprintf(Line3,"     A=%dHz          ",tim_ic_val[0]+para_arr[2]);
				}
				else
				{
					LcdSprintf(Line3,"     A=NULL          ");
				}
				
				if(tim_ic_val[1]+para_arr[2]>1000)
					LcdSprintf(Line4,"     B=%.2fKHz       ",(tim_ic_val[1]+para_arr[2])/1000.0f);
				else if(tim_ic_val[1]+para_arr[2]>0 && tim_ic_val[1]+para_arr[2]<1000)
					LcdSprintf(Line4,"     B=%dHz          ",(tim_ic_val[1]+para_arr[2]));
				else
				{
					LcdSprintf(Line4,"     B=NULL          ");
				}
			}
			else
			{
				temp[0]=(int)(1.0f/(float)(tim_ic_val[0]+para_arr[2])*1000000);
				temp[1]=(int)(1.0f/(float)(tim_ic_val[1]+para_arr[2])*1000000);
				if(tim_ic_val[0]+para_arr[2]>0)
				{
					if(temp[0]>1000)
					LcdSprintf(Line3,"     A=%.2fmS       ",(float)(temp[0]/1000.0f));
				else
					LcdSprintf(Line3,"     A=%duS         ",temp[0]);
				}
				else
					LcdSprintf(Line3,"     A=NULL          ");
				
				
				if(tim_ic_val[1]+para_arr[2]>0)
				{
					if(temp[1]>1000)
					LcdSprintf(Line4,"     B=%.2fmS       ",(float)(temp[1]/1000.0f));
				else
					LcdSprintf(Line4,"     B=%duS         ",temp[1]);
				}
				else
					LcdSprintf(Line4,"     B=NULL          ");

			}
			break;
			
		case 1:
			LcdSprintf(Line1,"        PARA       ");
			LcdSprintf(Line3,"     PD=%dHz            ",para_arr[0]);
			LcdSprintf(Line4,"     PH=%dHz            ",para_arr[1]);
			LcdSprintf(Line5,"     PX=%dHz            ",para_arr[2]);
		break;
		
		case 2:
			LcdSprintf(Line1,"        RECD      ");
			LcdSprintf(Line3,"     NDA=%d            ",recd_arr[0]);
			LcdSprintf(Line4,"     NDB=%d            ",recd_arr[1]);
			LcdSprintf(Line5,"     NHA=%d            ",recd_arr[3]);
			LcdSprintf(Line6,"     NHB=%d            ",recd_arr[2]);
		break;
	}
}

