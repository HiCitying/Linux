#include "TouchScreen.h"


int TouchScreen(void)
{
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd < 0)
    {
        perror("open touch_fd error\n");
    }

    int x,y;
    int x_start,y_start,x_stop,y_stop;
    int flags = 0;
    struct input_event ev;
    int ret;
    while(1)
    {

        //读取触摸屏事件
        ret = read(touch_fd,&ev,sizeof(ev));
        if(ret < sizeof(ev))
        {
            continue;
        }
        //printf("ev.type = %d , ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);

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

    //认为是一个x方向的事件
    if((abs(x_stop - x_start) - abs(y_stop - y_start) > 0) && abs(x_stop - x_start) > 30)
    {
        if (x_stop - x_start > 0) //右滑
        {
            close(touch_fd);
            return 1;
        }
        else					  //左滑
        {
            close(touch_fd);
            return 2;
        }
    } else if((abs(x_stop - x_start) - abs(y_stop - y_start) < 0) && abs(y_stop - y_start) > 30)//认为是一个y方向的事件
    {
        if(y_stop - y_start < 0)  //上滑
        {
            close(touch_fd);
            return 3;
        } else                    //下滑
        {
            close(touch_fd);
            return 4;
        }
    } else
    {
        close(touch_fd);
        return 0;
    }
}