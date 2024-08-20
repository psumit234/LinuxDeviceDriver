#include <stdio.h>
#include <fnctl.h>
#include <unistd.h>


#define DEVICE_NAME "/dev/char"

int main(){
    int fd;
    char buffer[100];
    fd = open(DEVICE_NAME, O_RDONLY);
    if(fd < 0){
        perror("Failed to open the device...");
        return 1;
    }
    read(fd,buffer, sizeof(buffer));
    printf("Data read from the device: %s\n", buffer);
    close(fd);
    return 0;
}