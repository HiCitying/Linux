#include "Mapping.h"


int *Mapping(char *lcd,int pywidth,int pyhigh)
{
    int lcd_fd = open(lcd,O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }

    int *p = mmap(NULL,pywidth*pyhigh*PX,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
    if(p == MAP_FAILED)
    {
        perror("mmap erorr\n");
    }
    return p;
}

void DeMapping(int *py,int pywidth,int pyhigh)
{
    munmap(py,pywidth*pyhigh*PX);
}