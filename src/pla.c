#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "pla.h"
#include "main.h"

int readPLA (char* path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Failed to open file: %s\n", path);
        return -1;
    }
    int len = lseek(fd, 0, SEEK_END);
    const char* PlaData = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);

    printf("PLA file loaded: %s\n", path);

    printf("%.8s\n", &PlaData[0x0041]);
    printf("Planet name: %.21s\n", &PlaData[0x0002]);

    switch (PlaData[0x98F4])
    {
        case 0x00:
            printf("Time Scale: %s\n", "No Game");
            break;
        case 0x01:
            printf("Time Scale: %s\n", "Geologic");
            break;
        case 0x02:
            printf("Time Scale: %s\n", "Evolution");
            break;
        case 0x03:
            printf("Time Scale: %s\n", "Civilization");
            break;
        case 0x04:
            printf("Time Scale: %s\n", "Technology");
            break;
        case 0x05:
            printf("Time Scale: %s\n", "Daisyworld");
            break;
    }

    glBindBuffer(GL_ARRAY_BUFFER, Engine.instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, 0x4000, &PlaData[0x0080], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    close(fd);

    return 0;
}
