# Pseudo-Random Number Generator Character Device Driver

## Overview

This project implements a simple Linux kernel character device driver that generates pseudo-random numbers. The driver creates a device file `/dev/randomnum` that, when read, returns a pseudo-random integer to the user space.

## Project Structure

- **src/**: Contains the main driver source code (`randomnum.c`).
- **include/**: Contains the header file (`randomnum.h`).
- **test/**: Contains a test program (`test_randomnum.c`) that reads random numbers from the device.
- **Makefile**: Used to build the kernel module.

## How It Works

- The driver uses the kernel function `get_random_bytes` to generate random numbers in kernel space.
- When the user performs a read operation on `/dev/randomnum`, the driver generates a random number and copies it to the user space.
- The driver logs relevant information to the kernel log, viewable via `dmesg`.

## Requirements

- A Linux system with kernel headers installed.
- Basic knowledge of building and loading Linux kernel modules.

## Building the Driver

1. Clone the repository or copy the project files to your development environment.
2. Navigate to the root of the project directory.
3. Run the following command to build the driver:

    ```bash
    make
    ```

   This will compile the driver and generate the `randomnum.ko` kernel module.

## Loading the Driver

1. Load the kernel module using `insmod`:

    ```bash
    sudo insmod src/randomnum.ko
    ```

2. Verify that the driver has been loaded and the device file has been created:

    ```bash
    ls /dev/randomnum
    ```

    You should see `/dev/randomnum` listed.

3. You can also check the kernel log for initialization messages:

    ```bash
    dmesg | tail
    ```

## Testing the Driver

1. Compile the test program located in the `test/` directory:

    ```bash
    gcc test/test_randomnum.c -o test/test_randomnum
    ```

2. Run the test program to read a random number from the device:

    ```bash
    ./test/test_randomnum
    ```

    This should output a random integer generated by the driver.

## Unloading the Driver

1. To unload the driver, use `rmmod`:

    ```bash
    sudo rmmod randomnum
    ```

2. Check the kernel log to ensure the driver has been unloaded:

    ```bash
    dmesg | tail
    ```

## Cleanup

To clean up the build artifacts, run:

```bash
make clean
```

## License

This project is licensed under the GPLv2 License.

## Author

SUMIT KUMAR PATEL

## Version

0.1