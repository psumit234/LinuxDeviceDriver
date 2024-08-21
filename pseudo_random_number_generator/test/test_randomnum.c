#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd;
    int random_number;

    fd = open("/dev/randomnum", O_RDONLY);
    if(fd < 0){
        perror("Failed to open the device...");
        return -1;
    }

    read(fd, &random_number, sizeof(random_number));
    printf("Random number: %d\n", random_number);

    close(fd);
    return 0;
    
}