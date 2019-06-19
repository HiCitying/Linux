#include "Show_Word.h"
#include "DrawPoint.h"


void Show_Word(char *word,int *py,int x, int y,int wide,int wordsize,int color)
{
    int i,j;
    int x1; //横坐标
    int y1;	//纵坐标
    int by = wide/8; //
    for(i = 0; i < wordsize; i++)	//遍历每个字节
    {
        for(j = 7; j >= 0; j--)		//遍历某个字节的每个位
        {
            if(word[i] & (1 << j))
            {
                x1 = x + 8 *(i % by)/*确定区域是在哪个字节*/+ 7 -j; /*确定是字节中的哪个位*/
                y1 = y + i / by;
                DrawPoint(py,x1,y1,color);//在对应位置的像素点上 上色
            }
        }
    }
}