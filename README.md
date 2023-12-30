Jeu du Pendu en C

Le classique jeu de Pendu recréé en langauge C. 
Devinez le mot caché en proposant des lettres. Attention vous n'avez que 8 tentatives !

Le programme sélectionne le mot à deviner de manière aléatoire dans le fichier "words.txt" lors de chaque début de partie.

Cette version propose un système de rejouabilité et de classement : ce classement est basé sur le nombre de tentatives d'un joueur pour trouver le mot caché.
 
Au début de chaque partie le jeu affiche un classement des meilleurs joueurs. Lors de chaque fin de partie, si le joueur a réussi à trouver le mot, son nom et son score sont enregistré dans le fichier "joueur.txt".
Ainsi, si le joueur est dans le top 10 des meilleurs joueur, il apparaitra dans le classment lors de la prochaine partie.


Instructions : 
1. Clonez le référenciel
2. Compilez le programme grâce à un compilateur C tel que GCC
    - exemple pour windows : gcc -o pendu.exe main.c classement.c
    - exemple pour linux :  gcc -o pendu main.c classement.c
3. Exécutez le jeu et commencez à deviner les mots

Bonne partie ! 
