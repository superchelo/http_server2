#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5
#define BUF_SIZE 4096

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    // 1. Create socket (IPv4, TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind to IP/port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen for connections
    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("TCP server listening on port %d...\n", PORT);

    // 4. Accept a client connection
    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len)) == -1) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected!\n");

    // 5. Communicate with client
    while (1) {
        int bytes_read = read(client_fd, buffer, BUF_SIZE - 1);
        if (bytes_read <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);

        // Echo back
        if (send(client_fd, buffer, bytes_read, 0) == -1) {
            perror("send failed");
            break;
        }
    }

    // 6. Clean up
    close(client_fd);
    close(server_fd);
    return 0;
}
