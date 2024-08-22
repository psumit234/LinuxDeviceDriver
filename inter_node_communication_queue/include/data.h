#ifndef _DATA_H
#define _DATA_H

#include <stdint.h>
#define MAX_DATA_SIZE 1024

typedef struct{
    uint16_t id;
    uint8_t data[MAX_DATA_SIZE];
    uint8_t length;
} DataPacket;
#endif 