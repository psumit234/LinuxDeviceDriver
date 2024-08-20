# Simple Character Device Driver

## Overview

This project demonstrates a basic Linux character device driver that supports basic file operations like `open`, `close`, `read`, and `write`. The driver registers itself with a specific major number and interacts with user-space applications through a device file in the `/dev/char/` directory.

## Features

- Registers a character device with the Linux kernel.
- Supports basic file operations: `open`, `close`, `read`, and `write`.
- Provides example user-space applications to test the driver.
- Uses a specific major number (e.g., 108) for the device registration.

## File Structure

```bash
char_device_driver/
│
├── Makefile                    # Build instructions for the kernel module
├── README.md                   # This documentation file
├── src/                        # Source code for the kernel module
│   ├── char_device_driver.c    # Main character device driver implementation
│   └── char_device_driver.h    # Header file for the character device driver
├── test/                       # User-space applications for testing the driver
│   ├── test_read.c             # Test application to read from the device
│   └── test_write.c            # Test application to write to the device
└── include/                    # Additional header files
    └── char_device_driver.h    # Header file for device driver (same as in src/)
```

## Prerequisites
- Linux system with kernel Headers installed.
- Basic Understanding of Linux kernel Module development.
- GCC and Make installed on your system.

## Build and Install

1. Clone the Repository
```bash
git clone <repository-url>
cd char_device_driver
```

2. Build the Kernel Module 
```bash
make 
```
3. Insert The Module 
```bash
sudo insmod src/char_device_driver.ko 
```

4. Create the Device File
    You need to create a device file in `/dev/char/` to interact with driver:
```bash
    sudo mkdir -p /dev/char
    sudo mknod /dev/char/my_char_device c 108 0
     
```

## Testing 
### Write to the Device
1. Compile the test application:
```bash
gcc -o test/test_write test/test_write.c
```
2. Run the test application to write data to the device:
```bash
./test/test_write

```
### Read from the Device
1. Compile the test application:
```bash
gcc -o test/test_read test/test_read.c
```
2. Run the test application to write data to the device:
```bash
./test/test_read

```

## Unistall the Module
1. Remove the Module
```bash
sudo rmmod char_device_driver
```

2. Clean Up the Build Files
```bash
make clean
```
## License
- This project is licensed under the MIT License - see the LICENSE file for details.
