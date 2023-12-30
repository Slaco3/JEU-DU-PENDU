Jeu du Pendu en C

Le classique jeu du Pendu recréé en langage C. Devinez le mot caché en proposant des lettres. Attention, vous n'avez que 8 tentatives !

Le programme sélectionne le mot à deviner de manière aléatoire dans le fichier "words.txt" à chaque début de partie.

Cette version propose un système de rejouabilité et de classement : le classement est basé sur le nombre de tentatives d'un joueur pour trouver le mot caché.

Au début de chaque partie, le jeu affiche un classement des meilleurs joueurs. À la fin de chaque partie, si le joueur a réussi à trouver le mot, son nom et son score sont enregistrés dans le fichier "joueur.txt". Ainsi, si le joueur est dans le top 10 des meilleurs joueurs, il apparaîtra dans le classement lors de la prochaine partie.

Instructions :
1. Clonez le référentiel.
2. Compilez le programme grâce à un compilateur C tel que GCC.
   - Exemple pour Windows : gcc -o pendu.exe main.c classement.c
   - Exemple pour Linux : gcc -o pendu main.c classement.c
3. Exécutez le jeu et commencez à deviner les mots.

Bonne partie !
