#include <stdio.h>
#include <errno.h>
#include <linux/input.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

#include "DrawPoint.h"
#include "ClearScreen.h"
#include "Play_Music.h"
#include "Show_Bmp.h"
#include "Open_Led.h"
#include "Show_Num.h"
#include "Show_Word.h"
#include "LTPHH.h"
#include "TouchScreen.h"
#include "V4l2.h"
#include "Index.h"

int *p;

typedef struct SData{
    int L;
    int T;
    int P;
    int H1;
    int H2;
}SData;

SData sdata;

void *ShowData()
{
    while (1)
    {

        Show_Bmp("./sensordata.bmp",p,600,480,200,0);
        Show_Bmp("./Lsensor.bmp",p,200,480,0,0);
        Show_Num(sdata.L,p,381,376,0x00FF0000); //lxu
        Show_Num(sdata.T,p,390,50,0x00FF0000);   //t
        Show_Num(sdata.H2,p,521,208,0x00FF0000); //h
        Show_Num(sdata.P,p,620,105,0x00FF0000);//p
        Show_Num(sdata.H1,p,707,362,0x00FF0000);//hum
        sleep(1);
    }
}



void main(void)
{



    ClearScreen(0,0,800,480,0x0090EE90);
    Index();

    pthread_t sensor;
    pthread_t showsensor;
    pthread_t vedio;



    int rph;  //判断初始线程返回值
    int rph2; //判断摄像头线程
    int rph3; //判断显示传感器值


    int flag=0;   //判断Vedio线程是否创建的标志
    int showsflag=0;  //判断显示传感器数值线程是否创建的标志

    memset(&sensor, 0, sizeof(sensor));
    if((rph = pthread_create(&sensor, NULL,LTPHH,(SData *)&sdata)) != 0)
    {
        printf("Creat pthread error\n");
    }else{
        printf("Creat pthread success\n");
    }

    V4l2();

    p=(int *)Mapping("/dev/fb0",800,480);

    int TS;//接收触屏返回值

    while (1)
    {

        //printf("%d %d %d %d %d\n",sdata.L,sdata.T,sdata.P,sdata.H1,sdata.H2);

        TS=TouchScreen();

        switch (TS)
        {
            case 0:
            {
                printf("Touch 000000000\n");
                break;
            }
            case 1:
            {

                printf("Touch 111111111\n");


                if(showsflag==1)
                {
                    pthread_cancel(showsensor);
                    showsflag=0;
                }

                if(flag==0)
                {
                    Show_Bmp("Rvedio.bmp",p,160,480,640,0);

                    memset(&vedio, 0, sizeof(vedio));
                    if((rph2 = pthread_create(&vedio, NULL,ShowVedio, NULL)) != 0)
                    {
                        printf("Create V4l2 success\n");
                    }else
                    {
                        printf("Create V4l2 error\n");
                    }
                    flag=1;
                } else if(flag==1)
                {
                    printf("Exitttttttt\n");
                }


                break;
            }
            case 2:
            {
                printf("Touch 222222222\n");

                if(flag==1)
                {
                    pthread_cancel(vedio);
                    flag=0;
                }

                if(showsflag==0)
                {
                    memset(&showsensor, 0, sizeof(showsensor));
                    if((rph3 = pthread_create(&showsensor, NULL,ShowData, NULL)) != 0)
                    {
                        printf("Create ShowData success\n");
                    }else
                    {
                        printf("Create ShowData error\n");
                    }
                    showsflag=1;
                } else if(showsflag==1)
                {
                    printf("Exxxxxxxxxxxit\n");
                }

                break;
            }
            case 3:
            {
                printf("Touch 333333333\n");
                Open_Led(1,9);
                break;
            }
            case 4:
            {
                Open_Led(0,9);
                printf("Touch 444444444\n");
                break;
            }
            default:
            {
                break;
            }
        }


    sleep(1);

    }
    pthread_cancel(sensor);

}