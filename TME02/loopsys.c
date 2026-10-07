#include <stdio.h>
#include <unistd.h>
int main(){
    long long i  = 0;
    while (i  < 50000000){
        getpid();
        i++;
    }


    return 0;
}