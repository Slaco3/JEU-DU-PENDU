#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classement.h"

#define TAILLE_MAX_CHAINE_NOM_ET_SCORE 50


int recuperer_nombre_lignes_fichier_txt(char nom_fichier[]) {
	char ligne[100];   
	int compteur = 0;
	
	FILE* fichier = NULL;
	
	fichier = fopen(nom_fichier, "r");
	
	if (fichier == NULL) {
        printf("Désolé il y eu un problème lors de l'ouverture d'un fichier texte.\n");
        exit(1);
    }
	
	while(fgets(ligne, sizeof(ligne), fichier) != NULL) {
		compteur ++;                                              // on  utilise un compteur qu'on va incrémenter tant que fgets a quelque chose à lire
	}
	
	fclose(fichier);
	
	return compteur;
}


void recuperer_nom_score_joueur_txt(Joueur* joueurs){       // fonction qui récupère un tableau de structures Joueur depuis le fichier joueur.txt
	char nom_et_score[TAILLE_MAX_CHAINE_NOM_ET_SCORE] = {0};    // Cette variable correpsond à une ligne de mon fichier txt, qui va prendre tour à tour les différentes valeures
	FILE* fichier = NULL;
	int indice_joueur = 0;
	
	fichier = fopen("joueur.txt", "r");
	
	if (fichier == NULL) {
        printf("Désolé il y eu un problème lors de l'ouverture du fichier permettant de stocker le nom et le score du joueur.\n");
        exit(1);
    }
    
	while(fgets(nom_et_score, sizeof(nom_et_score), fichier) != NULL){     // on récupère le contenu d'une ligne tant qu'il y une ligne à récupérer, et on stocke son contenu dans nom_et_score
        int longueur_mot = strlen(nom_et_score);
		int indice_derniere_lettre = longueur_mot - 1;
		if (nom_et_score[indice_derniere_lettre] =='\n') {       // ici on retire le le caratère '\n' de retour à la ligne comme vu précédemment 
		    nom_et_score[indice_derniere_lettre] = '\0';	
    	}
    	
    	char* nom_joueur = strtok(nom_et_score, ",");     // avec strtok on 'parse' notre ligne pour récupérer le nom (->ce qui se situe avant la virgule)
    	strcpy(joueurs[indice_joueur].nom, nom_joueur);      // on copie ce nom dans la variable nom de notre strucutre Joueur
    	char* score_str = strtok(NULL, ",");             // cette fois on récupère ce qui est après la virgule  -> le score
    	joueurs[indice_joueur].score = atoi(score_str);      // la fonction atoi convertie la chaine de caractère contenant le score en int, et on stocke ce nombre dans la varaible score de la structure Joueur
    	 
		indice_joueur ++;	                     // on incrémente ce nombre pour remplir les variables nom et score du prochain joueur dans le tableau, au tour de boucle suivant
    }
	fclose(fichier);
}


int comparer(const void* a_void, const void* b_void){    // fonction de comparaison que l'on utilise avec qsort
	Joueur a = *(Joueur*) a_void;
	Joueur b = *(Joueur*) b_void;
	
	return a.score - b.score;     // permet de classer deux structures Personne en fonction de leur attribut score
}


void afficher_classement(Joueur joueurs[], int nbre_joueurs) {   // affiche le top 10 des joueurs
	int nbre_lignes = 10;               
	printf("\nCLASSEMENT : \n\n");
	
	if (nbre_joueurs < 10) {                  // si j'ai moins de 10 joueurs je n'afffiche que ceux là.
		nbre_lignes = nbre_joueurs;
	}
	
	for (int i=0; i<nbre_lignes; i++) {
		printf("%d . %s  (%d tentatives)\n", i+1, joueurs[i].nom, joueurs[i].score);
	}
	printf("\n");
}


