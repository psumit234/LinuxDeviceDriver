#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/char"  // Replace with your device file path

int main() {
	int fd;
	char buffer[] = "Hello, World!";

	fd = open(DEVICE, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open the device");
		return 1;
	}

	write(fd, buffer, sizeof(buffer));
	printf("Written to device: %s\n", buffer);

	close(fd);
	return 0;
}
