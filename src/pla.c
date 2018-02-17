#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "pla.h"

int readPLA (char* path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Failed to open file: %s\n", path);
        return -1;
    }
    int len = lseek(fd, 0, SEEK_END);
    const char* fileData = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);

    printf("PLA file loaded: %s\n", path);

    close(fd);

    return 0;
}
