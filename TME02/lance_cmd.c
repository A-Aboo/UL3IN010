#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

void lance_command(char *cmd)
{
    struct tms before;
    struct tms after;
    clock_t total_before;
    clock_t total_after;
    long ticks;
    int res;

    ticks = sysconf(_SC_CLK_TCK);

    total_before = times(&before);

    res = system(cmd);

    total_after = times(&after);

    if (res == -1 || !WIFEXITED(res) || WEXITSTATUS(res) != 0)
        fprintf(stderr, "Error\n");

    printf("\nStatistiques de \"%s\" :\n", cmd);

    printf("Temps total : %.6f\n",
        (double)(total_after - total_before) / ticks);

    printf("Temps utilisateur : %.6f\n",
        (double)(after.tms_utime - before.tms_utime) / ticks);

    printf("Temps systeme : %.6f\n",
        (double)(after.tms_stime - before.tms_stime) / ticks);

    printf("Temps utilisateur fils : %.6f\n",
        (double)(after.tms_cutime - before.tms_cutime) / ticks);

    printf("Temps systeme fils : %.6f\n",
        (double)(after.tms_cstime - before.tms_cstime) / ticks);
}


int main(int argc, char **argv){
    for (int i = 1 ; i < argc; i++){
        lance_command(argv[i]);
    }
    return 0;
}