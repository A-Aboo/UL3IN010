#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <wait.h>
#include <sys/resource.h>

int main(void)
{
    for (int i = 0; i < 2; i++)
    {
        int id = fork();

        if (id == 0)
        {
            printf("Fils %d termine\n", getpid());
            exit(0);
        }
    }

    printf("Le pere dort pendant 10 secondes\n");

    sleep(10);

    wait(NULL);
    wait(NULL);

    return 0;
}