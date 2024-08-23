# Inter-Node Communication using Circular buffer

## Overview

This project demonstrates the implementation of a circular buffer in C, designed to facilitate communication between multiple applications and a UART interface. The circular buffer stores data in a thread-safe manner, allowing it to be sent and received via UART, enabling efficient inter-node communication.

## Project Structure
├── include
│ ├── circular_buffer.h # Header file for the circular buffer
│ ├── communication.h # Header file for UART communication
│ ├── Uart.h # UART driver header file
├── src
│ ├── circular_buffer.c # Implementation of the circular buffer
│ ├── communication.c # UART communication functions
├── test
│ ├── main.c # Main application
├── Makefile # Makefile to build the project
├── README.md # Project documentation



### Description of Files

- **include/circular_buffer.h**: Declares the functions and structures used in the circular buffer implementation.
- **include/communication.h**: Declares the functions for handling UART communication.
- **include/Uart.h**: The header file for the UART driver, containing function declarations such as `Uart_Init`, `Uart_AsyncSend`, and `Uart_AsyncReceive`.
- **src/circular_buffer.c**: Contains the implementation of the circular buffer, including functions for adding and removing data packets.
- **src/communication.c**: Implements the logic for communicating between the buffer and UART.
- **test/main.c**: The main application that initializes the system, creates threads, and simulates data flow between applications and UART.
- **Makefile**: A makefile to build the project.

## How to Build

To build the project, ensure you have a C compiler installed (e.g., `gcc`). Navigate to the root directory of the project and run:

```bash
make
```

This command will compile the source files located in `src` and produce an executable named `main` in the `test` directory.

## How to Run
After building the project, navigate to the `test` directory and run the executable:
```bash
./main
```
The application will initialize the circular buffer and UART communication. It creates threads to handle the data flow between the buffer and UART, simulating an application that adds data to the buffer and processes it through UART.