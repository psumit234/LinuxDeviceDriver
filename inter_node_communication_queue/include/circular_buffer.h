#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "data.h"
#include <pthread.h>

#define BUFFER_SIZE 1024

typedef struct{
    DataPacket buffer[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} CircularBuffer;

void init_buffer(CircularBuffer *cb);
void buffer_add(CircularBuffer *cb, DataPacket data);
DataPacket buffer_remove(CircularBuffer *cb);

#endif