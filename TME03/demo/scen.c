#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sched.h>

#define LONGTIME 8E8
void ProcLong(int *);
void ProcCourt(int *);

// Exemple de processus long (une simple bouble),
// Chaque processus long cr�e a son tour 4 processus courts
//
void ProcLong(int *pid) {
  long i;
  static int cpt = 0;

  for (i=0;i<LONGTIME;i++) {
    if (i%(long)(LONGTIME/4) == 0)  {
      int *tcpt = (int *) malloc(sizeof(int));
      *tcpt = cpt;
      CreateProc((function_t)ProcCourt,(void *)tcpt, 10);
      cpt++;
    }
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Long %d - %ld\n",*pid, i);
  }
  printf("############ FIN LONG %d\n\n", *pid );
}


// Processus court
void ProcCourt(int *pid) {
  long i;

  for (i=0;i<LONGTIME/10;i++)
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Court %d - %ld\n",*pid, i);
  printf("############ FIN COURT %d\n\n", *pid );
}




// Exemples de primitive d'election definie par l'utilisateur
// Remarques : les primitives d'election sont appel�es directement
//             depuis la librairie. Elles ne sont app�l�es que si au
//             moins un processus est � l'etat pret (RUN)
//             Ces primitives manipulent la table globale des processus
//             d�finie dans sched.h


// Election al�atoire
int RandomElect(void) {
  int i;

  printf("RANDOM Election !\n");

  do {
    i = (int) ((float)MAXPROC*rand()/(RAND_MAX+1.0));
  } while (Tproc[i].flag != RUN);

  return i;
}


// Election de SJF "Shortest Job Fisrt"
int SJFElect(void) {
    int p = -1;
    int i = 0;
    double min = 0;

    printf("SJF Election !\n");

    while (i < MAXPROC) {

        if (Tproc[i].flag == RUN) {

            if (p == -1 || Tproc[i].duration < min) {
                min = Tproc[i].duration;
                p = i;
            }
        }

        i++;
    }

    return p;
}

// Approximation SJF
int ApproxSJF(void) {
    int p = -1;
    int i = 0;
    double min = 0;

    int x = -1;
    struct timeval now;

    gettimeofday(&now, NULL);

    printf("Approx SJF Election !\n");

    while (i < MAXPROC) {
        if (Tproc[i].flag == RUN) {

            // ApproxSJF normal
            if (p == -1 || Tproc[i].ncpu < min) {
                min = Tproc[i].ncpu;
                p = i;
            }
            // famine av
            if (now.tv_sec - Tproc[i].start_time.tv_sec >= 10) {
                if (x == -1 || Tproc[i].start_time.tv_sec < Tproc[x].start_time.tv_sec) 
                    x = i;
            }
        }
        i++;
    }
    if (x != -1)
        p = x;

    return p;
}


int main (int argc, char *argv[]) {
  int i;
  int *j;  

  // Cr�er les processus long
  for  (i = 0; i < 2; i++) {
    j = (int *) malloc(sizeof(int));
    *j= i;
    CreateProc((function_t)ProcLong,(void *)j, 80);
  }



  // Definir une nouvelle primitive d'election avec un quantum de 1 seconde
  // SchedParam(NEW, 1, ApproxSJF);
  SchedParam(NEW, 0, SJFElect);
  // Lancer l'ordonnanceur en mode non "verbeux"
  sched(0);     

  // Imprimer les statistiques
  PrintStat();

  return EXIT_SUCCESS;

}
