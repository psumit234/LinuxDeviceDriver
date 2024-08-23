#ifndef INTER_NODE_COMMUNICATION_H
#define INTER_NODE_COMMUNICATION_H
#include "circular_buffer.h"
#include "Muc.h"
#include "Uart.h"
#include "Platform.h"
#include "Linflexd_Uart_Ip_Irq.h"
#include "Port.h"
#include "check_example.h"
#include <string.h>
#define UART_CHANNEL  0U

#define ERROR_MSG "An error occurred! The application will stop!\r\n"

void uart_send(DataPacket data);
DataPacket uart_receive();
void *app_to_uart_thread(void *arg);
void *uart_to_app_thread(void *arg);

#endif