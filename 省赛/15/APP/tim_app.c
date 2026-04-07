#include "tim_app.h"
int tim_ic_buffer[2][64];
int tim_ic_temp[2];
int tim_ic_val[2];

uint8_t sudden_change_detected_a;
uint8_t sudden_change_detected_b;
uint8_t nhx_flag[2]; // 频率超限标志位

typedef struct//定义结构体
{
    uint32_t timestamp; // 采集时的时间戳
    uint32_t fre;    // 采集到的频率
} fre_data_t;

fre_data_t buffer_a[30];//定义完结构体后开始定义变量
fre_data_t buffer_b[30];

int buffer_start_a=0;
int buffer_end_a=0;
int buffer_start_b=0;
int buffer_end_b=0;
void limit_value(int *data, int size, uint32_t min_val, uint32_t max_val) 
{
    for (int i = 0; i < size; i++) 
    {
        if (data[i] < min_val) {
            data[i] = min_val;
        } else if (data[i] > max_val) 
        {
            data[i] = max_val;
        }
    }
}


void add_fre_data_a(uint32_t fre,uint32_t current_time,fre_data_t *buffer)
{
	buffer[buffer_end_a].timestamp=current_time;
	buffer[buffer_end_a].fre=fre;
	buffer_end_a=(buffer_end_a+1)%30;
	if(buffer_end_a==buffer_start_a)
	{
		buffer_start_a=(buffer_start_a+1)%30;
	}
	
	while(current_time-buffer[buffer_start_a].timestamp>3000)
	{
		buffer_start_a =(buffer_start_a+1)%30;
	}
}
void add_fre_data_b(uint32_t fre,uint32_t current_time,fre_data_t *buffer)
{
	buffer[buffer_end_b].timestamp=current_time;
	buffer[buffer_end_b].fre=fre;
	buffer_end_b=(buffer_end_b+1)%30;
	if(buffer_end_b==buffer_start_b)
	{
		buffer_start_b=(buffer_start_b+1)%30;
	}
	
	while(current_time-buffer[buffer_start_b].timestamp>3000)
	{
		buffer_start_b =(buffer_start_b+1)%30;
	}
}

void check_fre_a(uint8_t *sudden_change_count_a,fre_data_t *buffer)//ND
{
	uint32_t f_max_a =buffer[buffer_start_a].fre;
	uint32_t f_min_a =buffer[buffer_start_a].fre;
	
	int index =buffer_start_a;
	while(index!=buffer_end_a)
	{
		if(buffer[index].fre>f_max_a)
		{
			f_max_a=buffer[index].fre;
		}
		if(buffer[index].fre<f_min_a)
		{
			f_min_a=buffer[index].fre;
		}
		index=(index+1)%30;
	}
	
	
	uint32_t diff = f_max_a-f_min_a;
	if(diff>para_arr[0])
	{
		sudden_change_detected_a=1;
	}
	else if(sudden_change_detected_a==1)
	{
		sudden_change_detected_a=0;
		(*sudden_change_count_a)++;
	}
}

void check_fre_b(uint8_t *sudden_change_count_b,fre_data_t *buffer)//ND
{
	uint32_t f_max_b =buffer[buffer_start_b].fre;
	uint32_t f_min_b =buffer[buffer_start_b].fre;
	
	int index =buffer_start_b;
	while(index!=buffer_end_b)
	{
		if(buffer[index].fre>f_max_b)
		{
			f_max_b=buffer[index].fre;
		}
		if(buffer[index].fre<f_min_b)
		{
			f_min_b=buffer[index].fre;
		}
		index=(index+1)%30;
	}
	
	
	uint32_t diff = f_max_b-f_min_b;
	if(diff>para_arr[0])
	{
		sudden_change_detected_b=1;
	}
	else if(sudden_change_detected_b==1)
	{
		sudden_change_detected_b=0;
		(*sudden_change_count_b)++;
	}
}
void ic_proc(void)
{
	 uint32_t current_time = HAL_GetTick(); // 获取当前时间
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

	
	//tim_ic_val[0]+=para_arr[2];
	//tim_ic_val[1]+=para_arr[2];//px
	
	limit_value(&tim_ic_val[0], 1, 400, 20000);
	limit_value(&tim_ic_val[1], 1, 400, 20000);
	
	add_fre_data_a(tim_ic_val[0]+para_arr[2],current_time,buffer_a);
	check_fre_a(&recd_arr[0],buffer_a);//NDA
	
	add_fre_data_b(tim_ic_val[1]+para_arr[2],current_time,buffer_b);
	check_fre_b(&recd_arr[1],buffer_b);//NDB
	
	for(int i=0;i<2;i++)
	{
		if(tim_ic_val[i]<para_arr[1])//频率是否超过PH
		{
			nhx_flag[i]=1;
		}
		else if(nhx_flag[i]==1)
		{
			nhx_flag[i]=0;
			recd_arr[3-i]++;//NHA,NHB
		}
	}
}






/*
如果sudden_change_detected是全局变量，那么处理buffer_a和buffer_b时会互相干扰。例如，当buffer_a触发了sudden_change_detected=1，接着处理buffer_b时，如果条件不满足，就会将sudden_change_detected置0，并增加sudden_change_count。这显然是不正确的，因为sudden_change_detected应该是每个buffer独立的变量，而不是全局的。

因此，sudden_change_detected应该作为每个buffer的状态保存，例如作为结构体的一部分，或者使用不同的变量来分别处理buffer_a和buffer_b的情况。否则，这两个check_fre调用会互相干扰sudden_change_detected的状态，导致逻辑错误。

例如，处理buffer_a时设置sudden_change_detected为1，然后处理buffer_b时如果条件不满足，就会将sudden_change_detected置0，并增加buffer_b的计数，而这时buffer_a的状态被错误地改变了。这显然是一个bug。

因此，sudden_change_detected应该是每个buffer对应的变量，而不是全局变量。例如，可能需要将sudden_change_detected作为buffer结构体的成员，或者使用不同的变量来分别跟踪每个buffer的状态。

用户当前的代码中，sudden_change_detected是一个全局变量，这会导致不同的buffer检查之间相互干扰，产生错误的结果。这是一个严重的逻辑错误。
*/















