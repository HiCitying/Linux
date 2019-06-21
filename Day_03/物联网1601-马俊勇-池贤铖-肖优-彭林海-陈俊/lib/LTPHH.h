#ifndef _LTPHH_H_
#define _LTPHH_H_

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//void LTPHH(int *py,int *L,int *T,int *P,int *H1,int *H2,int flag);
//void LTPHH(int *p,int flag);
void *LTPHH(void *arg);

#endif