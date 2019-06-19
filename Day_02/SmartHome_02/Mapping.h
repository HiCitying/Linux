#ifndef _MAPPING_H_
#define _MAPPING_H_

#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define PX 4
int *Mapping(char *lcd,int pywidth,int pyhigh);
//lcd      LCD文件位置
// pywidth 映射屏幕宽度
// pyhigh  映射屏幕高度
// PX      单个屏幕像点字节数
void DeMapping(int *py,int pywidth,int pyhigh);


#endif