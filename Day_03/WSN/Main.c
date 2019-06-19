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

void main(void)
{




//    int function=-1;
//    char *picture[3]={"plh_1.bmp","Hong.bmp","Bu.bmp"};
//    int i=0;//picture下标


    typedef struct SData{
        int L;
        int T;
        int P;
        int H1;
        int H2;
    }SData;

    SData sdata;


    pthread_t sensor;
    pthread_t color;


    int rph; //判断线程返回值
    memset(&sensor, 0, sizeof(sensor));
    if((rph = pthread_create(&sensor, NULL,LTPHH,(SData *)&sdata)) != 0)
    {
        printf("Creat pthread error\n");
    }else{
        printf("Creat pthread success\n");
    }


    printf("TTTTTTTTTTTT\n");

    int *p=(int *)Mapping("/dev/fb0",800,480);

    int TS;//接收触屏返回值

    while (1)
    {

        printf("%d %d %d %d %d\n",sdata.L,sdata.T,sdata.P,sdata.H1,sdata.H2);
        printf("ssssssssss\n");
        //TS=TouchScreen();

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
                break;
            }
            case 2:
            {
                printf("Touch 222222222\n");
                break;
            }
            case 3:
            {
                printf("Touch 333333333\n");
                break;
            }
            case 4:
            {
                printf("Touch 444444444\n");
                break;
            }
            default:
            {
                break;
            }
        }


    sleep(1)

    }
    pthread_cancel(sensor);

}