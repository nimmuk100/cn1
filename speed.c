#include<stdio.h>
#include<stdlib.h>

int main(){
    printf("Speed test \n");
    int result=system("speedtest-cli");
    return result;
}