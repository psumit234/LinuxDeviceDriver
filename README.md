# Linux Device Driver Projects

This repository contains a collection of Linux device driver examples designed for learning and experimentation on a standard laptop. These projects cover various aspects of Linux kernel development, including character and block devices, interrupt handling, and interfacing with user space through `procfs` and `sysfs`.

## Projects Overview

### 1. Basic Character Device Driver

**Objective**: Implement a simple character device driver that supports basic read and write operations.

**Key Features**:

- Registers a character device with the Linux kernel.
- Supports operations like `open`, `close`, `read`, and `write`.
- Creates a `/dev/simplechar` file for user-space interaction.

### 2. Pseudo-Random Number Generator Driver

**Objective**: Develop a character device driver that returns pseudo-random numbers.

**Key Features**:

- Generates random numbers using kernel space functions.
- Provides random numbers through read operations on the `/dev/randomnum` file.

### 3. Virtual Block Device Driver

**Objective**: Create a virtual block device that acts as a ramdisk.

**Key Features**:

- Implements a block device driver managing a memory buffer.
- Supports read and write operations through the block device interface.
- Mountable as a filesystem using a file like `/dev/vramdisk`.

### 4. LED Control Simulation Driver

**Objective**: Simulate an LED control driver that toggles "LED" state via user commands.

**Key Features**:

- Implements simple IOCTL commands to control LED states.
- Simulates LED on/off and blink actions, logging the state to the kernel log.

### 5. ProcFS/SysFS Interface Driver

**Objective**: Interact with user space via the `/proc` or `/sys` filesystem.

**Key Features**:

- Creates entries in `/proc` or `/sys` to display and control driver states.
- Allows read/write operations from user space to modify driver behavior.

### 6. Simulated Temperature Sensor Driver

**Objective**: Develop a driver that simulates temperature sensor readings.

**Key Features**:

- Returns simulated temperature readings in Celsius or Fahrenheit.
- Updates temperature values periodically using kernel timers.
- Allows mode switching via IOCTL.

### 7. Interrupt Handling Driver

**Objective**: Create a driver that handles simulated interrupts.

**Key Features**:

- Implements an Interrupt Service Routine (ISR).
- Triggers interrupts using kernel timers or software interrupts.
- Logs interrupt handling events using `dmesg`.

### 8. Keyboard Input Logger Driver

**Objective**: Log keyboard inputs to the kernel log or a specific file.

**Key Features**:

- Captures and logs keyboard events.
- Filters specific key inputs.
- Logs keypress and key release events.

## Getting Started

### Prerequisites

- **Linux Kernel Headers**: Ensure that your system has the Linux kernel headers installed.
- **Development Tools**: Install `gcc`, `make`, and other development tools required for compiling kernel modules.

### Setup and Compilation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/LinuxDeviceDriver.git
   cd LinuxDeviceDriver
   ```

2. Navigate to the desired project directory:

   ```bash
   cd BasicCharacterDriver
   ```

3. Compile the driver:

   ```bash
   make
   ```

4. Load the driver:

   ```bash
   sudo insmod simplechar.ko
   ```

5. Interact with the driver:

   ```bash
   echo "Hello, Driver!" > /dev/simplechar
   cat /dev/simplechar
   ```

6. Unload the driver:
   ```bash
   sudo rmmod simplechar
   ```

### Note

- Always ensure you have a backup or are working in a safe environment (e.g., a virtual machine) when testing drivers.
- Modifying kernel space can potentially cause system instability.

## Contribution

Feel free to contribute to this repository by adding new drivers, improving existing code, or enhancing documentation.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
