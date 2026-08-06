#ifndef TAB_H
#define TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#ifndef NMAX
# define NMAX 1000000
#endif 

void initTab(int *tab , int size);
void printTab(int *tab, int size);
int sumTab(int *tab, int size);
int MinSubTab(int *min , int *tab, int size);
void printMem(char *message);

#endif
