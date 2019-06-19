#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int init_serial(const char *file, int baudrate);
#endif