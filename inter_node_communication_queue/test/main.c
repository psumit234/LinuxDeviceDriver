#include "circular_buffer.h"
#include "inter_node_communication.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    volatile Uart_StatusType Uart_Status;
    volatile Std_ReturnType Std_Uart_Status;
    uint32_t varRemainingBytes;
    
    Std_Uart_Status = E_NOT_OK;

    // Initialize the Mcu Driver
    Mcu_Init(NULL_PTR);

    // Initialize the clock tree and apply PLL as system clock
    Mcu_InitClock(McuClockSettingConfig_0);

    while( MCU_PLL_LOCKED != Mcu_GetPllStatus()){
        // Wait for the PLL to lock
    }

    // Distribute the PLL across the clock tree
    Mcu_DistributePllClock();

    // Apply a mode configuration
    Mcu_SetMode(McuModeSettingConf_0);

    // Initialize pins
    Port_Init(NULL_PTR);

    // Initialize IRQs
    Platform_Init(NULL_PTR);
    Platform_InstallIrqHandler(LINFLEXD1_IRQn, LINFLEXD1_UART_IRQHandler, NULL_PTR);

    // Initialize the Circuler Buffer
    CircularBuffer cb;
    init_buffer(&cb);

    // Initialize an UART Driver
    Uart_Init(&Uart_xConfig_BOARD_InitPeripherals);

    // Create a thread to send data from the buffer to UART
    pthread_t app_uart_thread, uart_app_thread;

    pthread_create(&app_uart_thread, NULL, app_to_uart_thread, &cb);
    pthread_create(&uart_app_thread, NULL, uart_to_app_thread, &cb);

    pthread_join(app_uart_thread, NULL);
    pthread_join(uart_app_thread, NULL);

    return 0;
}