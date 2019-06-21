#ifndef _CLEARSCREEN_H_
#define _CLEARSCREEN_H_

#define SWIDTH 800  // 屏幕宽度
#define SHIGH  480  // 屏幕高度


#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


void ClearScreen(int x0,int y0,int pw,int ph,int color);
//ph 高度
//pw 宽度
//color 颜色
//x0 初始x位置
//y0 初始位置

#endif