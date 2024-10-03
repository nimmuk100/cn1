#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Server port number

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed. Error");
        return 1;
    }
    printf("Connected to server\n");

    // Communicate with the server
    while (1) {
        printf("Enter message: ");
        fgets(message, 2000, stdin);

        // Send some data to the server
        if (send(sock, message, strlen(message), 0) < 0) {
            printf("Send failed\n");
            return 1;
        }

        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0) {
            printf("Receive failed\n");
            break;
        }
        printf("Server reply: %s\n", server_reply);

        // Exit if message is "exit"
        if (strncmp(message, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }
    }

    // Close the socket
    close(sock);

    return 0;
}
