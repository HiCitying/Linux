#include <stdio.h>
#include <errno.h>
#include <linux/input.h>
#include <signal.h>
#include "DrawPoint.h"
#include "ClearScreen.h"
#include "Play_Music.h"
#include "Show_Bmp.h"
#include "Open_Led.h"
#include "Show_Num.h"
#include "Show_Word.h"
#include "LTPHH.h"

void main(void)
{



    ClearScreen(0,0,800,480,0x00ffffff);
    ClearScreen(0,195,5,480,0x00ff0000);
    ClearScreen(115,0,195,5,0x00ff0000);
    ClearScreen(235,0,195,5,0x00ff0000);
    ClearScreen(355,0,195,5,0x00ff0000);


    int pid_1=-1;
    int pid_2=-1;
    int pid_3=-1;
    int pid_4=-1;

    int pid_5=-1;
    int function=-1;
    ///////////////////////////////////
    char *music[2]={"TSLS.mp3","TSWD.mp3"};


    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }

    int led_fd = open("/dev/led_drv",O_RDWR);
    if(led_fd < 0)
    {
        perror("open led_fd erorr\n");
    }

    int *p=(int *)Mapping("/dev/fb0",800,480);



    Open_Led(led_fd,0,10);
    Show_Bmp("Hong.bmp",p,800,480,0,0);



    struct input_event event;


    int x,y;
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd < 0)
    {
        perror("open touch_fd error\n");
    }
    int ret;
    int flag=0;
    int num_music=0;
    int led_flag=0;


    while(1)
    {

        //读取触摸屏事件
        ret = read(touch_fd,&event,sizeof(event));
        if(ret < sizeof(event))
        {
            continue;
        }
       //printf("ev.type = %d , ev.code = %d, ev.value = %d\n",event.type,event.code,event.value);

            //认为按下去了
        else if(event.type == EV_KEY && event.code == BTN_TOUCH && event.value != 0 )
        {
            if(x>0&&x<200)
            {
                if(y>0&&y<120)
                {
                    printf("first\n");
                    //function=1;
                } else if(y>120&&y<240)
                {
                    printf("second\n");
                    function=2;
                } else if(y>240&&y<360)
                {
                    printf("third\n");
                    function=3;

                } else
                {
                    printf("forth\n");
                    function=4;
                }



                switch (function)
                {
                    case 1:
                    {
                        break;
                    }
                    case 2:
                    {

                    }
                    case 3:
                    {

                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            } else
            {
                switch (function)
                {
                    case 1:
                    {
                        //判断区域
                        break;
                    }
                    case 2:
                    {
                        break;
                    }
                    case 3:
                    {

                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                    default:
                    {

                    }

                }
            }
        }
        //认为是一个X事件
        if(event.type == EV_ABS && event.code == ABS_X)
        {
            x = event.value;
            //printf("xxxxxxxxxxxxxx:   %d",x);
        }
            //认为是一个Y事件
        else if(event.type == EV_ABS && event.code == ABS_Y)
        {
            y = event.value;
            //printf("yyyyyyyyyyyyyy:   %d",y);
        }
            //认为此时弹起来了
        else if(event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 0)
        {

        }

    }


}