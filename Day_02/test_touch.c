#include <stdio.h>

int touch_screen(void)
{
	int x,y;
	int x_start,y_start,x_stop,y_stop,
	int flags = 0;
	while(1)
	{
		struct input_event ev;
		//读取触摸屏事件
		int ret = read(touch_fd,&ev,sizeof(ev));
		if(ret < sizeof(ev))
		{
			continue;
		}
		printf("ev.type = %d , ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);
		
		//认为是一个X事件
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			x = ev.value;
		}
		//认为是一个Y事件
		else if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			y = ev.value;
		}
		//认为按下去了
		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0 )
		{
			if (flags == 0)
			{
				x_start = x;
				y_start = y;
				flags = 1;
			}
		}
		//认为此时弹起来了
		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			x_stop = x;
			y_stop = y;
			break;
		}
	}
	
	if((abs(x_stop - x_start) - abs(y_stop - y_start) > 0) && abs(x_stop - x_start) > 30) //认为是一个x方向的事件
	{
		if (x_stop - x_start > 0) //右滑
		{
			return 1;
		}
		else						//左滑
		{
			return 2;
		}
	}
	
}



int main(void)
{
	
	//1.打开触摸屏文件
	int touch_fd = open("/dev/input/event0",O_RDWR);
	if(touch_fd < 0)
	{
		perror("open touch_fd error\n");
	}
	while(1)
	{
		int flag = touch_screen();
		
		if(flag == 1)
		{
			
		}
		if(flag == 2)
		{
			
		}
		
		if(flag == 3)
		{
			
		}
		if(flag == 4)
		{
			
		}
		
		if(flag == 0)
		{
			
		}
	}
	
	
	
	return 0;
}