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

    while(cb->count == BUFFER_SIZE){
        printf("Buffer is full, waiting for consumer to consume\n");
        pthread_cond_wait(&cb->not_full, &cb->lock);
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;

    pthread_cond_signal(&cb->not_empty);
    pthread_mutex_unlock(&cb->lock);
}

DataPacket buffer_remove(CircularBuffer *cb){
    pthread_mutex_lock(&cb->lock);

    while(cb->count == 0){
        printf("Buffer is empty, waiting for producer to insert\n");
        pthread_cond_wait(&cb->not_empty, &cb->lock);
    }

    DataPacket data = cb->buffer[cb->tail];
    cb->tail = (cb->tail +1 )% BUFFER_SIZE;
    cb->count--;

    pthread_cond_signal(&cb->not_full);
    pthread_mutex_unlock(&cb->lock);

    return data;
}