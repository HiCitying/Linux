#include "V4l2.h"


int *pfb = NULL;//lcd addr
int lcd_fd;

struct userbuf{
    void *start;
    int length;
};
struct userbuf ub[12] = {0};//测试使用

//画点
void lcd_draw_point(int x,int y,int color)
{
    if (x >=0 && x < 800 && y >=0 && y < 480)
    {
        *(pfb + 800*y + x) = color;
    }
}

int convert_yuv_to_rgb_pixel(int y, int u, int v)
{
    unsigned int pixel32 = 0;
    unsigned char pixel[3];// = (unsigned char *)&pixel32;
    int r, g, b;
    r = y + (1.370705 * (v-128));
    g = y - (0.698001 * (v-128)) - (0.337633 * (u-128));
    b = y + (1.732446 * (u-128));
    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;
    pixel[0] = r * 220 / 256;
    pixel[1] = g * 220 / 256;
    pixel[2] = b * 220 / 256;

    pixel32 = (pixel[0] << 16 ) | (pixel[1] << 8) | (pixel[2]);
    return pixel32;
}

void process_yuv_image(unsigned char *yuv, int width, int height)
{
    unsigned int in, out = 0;
    unsigned int pixel_16;
    unsigned char pixel_24[3];
    unsigned int pixel32;
    int y0, u, y1, v;

    int pixel_num = 0;

    for(in = 0; in < width * height * 2; in += 4)
    {
        pixel_16 =
                yuv[in + 3] << 24 |
                yuv[in + 2] << 16 |
                yuv[in + 1] <<  8 |
                yuv[in + 0];
        y0 = (pixel_16 & 0x000000ff);
        u  = (pixel_16 & 0x0000ff00) >>  8;
        y1 = (pixel_16 & 0x00ff0000) >> 16;
        v  = (pixel_16 & 0xff000000) >> 24;

        pixel32 = convert_yuv_to_rgb_pixel(y0, u, v);
        pixel_num ++;
        lcd_draw_point(pixel_num%width,   pixel_num/width,  pixel32);


        //pixel_24[0] = (pixel32 & 0x000000ff);
        //pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        //pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        //rgb[out++] = pixel_24[0];
        //rgb[out++] = pixel_24[1];
        //rgb[out++] = pixel_24[2];
        pixel32 = convert_yuv_to_rgb_pixel(y1, u, v);
        pixel_num ++;
        lcd_draw_point(pixel_num%width,   pixel_num/width,  pixel32);
        //pixel_24[0] = (pixel32 & 0x000000ff);
        //pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        //pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        //rgb[out++] = pixel_24[0];
        //rgb[out++] = pixel_24[1];
        //rgb[out++] = pixel_24[2];
    }
    return ;


}

//清屏
void lcd_clear(int color)
{
    int i,j;
    for(i=0;i<480;i++)
        for(j=0;j<800;j++)
            lcd_draw_point(j,i,color);
}

//屏幕初始化
void lcd_init()
{
    //打开屏幕设备
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }

    //映射
    pfb = mmap(NULL, 800*480*4, PROT_WRITE|PROT_READ,MAP_SHARED, lcd_fd, 0);
    if(pfb == MAP_FAILED)
    {
        perror("open mmap error\n");
    }

    lcd_clear(0x00FFFFFF);
}

//.资源回收
void lcd_video_close()
{
    munmap(pfb,800*480*4);
    close(lcd_fd);
    printf("************game over!************\n");
}

int fd;
struct v4l2_fmtdesc check;
int ret;
struct v4l2_format s_fmt;
struct v4l2_requestbuffers reqbuf;
struct v4l2_buffer buf;

enum v4l2_buf_type type;

void V4l2()
{
    //初始化显示屏
    lcd_init();
    //1.打开摄像头对应的驱动文件
    //int fd;
    fd = open("/dev/video7",O_RDWR);
    if(fd < 0)
    {
        perror("open dev failed\n");
        //return 0;
    }
    //2.查询视频设备所支持的格式
    //struct v4l2_fmtdesc check;
    check.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    check.index = 0;
    //int ret;
    ret = ioctl(fd,VIDIOC_ENUM_FMT,&check);
    if(ret == 0)// return success
    {
        printf("format:%s\n",check.description);
    }
    //3.设置视频格式
    //struct v4l2_format s_fmt;
    s_fmt.fmt.pix.width = 640;
    s_fmt.fmt.pix.height = 480;
    s_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    s_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd,VIDIOC_S_FMT,&s_fmt);
    if(ret != 0)
    {
        perror("set format error\n");
        //return -1;
    }
    printf("pix.field=%d\n",s_fmt.fmt.pix.field);
    printf("pix.width=%d\n",s_fmt.fmt.pix.width);

    //4.申请内核态缓冲
    //struct v4l2_requestbuffers reqbuf;
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.count = 12;
    reqbuf.memory = V4L2_MEMORY_MMAP;

    ret = ioctl(fd,VIDIOC_REQBUFS,&reqbuf);
    if(ret != 0)
    {
        perror("reqbuf");
        //return -1;
    }else
    {
        printf("request buf success\n");
    }


    //5.查询内核缓冲
    //////////////////////////////////////////////
    //struct v4l2_buffer buf;
    int i;
    for(i = 0; i < 12; i++)
    {
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        ret = ioctl(fd,VIDIOC_QUERYBUF,&buf);
        if(ret != 0)
        {
            perror("querybuf");
            //return -1;
        }
        else
        {
            printf("querybuf success\n");
        }


        //6.把内核空间分配好的缓冲映射到用户空间
        /*struct userbuf{
            void *start;
            int length;
        };*/
        //struct userbuf ub;

        ub[i].length = buf.length;
        ub[i].start = mmap(0,buf.length,
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED,fd,buf.m.offset);
        if(ub[i].start == MAP_FAILED)
        {
            perror("map_failed");
            //return -1;
        }
        else
        {
            printf("ub[%d].len=%d\n",i,ub[i].length);
            printf("ub[%d].start = %#x",i,ub[i].start);
        }

        //7.添加到采集队列
        ret = ioctl(fd,VIDIOC_QBUF,&buf);
        if(ret != 0)
        {
            perror("add queue failed");
           // return -1;
        }
        else
        {
            printf("add queue success\n");
        }
    }


    //8.启动视频采集
    //enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd,VIDIOC_STREAMON,&type);
    if(ret != 0)
    {
        perror("start capture failed");
        //return -1;
    }
    else
    {
        printf("start capture success\n");
    }

    bzero(&buf,sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    //ShowVedio();
/*
    while (1)
    {

            //9.从队列中取出缓冲
            ret = ioctl(fd,VIDIOC_DQBUF,&buf);
            if(ret != 0)
            {
                perror(" dequeue failed");
                //return -1;
            }
            else
            {
                printf("out dequeue success\n");
            }

            //10.处理采集到的数据以及在lcd屏幕上显示出来

            process_yuv_image(ub[buf.index].start, 640, 480);
            //printf("ub[%d].start = %#x",buf.index,ub[buf.index].start);

            //11.将使用完的缓存区再放回采集队列
            ret = ioctl(fd,VIDIOC_QBUF,&buf);
            if(ret != 0)
            {
                perror("queue failed");
                //return -1;
            }
            //usleep(300);

    }

*/

/*
    //12.停止采集
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd,VIDIOC_STREAMOFF,&type);
    if(ret != 0)
    {
        perror("stop capture failed");
        //return -1;
    }
    else
    {
        printf("stop capture success\n");
    }

    //13.资源回收
    for(i = 0; i < 24; i++)
    {
        munmap(ub[i].start,ub[i].length);
    }

    close(fd);

    lcd_video_close();

    return 0;

*/
}

//void Resive()
//{
//    int j;
//    //12.停止采集
//    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    ret = ioctl(fd,VIDIOC_STREAMOFF,&type);
//    if(ret != 0)
//    {
//        perror("stop capture failed");
//        //return -1;
//    }
//    else
//    {
//        printf("stop capture success\n");
//    }
//
//    //13.资源回收
//    for(j = 0; j < 8; j++)
//    {
//        munmap(ub[j].start,ub[j].length);
//        printf("%d              frame\n",j);
//    }
//
//    close(fd);
//
//    printf("Befor game over\n");
//
//    lcd_video_close();
//}



void *ShowVedio()
{
    while (1)
    {

        //9.从队列中取出缓冲
        ret = ioctl(fd,VIDIOC_DQBUF,&buf);
        if(ret != 0)
        {
            perror(" dequeue failed");
            //return -1;
        }
        else
        {
            printf("out dequeue success\n");
        }

        //10.处理采集到的数据以及在lcd屏幕上显示出来

        process_yuv_image(ub[buf.index].start, 640, 480);
        //printf("ub[%d].start = %#x",buf.index,ub[buf.index].start);

        //11.将使用完的缓存区再放回采集队列
        ret = ioctl(fd,VIDIOC_QBUF,&buf);
        if(ret != 0)
        {
            perror("queue failed");
            //return -1;
        }
        //usleep(300);

    }

}















