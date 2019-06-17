#include "Open_Led.h"

void Open_Led(int led_fd,int status,int led_id)
{
    unsigned char cmd[2];
    cmd[0] = status;
    cmd[1] = led_id;
    lseek(led_fd,0,SEEK_SET);
    write(led_fd,cmd,2);
    //close(led_fd);

}