#include <stdio.h>
#include <unistd.h>



int main( int argc, char **argv){
    // long long i = 5000000000;
    // long long j = 0;
    // while (j  < i)
    //     j++;
    long long i = 50000000;
    long long j = 0;
    while ( j < i){
        getpid();
        j++;
    }
    

    return 0;
}