#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Network Information:\n");

    // Get and display hostname
    printf("\nHostname:\n");
    system("hostname");

    // Get and display IP address
    printf("\nIP Address:\n");
    system("hostname -I");

    // Get and display MAC address
    printf("\nMAC Address:\n");
    system("ip link show | grep 'ether'");

    return 0;
}
