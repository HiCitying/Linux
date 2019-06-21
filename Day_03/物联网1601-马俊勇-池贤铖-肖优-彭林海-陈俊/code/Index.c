﻿//#include "myutils.h"
#include "Index.h"


void Index(void)
{
	//1.打开文件
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}
	
	//2.映射文件
	int *p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap erorr\n");
	}
	
	unsigned char buff[4][175]={{0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x07,0xC0,0x60,0x00,0x00,0x07,0xFF,0xEF,0xFF,0x00,0x0F,0xFF,
0xEF,0xFF,0x00,0x1F,0xFF,0xEF,0xFF,0x00,0x1E,0x3C,0x0F,0x0F,0x00,0x0E,0x3C,0x0F,
0x0F,0x00,0x3F,0xFF,0xFF,0x0F,0x00,0x3F,0xFF,0xFF,0x0F,0x00,0x3F,0xFF,0xFF,0x0F,
0x00,0x00,0x7C,0x0F,0x0F,0x00,0x00,0xFF,0x0F,0xFF,0x00,0x01,0xFF,0xEF,0xFF,0x00,
0x03,0xE7,0xFF,0xFF,0x00,0x0F,0xC3,0xE0,0x00,0x00,0x1F,0x80,0xC0,0x00,0x00,0x1F,
0xFF,0xFF,0xF8,0x00,0x0F,0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,0xF8,0x00,0x01,0xF0,
0x00,0xF8,0x00,0x01,0xF0,0x00,0xF8,0x00,0x01,0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,
0xF8,0x00,0x01,0xFF,0xFF,0xF8,0x00,0x01,0xF0,0x00,0xF8,0x00,0x01,0xF0,0x00,0xF8,
0x00,0x01,0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,0xF8,0x00,
0x01,0xF0,0x00,0xF8,0x00,0x00,0xE0,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0xF0,0x01,0xE0,0x00,0x00,
0xF0,0x01,0xE0,0x00,0x3F,0xFF,0xBF,0xFF,0x80,0x3F,0xFF,0xBF,0xFF,0x80,0x3F,0xFF,
0xBF,0xFF,0x80,0x00,0xF0,0x01,0xE0,0x00,0x1F,0xFF,0xBF,0xFF,0x00,0x1F,0xFF,0xBF,
0xFF,0x00,0x08,0xF1,0x11,0xE3,0x00,0x00,0xF0,0x01,0xE0,0x00,0x7F,0xFF,0xFF,0xFF,
0xC0,0x7F,0xFF,0xFF,0xFF,0xC0,0x00,0xF0,0x01,0xE0,0x00,0x0F,0xFF,0xFF,0xFC,0x00,
0x0F,0xFF,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x1E,0x00,0x07,
0xFF,0xFF,0xFE,0x00,0x07,0xFF,0xFF,0xFE,0x00,0x07,0xFF,0xFF,0xFE,0x00,0x00,0x00,
0x00,0x1E,0x00,0x07,0xFF,0xFF,0xFE,0x00,0x07,0xFF,0xFF,0xFE,0x00,0x00,0x00,0xE0,
0x08,0x00,0x1C,0x79,0xE0,0x3C,0x00,0x1E,0x78,0xF0,0x3E,0x00,0x1E,0x78,0xFB,0xDF,
0x00,0x3E,0x78,0x73,0xCF,0x80,0x3C,0x7F,0xFF,0xC7,0xC0,0x7C,0x7F,0xFF,0x83,0x80,
0x38,0x3F,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,
0x00,0xF8,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,
0xF0,0x00,0x00,0x0F,0xFF,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,
0xFE,0x00,0x0F,0x03,0xE0,0x1E,0x00,0x0F,0x03,0xC0,0x1E,0x00,0x0F,0x07,0xE0,0x1E,
0x00,0x07,0x07,0xE0,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x00,0x1F,0xF0,0x30,0x00,
0x00,0x3E,0xF0,0x78,0x00,0x00,0x7E,0xF8,0xFC,0x00,0x00,0xFC,0x79,0xF8,0x00,0x01,
0xF8,0x3F,0xE0,0x00,0x03,0xF8,0x3F,0xC0,0x00,0x0F,0xF8,0x1F,0x80,0x00,0x3F,0xF8,
0x1F,0x00,0x00,0x7F,0x78,0x0F,0x80,0x00,0x3E,0x78,0x07,0xC0,0x00,0x18,0x78,0x43,
0xE0,0x00,0x00,0x78,0xE1,0xF8,0x00,0x00,0x7B,0xE0,0xFE,0x00,0x00,0x7F,0xF0,0x7F,
0x80,0x00,0x7F,0xC0,0x3F,0x80,0x00,0x7F,0x80,0x1F,0x00,0x00,0xFE,0x00,0x06,0x00,
0x00,0x78,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,
0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,
0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x0C,0x1F,0x1E,
0x0E,0x00,0x3E,0x1F,0x1E,0x0F,0x80,0x3E,0x1F,0x1E,0x1F,0x00,0x1F,0x1F,0x1E,0x1F,
0x00,0x1F,0x1F,0x1E,0x1E,0x00,0x1F,0x1F,0x1E,0x3E,0x00,0x0F,0x9F,0x1E,0x3E,0x00,
0x0F,0x9F,0x1E,0x3C,0x00,0x0F,0x9F,0x1E,0x7C,0x00,0x07,0xDF,0x1E,0x7C,0x00,0x07,
0xDF,0x1E,0x78,0x00,0x07,0xDF,0x1E,0xF8,0x00,0x03,0xFF,0x1E,0xF0,0x00,0x03,0x9F,
0x1E,0x70,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,
0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,0x00,0x00,0x1F,0x1E,0x00,
0x00,0x7F,0xFF,0xFF,0xFF,0xC0,0x7F,0xFF,0xFF,0xFF,0xC0,0x7F,0xFF,0xFF,0xFF,0xC0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
	
	int i,color=0x00ff0000;

	printf("IIIIIIIIIIIndexxxxxxxxxx\n");
	for (i=0; i<4;i++)
	{
		//write_word(buff[i],40,35,300+i*40,200,color);
		Show_Word(buff[i],p,300+i*40,200,40,175,color);
		printf("FFFFFFFFFFFFFFFFFF\n");
	}
	
	close(lcd_fd);
    munmap(p,800*480*4);
	
	//return 0;
}