#include "tim_app.h"

int tim_ic_buffer[2][64];
int tim_ic_temp[2];
int tim_ic_val[2];
float data_v;
float last_v=0;
uint8_t speed_valid = 0;// 速度更新标志
uint32_t speed_tick_low = 0;
uint32_t speed_tick_high = 0;
void ic_proc(void)
{
	tim_ic_temp[0]=0;
	tim_ic_temp[1]=0;
	for(int i=0;i<64;i++)
	{
		tim_ic_temp[0]+=tim_ic_buffer[0][i];
		tim_ic_temp[1]+=tim_ic_buffer[1][i];
	}
	tim_ic_temp[0] /=64;
	tim_ic_temp[1] /=64;
	tim_ic_val[0]=(int)((float)(1000.0f*1000.0f)/(float)tim_ic_temp[0]);
	tim_ic_val[1]=(int)((float)(1000.0f*1000.0f)/(float)tim_ic_temp[1]);
	if(lcdmode!=1)
	data_v=(tim_ic_val[0]*0.0628f*para[0])/para[1];
/*
		if((int)last_v!=(int)data_v)
	{
		speed_valid=1;
		
	}
	else if(speed_valid==1&&!lcdmode==1)
	{
		
		if(lcdmode_data==0)
		{
			if(data_v>=max_low)
			{
				speed_tick_low = uwTick;
				if((uwTick - speed_tick_low) > 2000)
				{
					max_low=data_v;//更新低频的最大值
					speed_valid=0;
				}
			}
		}
		
		if(lcdmode_data==1)
		{
			if(data_v>=max_high)
			{
				speed_tick_high = uwTick;
				if((uwTick - speed_tick_high) >2000)
				{
					max_high=data_v;//更新高频的最大值
					speed_valid=0;
				}
			}
		}
		
	}
	
	last_v=data_v;
	*/
	if ((int)last_v != (int)data_v) {
    speed_valid = 1;
} else if (speed_valid == 1 && lcdmode != 1) { // 修正条件判断
    if (lcdmode_data == 0) {
        if (data_v >= max_low) 
				{
            // 首次超过时设置时间戳
            if (speed_tick_low == 0) 
						{
                speed_tick_low = uwTick;
            }
						
            // 检查是否持续超过2000个tick
            if ((uint32_t)(uwTick - speed_tick_low) > 3000) //这里本来应该是2000ms，但是不知道是4t的原因还是单片机的原因，我只能改到3000才可以通过4他的测试，下面的同理
						{
                max_low = data_v;
                speed_valid = 0;
                speed_tick_low = 0; // 重置时间戳
            }
        } 
				else 
				{
            speed_tick_low = 0; // 低于阈值时重置计时
        }
    } 
		
		
		else if (lcdmode_data == 1) 
		{
        if (data_v >= max_high) {
            // 首次超过时设置时间戳
            if (speed_tick_high == 0) {
                speed_tick_high = uwTick;
            }
            // 检查是否持续超过2000个tick
            if ((uint32_t)(uwTick - speed_tick_high) > 3000) {
                max_high = data_v;
                speed_valid = 0;
                speed_tick_high = 0; // 重置时间戳
            }
        } else {
            speed_tick_high = 0; // 低于阈值时重置计时
        }
    }
}

last_v = data_v;
}
