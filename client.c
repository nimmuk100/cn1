#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000] = {0};

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    // Define the server's address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    // Connect to the server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 1;
    }
    printf("Connected to server\n");

    // Send a message to the server
    message = "Hello Server!";
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        printf("Send failed\n");
        return 1;
    }

    // Receive a reply from the server
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        printf("Receive failed\n");
    }
    printf("Server reply: %s\n", server_reply);

    // Close the socket
    close(socket_desc);

    return 0;
}
