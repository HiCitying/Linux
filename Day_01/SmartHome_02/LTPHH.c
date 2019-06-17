#include "LTPHH.h"
#include "Serial.h"
#include "Show_Num.h"
#include "ClearScreen.h"


//void LTPHH(int *py,int *L,int *T,int *P,int *H1,int *H2,int flag)
void LTPHH(int *py,int *L,int flag)
{
    int serial_fd = init_serial("/dev/ttySAC1",9600);

    while(1)
    {
        unsigned char cmd[3] = {0xA5,0x83,0x28};
        unsigned char buf[24] = {0};

        int ret = write(serial_fd,cmd,3);//下指令
        if(ret < 3)
        {
            perror("write serial_fd error\n");
        }
        ret = read(serial_fd,buf,24);//读数据
        if(ret < 24 || buf[0] != 0x5A || buf[1] != 0x5A)
        {
            usleep(200000);
            continue;
        }

        //处理数据

        //光照强度
        int lxu = buf[4] << 24 | buf[5] << 16 | buf[6] << 8 | buf[7];
        lxu = lxu / 100;
        *L=lxu;
        printf("lxu = %d\n",lxu);

        //温度
        int t = buf[13] << 8 | buf[14];
        t = t / 100;
        //*T=t;
        printf("t = %d\n",t);

        //气压
        int p = buf[15] << 24 | buf[16] << 16 | buf[17] << 8 | buf[18];
        p = p / 100;
        //*P=p;
        printf("p = %d\n",p);

        //湿度
        int hum = buf[19] << 8 | buf[20];
        hum = hum / 100;
        //*H1=hum;
        printf("hum = %d\n",hum);

        //海拔
        int h = buf[21] << 8 | buf[22];
        //*H2=h;
        printf("h = %d\n",h);

        //usleep(200000);
        if(flag==1)
        {
            ClearScreen(0,280,100,100,0x00ffffff);
            Show_Num(*L,py,300,0,0x00FF0000);
            Show_Num(t,py,300,20,0x00FF0000);
            Show_Num(p,py,300,40,0x00FF0000);
            Show_Num(hum,py,300,60,0x00FF0000);
            Show_Num(h,py,300,80,0x00FF0000);
            sleep(1);
        }


    }

    close(serial_fd);
}