#include "scheduler.h"

uint8_t task_num;

typedef struct
{
	void(*task_func)(void);
	uint32_t rate_ms;
	uint32_t last_run;
}task_t;


static task_t scheduler_task[]=
{
		{led_proc, 1, 0},  // 定义一个任务，任务函数为 Led_Proc，执行周期为 10 毫秒，初始上次运行时间为 0
    {key_proc, 10, 0},  // 定义一个任务，任务函数为 Key_Proc，执行周期为 10 毫秒，初始上次运行时间为 0
    {lcd_proc, 100,0},  // 定义一个任务，任务函数为 Lcd_Proc，执行周期为 100 毫秒，初始上次运行时间为 0
    {ic_proc,  100,0}
};

void scheduler_init(void)
{
	task_num=sizeof(scheduler_task)/sizeof(task_t);
}

void scheduler_run(void)
{
	for(uint8_t i=0;i<task_num;i++)
	{
		uint32_t now_time=HAL_GetTick();
		if (now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            // 更新任务的上次运行时间为当前时间
            scheduler_task[i].last_run = now_time;

            // 执行任务函数
            scheduler_task[i].task_func();
        }
	}
	
}