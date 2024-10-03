#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_ip_class(char *ip) {
    char *token = strtok(ip, ".");
    if (token != NULL) {
        int first_octet = atoi(token);

        // Determine the class based on the first octet
        if (first_octet >= 1 && first_octet <= 126) {
            printf("Class A\n");
        } else if (first_octet >= 128 && first_octet <= 191) {
            printf("Class B\n");
        } else if (first_octet >= 192 && first_octet <= 223) {
            printf("Class C\n");
        } else if (first_octet >= 224 && first_octet <= 239) {
            printf("Class D\n");
        } else if (first_octet >= 240 && first_octet <= 255) {
            printf("Class E\n");
        } else {
            printf("Invalid IP Address\n");
        }
    } else {
        printf("Invalid IP Address\n");
    }
}

int main() {
    char ip[16]; // Buffer to store the IP address (maximum 15 characters + null terminator)

    printf("Enter an IP address: ");
    fgets(ip, sizeof(ip), stdin); // Read user input

    // Remove the newline character if present
    ip[strcspn(ip, "\n")] = 0;

    find_ip_class(ip);
    return 0;
}
