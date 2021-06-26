#include "socketprogram.h"

int readline(int fd, char *buf)
{
    int haveReadCharNum = 0;
    const int READONCE = 0xf;
    char tmpbuf[READONCE + 1];
    while (read(fd, tmpbuf, READONCE) != 0 && haveReadCharNum < MAXLINE)
    {
        for (int i = 0; i < READONCE; ++i)
        {
            buf[haveReadCharNum] = tmpbuf[i];
            ++haveReadCharNum;
            if (buf[haveReadCharNum - 1] == '\n')
            {
                return haveReadCharNum;
            }
        }
    }
    return haveReadCharNum;
}