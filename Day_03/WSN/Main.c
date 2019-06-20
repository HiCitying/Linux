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
        printf("DDDDDDDDDDaaaaaaaaaaaaat\n");
        ClearScreen(0,0,800,480,0x00ffffff);
        Show_Num(sdata.L,p,381,376,0x00FF0000); //lxu
        Show_Num(sdata.T,p,390,50,0x00FF0000);   //t
        Show_Num(sdata.P,p,521,208,0x00FF0000); //h
        Show_Num(sdata.H1,p,620,105,0x00FF0000);//p
        Show_Num(sdata.H2,p,707,362,0x00FF0000);//hum
        sleep(1);
    }
}

//void *CleenSensor()
//{
//    while (1)
//    {
//        ClearScreen(0,0,800,480,0x00ffffff);
//        sleep(1);
//    }
//
//
//}

void main(void)
{




//    int function=-1;
//    char *picture[3]={"plh_1.bmp","Hong.bmp","Bu.bmp"};
//    int i=0;//picture下标





    pthread_t sensor;
    pthread_t showsensor;
    pthread_t vedio;
    pthread_t cleensensor;



    int rph; //判断线程返回值
    int rph2;
    int rph3;

    int rph4;

    int flag=0;
    int isstop;
    int showsflag=0;

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

        printf("%d %d %d %d %d\n",sdata.L,sdata.T,sdata.P,sdata.H1,sdata.H2);

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
//                if(cleenflag!=0)
//                {
//                    pthread_cancel(cleensensor);
//                    cleenflag=0;
//                }
                if(showsflag==1)
                {
                    pthread_cancel(showsensor);
                    showsflag=0;
                }

                if(flag==0)
                {

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
                    isstop= pthread_cancel(vedio);
                    //Resive();

//                    if(cleenflag==0)
//                    {
//                        memset(&cleensensor, 0, sizeof(cleensensor));
//                        if((rph4 = pthread_create(&cleensensor, NULL,CleenSensor, NULL)) != 0)
//                        {
//                            printf("Create CleenSensor success\n");
//                        }else
//                        {
//                            printf("Create CleenSensor error\n");
//                        }
//                        cleenflag=1;
//                    }


                    while (1)
                    {
                        if(isstop==0)
                        {
                            printf("TTTTTTTTTTTTSUCCESSSSS\n");
                            break;
                        } else
                        {
                            printf("WWWait stop");
                        }
                    }
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
                }


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


    sleep(1);

    }
    pthread_cancel(sensor);

}