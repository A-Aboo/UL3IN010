#include <stdio.h>


void initTab(int *tab , int size){
    tab = malloc(sizeof(int) * size);
    for(int i =0 ; i < size ; i++){
        tab[i] = rand()*10;
    }
}
