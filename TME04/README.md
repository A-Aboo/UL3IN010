# TME 4 - Gestion de Processus

Ce TME contient :

- Un `multi-grep` qui crée un processus fils par fichier avec `fork()`.
- L'exécution de `grep` avec `execl()`.
- Une limitation du nombre de processus fils avec `MAXFILS`.
- L'utilisation de `wait()` pour attendre les fils.
- L'affichage des temps CPU utilisateur et système avec `wait3()`.
- La création de deux processus zombies pendant 10 secondes.

## Compilation

```bash
make
```