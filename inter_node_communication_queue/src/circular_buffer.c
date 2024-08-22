#include "circular_buffer.h"

void init_buffer(CircularBuffer *cb)
{
    cb->head = 0;
    cb->tail = 0;
    cb->count =0;
    pthread_mutex_init(&cb->lock,NULL);
    pthread_cond_init(&cb->not_full,NULL);
    pthread_cond_init(&cb->not_empty,NULL);
}

void buffer_add(CircularBuffer *cb, DataPacket data){
    pthread_mutex_lock(&cb->lock);

    pthread_mutex_unlock(&cb->lock);
}