# TME 3 - Ordonnancement

Ce TME utilise la bibliothèque `libsched` pour tester plusieurs algorithmes d'ordonnancement.

## 1. Test de la bibliothèque

On peut modifier le quantum et tester l'élection aléatoire avec :

```c
SchedParam(NEW, 1, RandomElect);
```

## 2. SJF - Shortest Job First

La fonction `SJFElect()` choisit parmi les processus prêts celui qui a la plus petite durée estimée :

```c
Tproc[i].duration
```

SJF est utilisé ici sans temps partagé :

```c
SchedParam(NEW, 0, SJFElect);
```

## 3. Approximation de SJF

Comme la durée réelle d'une tâche n'est généralement pas connue, `ApproxSJF()` utilise :

```c
Tproc[i].ncpu
```

`ncpu` représente le temps CPU déjà consommé.

Le processus ayant consommé le moins de CPU est choisi.

Test avec un quantum de 1 seconde :

```c
SchedParam(NEW, 1, ApproxSJF);
```

### Comparaison avec Random

`RandomElect()` choisit un processus aléatoirement.

`ApproxSJF()` favorise les tâches qui ont consommé peu de CPU, donc généralement les tâches courtes.

### Famine

Oui, `ApproxSJF()` peut provoquer une famine si de nouvelles tâches courtes arrivent continuellement.

Pour éviter cela, on peut utiliser un mécanisme de vieillissement (`aging`) et donner la priorité à une tâche qui attend depuis longtemps.