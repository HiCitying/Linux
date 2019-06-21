#ifndef _V4l2_
#define _V4l2_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>

void lcd_draw_point(int x,int y,int color);
int convert_yuv_to_rgb_pixel(int y, int u, int v);
void process_yuv_image(unsigned char *yuv, int width, int height);
void lcd_clear(int color);
void lcd_init();
void lcd_video_close();

void V4l2();
//void Resive();

void *ShowVedio();


#endif