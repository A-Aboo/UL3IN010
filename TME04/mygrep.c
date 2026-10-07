#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <wait.h>
#include <sys/resource.h>

int main(int argc, char ** argv){
    int nb_fils = 0;
    int MAX = 5;
   for (int i = 2 ; i < argc ; i++){
    if ( nb_fils == MAX){
        wait(NULL);
        nb_fils--;
    }
    int id = fork();
    if ( id == 0){
        execl("/usr/bin/grep",  "grep",  argv[1] ,  argv[i] , NULL );
        // f child did not transformed to to execl then a error happend 
        
        perror("execl");
        exit(1);
    }else{
        nb_fils++;
    }
   }
    while (nb_fils > 0){
        struct rusage usage;
        int pid = wait3(NULL, 0, &usage);
        printf("Fils %d\n", pid);
        printf("CPU utilisateur : %ld.%06ld s\n",usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("CPU systeme     : %ld.%06ld s\n",usage.ru_stime.tv_sec,usage.ru_stime.tv_usec);
        nb_fils--;
    }
   
    //    for ( int i =2 ; i  < argc ; i++){
    //     wait(NULL);
    //    }
   return 0;
}