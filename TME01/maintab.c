#include "tab.h"


int main(int argc, char **argv){

    int *tab1 = malloc(sizeof(int)  * NMAX);
    if(!tab1){
        perror("Error");
        return 1;
    }
    
    (void)argc;
    (void)argv;
    int tab2[NMAX];
    srand((unsigned int)time(NULL));
    
    printMem("before");

    initTab(tab1, NMAX);
    
    printMem("after");
    initTab(tab2, NMAX);
   // printf("Tab dans le Tas \t");
  //  printTab(tab1, NMAX);

  //  printf("Tab dans la pile \t");
 //   printTab(tab2, NMAX);

    printf("sum du tableau1 %d \n"  ,sumTab(tab1, NMAX));
    int min;

    printf("somme du tab2 %d" , MinSubTab(&min, tab2 , NMAX));
    printf("   min  %d\n" , min);
    
    
    free(tab1);
    return 0;
}   