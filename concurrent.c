#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

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

    // Accept an incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        if (new_socket < 0) {
            perror("Accept failed");
            return 1;
        }
        printf("Connection accepted\n");

        // Create child process using fork()
        if (fork() == 0) {
            // Child process: handles client
            recv(new_socket, client_message, 2000, 0);
            printf("Client message: %s\n", client_message);

            // Send reply
            char *message = "Hello Client, I received your message.";
            write(new_socket, message, strlen(message));

            // Close the socket for the client
            close(new_socket);
            return 0;  // Child process terminates
        } else {
            // Parent process: closes the new socket and waits for another client
            close(new_socket);
            // Optional: wait for child process to finish (not mandatory)
            wait(NULL);
        }
    }

    if (new_socket < 0) {
        perror("Accept failed");
        return 1;
    }

    // Close the main socket
    close(socket_desc);
    return 0;
}
