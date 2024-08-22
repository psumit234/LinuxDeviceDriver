#ifndef INTER_NODE_COMMUNICATION_H
#define INTER_NODE_COMMUNICATION_H
#include "circular_buffer.h"

void uart_send(DataPacket data);
DataPacket uart_receive();
void *app_to_uart_thread(void *arg);
void *uart_to_app_thread(void *arg);

#endif