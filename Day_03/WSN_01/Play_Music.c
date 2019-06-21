#include "Play_Music.h"
#include <unistd.h>

void Play_Music(char *music)
{
    execlp("madplay","madplay",music,NULL);
    //wait(&pid);
}