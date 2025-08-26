#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUF_SIZE 4096

void *thread_func(void * c_fd){
        char buffer[BUF_SIZE];
        int client_fd = (int) c_fd;
        // 5. Communicate with client
        int bytes_read = read(client_fd, buffer, BUF_SIZE - 1);
        if (bytes_read <= 0) {
            printf("Client disconnected.\n");
        }

        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);

        // Echo back
        if (send(client_fd, buffer, bytes_read, 0) == -1) {
            perror("send failed");
        }
        close(client_fd);
    pthread_exit(0);
}