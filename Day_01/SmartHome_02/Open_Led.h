#ifndef _OPEN_LED_H_
#define _OPEN_LED_H_


#include <unistd.h>
#include <sys/types.h>


void Open_Led(int fd,int status,int led_id);
// fd led驱动描述符
// cmd[0] 灯状态 0 熄灭 1 点亮
// cmd[1] 灯号

#endif