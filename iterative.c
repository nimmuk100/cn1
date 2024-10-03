#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char client_message[2000] = {0};

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    printf("Socket created\n");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind the socket
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed. Error");
        return 1;
    }
    printf("Bind done\n");

    // Listen for incoming connections
    listen(socket_desc, 3);
    printf("Waiting for incoming connections...\n");

    // Loop to accept multiple clients
    while (1) {
        c = sizeof(struct sockaddr_in);
        new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (new_socket < 0) {
            perror("Accept failed");
            continue; // Continue to accept next connection
        }
        printf("Connection accepted\n");

        // Clear client_message buffer
        memset(client_message, 0, sizeof(client_message));

        // Receive a message from the client
        recv(new_socket, client_message, sizeof(client_message), 0);
        printf("Client message: %s\n", client_message);

        // Send a reply to the client
        char *message = "Hello Client, I received your message.";
        write(new_socket, message, strlen(message));

        // Close the connected socket
        close(new_socket);
        printf("Connection closed\n");
    }

    // Close the listening socket (not reachable in this version)
    close(socket_desc);
    return 0;
}
