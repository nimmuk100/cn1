#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char *message;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    printf("Socket created\n");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to server IP if needed

    // Infinite loop to keep connecting
    while (1) {
        // Connect to the server
        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            perror("Connect failed. Retrying...");
            sleep(2);  // Wait for a bit before retrying
            continue;  // Retry connecting
        }

        // Send a message to the server
        message = "Hello Server!";
        if (send(sock, message, strlen(message), 0) < 0) {
            printf("Send failed\n");
            break;
        }

        // Receive a reply from the server
        char server_reply[2000] = {0};
        if (recv(sock, server_reply, sizeof(server_reply), 0) < 0) {
            printf("Receive failed\n");
            break;
        }

        printf("Server reply: %s\n", server_reply);

        // Close the socket after communication
        close(sock);
        sleep(2);  // Wait before reconnecting
    }

    return 0;
}
