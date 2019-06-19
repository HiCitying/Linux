#include "ClearScreen.h"

//ph 高度
//pw 宽度
//color 颜色



void ClearScreen(int x0,int y0,int pw,int ph,int color)
{
    int x,y;
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }
    lseek(lcd_fd,0,SEEK_SET);
    int *p=mmap(NULL,SWIDTH*SHIGH*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
    for(x=x0;x<x0+ph;x++)
    {
        usleep(1);
        for(y=y0;y<y0+pw;y++)
        {
            if(x<0||x>SHIGH||y<0||y>SWIDTH)
            {
                perror("Segment default\n");
            } else
            {

                *(p+x*SWIDTH+y)=color;
            }
        }
    }

    munmap(p,SWIDTH*SHIGH*4);
    close(lcd_fd);

}
