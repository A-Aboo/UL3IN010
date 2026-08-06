#include "tab.h"


int main(int argc, char **argv){
    int *tab1 = malloc(sizeof(int)  * NMAX);
    if(!tab1){
        perror("Error");
        return 1;
    }
    
    int tab2[NMAX];
    srand((unsigned int)time(NULL));

    initTab(tab1, 10);
    initTab(tab2, 10);

    printf("Tab dans le Tas \t");
    printTab(tab1, 10);

    printf("Tab dans la pile \t");
    printTab(tab2, 10);

    free(tab1);
    return 0;
}