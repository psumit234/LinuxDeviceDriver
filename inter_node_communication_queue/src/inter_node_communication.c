#include "inter_node_communication.h"

// send data from buffer to UART
void *app_to_uart_thread(void *arg){
    CircularBuffer *cb = (CircularBuffer *)arg;
    volatile uint32_t varRemainingBytes;

    while(1){
        // Get data from the buffer
        DataPacket data = buffer_remove(cb);


        // Send data to UART
        Uart_AsyncSend(UART_CHANNEL, data.data, data.length);
        while(Uart_GetStatus(UART_CHANNEL, &varRemainingBytes, UART_SEND) == UART_STATUS_OPERATION_ONGOING);
    }
}


// receive data from UART to buffer
void *uart_to_app_thread(void *arg){
    CircularBuffer *cb = (CircularBuffer *)arg;
    volatile uint32_t varRemainingBytes;
    volatile Uart_StatusType Uart_Status;
    uint8_t Rx_Buffer[PAYLOAD_SIZE];   // Adjust size to match your payload size

    while(1){
        // Receive data from UART
        Uart_AsyncReceive(UART_CHANNEL, Rx_Buffer, sizeof(Rx_Buffer));
        while(Uart_GetStatus(UART_CHANNEL, &varRemainingBytes,UART_RECEIVE) == UART_STATUS_OPERATION_ONGOING);

        // Check if the received data is error-free
        Uart_Status = Uart_GetStatus(UART_CHANNEL, &varRemainingBytes, UART_RECEIVE);
        if(Uart_Status != UART_STATUS_NO_ERROR){
            // If error, send error message and continue
            Uart_AsyncSend(UART_CHANNEL, (const uint8_t *)ERROR_MSG, strlen(ERROR_MSG));
            while(Uart_GetStatus(UART_CHANNEL, &varRemainingBytes, UART_SEND) == UART_STATUS_OPERATION_ONGOING);
            continue;
        }

        // Store received data in the circular buffer
        DataPacket data;
        data.id = 0; // Set the ID as needed
        memcpy(data.data, Rx_Buffer, sizeof(Rx_Buffer));
        data.length = sizeof(Rx_Buffer);
        buffer_add(cb, data);
    }
}