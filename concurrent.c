#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 2000

int main() {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char client_message[BUFFER_SIZE] = {0};
    char server_message[BUFFER_SIZE] = {0};
    pid_t child_pid;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    printf("Socket created \n");

    // Prepare server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind the socket
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    printf("Bind successful \n");

    // Listen for incoming connections
    listen(socket_desc, 3);
    printf("Server is listening \n");

    // Accept and handle incoming connections concurrently
    while (1) {
        c = sizeof(struct sockaddr_in);
        new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
        if (new_socket < 0) {
            printf("Accept failed\n");
            return 1;
        }
        printf("Connection accepted\n");

        // Fork a new process for each client
        child_pid = fork();
        if (child_pid == 0) {  // Child process
            close(socket_desc);  // Child does not need access to the main socket

            // Interaction loop with the client
            while (1) {
                // Clear client message buffer
                memset(client_message, 0, BUFFER_SIZE);

                // Receive message from client
                int valread = recv(new_socket, client_message, BUFFER_SIZE, 0);
                if (valread > 0) {
                    client_message[valread] = '\0';  // Null-terminate the client message
                    printf("Client: %s\n", client_message);

                    // Get the server's response
                    printf("Enter message to client: ");
                    fgets(server_message, BUFFER_SIZE, stdin);

                    // Send the server's message to the client
                    send(new_socket, server_message, strlen(server_message), 0);
                } else {
                    printf("Client disconnected\n");
                    break;  // Exit the loop if client disconnects
                }
            }

            // Close the client socket in the child process
            close(new_socket);
            exit(0);  // End child process
        }
        else {
            // Parent process continues to accept new clients
            close(new_socket);  // Parent closes the new socket, but it's open in the child
        }
    }

    close(socket_desc);  // Close the main server socket (though unreachable in this case)
    return 0;
}
