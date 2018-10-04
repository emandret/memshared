#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct s_shared
{
    unsigned int x;
    unsigned int y;
    char str[1024];
};
