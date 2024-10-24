#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 2000

int main() {
    int socket_desc;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    // Server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost
    server.sin_port = htons(8888);

    // Connect to the server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }
    printf("Connected to the server...\n");

    // Continuous interaction with the server
    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to the server
        send(socket_desc, buffer, strlen(buffer), 0);

        // Receive and display server's response
        int valread = recv(socket_desc, buffer, BUFFER_SIZE, 0);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Server: %s\n", buffer);
        } else {
            printf("Connection closed by server\n");
            break;  // Exit the loop if server disconnects
        }
    }

    // Close the socket when done
    close(socket_desc);
    return 0;
}
