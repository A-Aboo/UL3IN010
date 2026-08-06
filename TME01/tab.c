#include "tab.h"

void initTab(int *tab , int size){
    srand(10);
    for(int i =0 ; i < size ; i++){
        tab[i] = rand() % 10;
    }
}

void printTab(int *tab, int size){
    for(int i =0 ; i < size ; i++){
        printf("%d\t", tab[i]);
    }
    printf("\n");
}