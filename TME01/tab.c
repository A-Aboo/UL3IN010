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

int sumTab(int *tab, int size){
    int i =0 ;
    for (int j =0 ;j  <size ; j++){
        i += tab[j];
    }
    return i;
}

int MinSubTab(int *min , int *tab, int size){
    int m = tab[0];
    int s = 0;
    for(int i =0  ; i < size ; i++ ){
        if (m > tab[i]){
            m = tab[i];
        }  
        s += tab[i];

    }

    *min = m;
    return s ;
    // ou return subTab(tab,size);
}

void printMem(char *message){
    struct rusage usage;
    if(getrusage(RUSAGE_SELF , &usage ) == -1){
        perror("Error");
        return ;
    }
    printf("%s , %ld \n" ,message,  usage.ru_maxrss );
}