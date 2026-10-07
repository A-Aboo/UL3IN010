# TME 2 - Gestion du temps

Ce TME contient :

- Un programme `mytimes` qui exécute des commandes avec `system()`.
- Le calcul du temps total avec `gettimeofday()`.
- Le calcul des temps CPU avec `times()` :
  - temps utilisateur
  - temps système
  - temps utilisateur des fils
  - temps système des fils
- Les programmes `loopcpu` et `loopsys`.
- Des tests de priorité avec `nice`.

## Réponses aux questions

### 1.1 `time sleep 5`

`sleep` dure environ 5 secondes, mais consomme presque aucun temps CPU car le processus est en attente.

### 1.2 `loopcpu`

Le temps utilisateur (`user`) est élevé car le programme effectue beaucoup de calculs en mode utilisateur.

### 1.3 `loopsys`

Le temps système (`sys`) est élevé car `getpid()` est un appel système exécuté plusieurs fois.

### 3.2 `sleep 5` et `sleep 10`

Le temps total mesuré est environ 5 secondes puis 10 secondes.

### 4.2 Statistiques

- `sleep` : presque aucun temps CPU.
- `loopcpu` : principalement du temps utilisateur.
- `loopsys` : davantage de temps système.

### 5.1 `ps -l`

Avec une priorité normale, `NI` vaut généralement `0` (et `PRI` est souvent autour de `80` sous Linux).

### 5.2 `nice -19 ps -l`

La valeur `NI` devient `19` : le processus a une priorité plus faible.

### 5.3 9 `loopcpu` sur 8 cœurs

Il y a plus de processus que de cœurs disponibles. Ils doivent donc partager le processeur.

Le processus lancé avec une priorité plus faible reçoit moins de CPU et termine généralement plus tard que les autres.

## Compilation

```bash
make
```