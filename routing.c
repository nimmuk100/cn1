#include<stdio.h>
#include<stdlib.h>

int main(){
    printf("Routing details \n");
    int result=system("ip route");
    return result;
}