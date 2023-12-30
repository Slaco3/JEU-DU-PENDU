#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "classement.h"


/* Constantes de prérpocesseur  */

#define TAILLE_MAX_MOT_A_DEVINER 50          
#define TENTATIVES_MAX 8
#define LONGUEUR_MAX_NOM 50


/* Prototypes de mes fonctions  */

void afficher_titre();
void afficher_regles();
void demander_nom_joueur(char nom[]);
int nom_est_valide(char nom[]);
void recuperer_mot_aleatoire_fichier_txt(char mot_a_deviner[]);
void generer_mot_underscores(char mot_a_deviner[], char mot_underscores[]);
void afficher_separateur();
void afficher_demi_separateur();
void afficher_numero_tentative(int numero_tentative);
void afficher_dessin_pendu(int nbre_tentatives);
void afficher_mot_underscore(char* mot_underscore);
void afficher_lettres_deja_essayees(char lettres_deja_essayees[]);
char demander_lettre_utilisateur();
int lettre_est_valide(char lettre);
int lettre_est_dans_chaine(char lettre, char chaine[]);
void remplacer_underscore_par_lettre_dans_mot(char lettre, char mot_a_trouver[], char mot_underscore[]);
void ajouter_lettre_dans_chaine(char lettre, char chaine[]);
void stocker_nom_et_score(char nom[], int score);
int demander_continuer_a_jouer();


int main(){
    char nom_joueur[LONGUEUR_MAX_NOM];
    int continuer = 1;
    int nb_parties = 0;
    
    afficher_titre();
    afficher_regles();
    
	while(continuer) {      
		char mot_a_deviner[TAILLE_MAX_MOT_A_DEVINER] = {0};      // on initisalise nos variables
		char mot_underscores[TAILLE_MAX_MOT_A_DEVINER] = {0};      // mot undescore c'est le mot de la meme taille que le mot à devnier, qui n'est composé que d'undescores au debut de la partie et dont les lettres vont être révélées au fur et à mesure.
		int numero_tentative = 1;
		char lettres_deja_essayees[50] = {0};
		char lettre_utilisateur;
		
		recuperer_mot_aleatoire_fichier_txt(mot_a_deviner);         // ici on récupère un mot aléatoirement dans le fichier words.txt
   		generer_mot_underscores(mot_a_deviner, mot_underscores);      // on génére notre mot_underscores en conséquence
    
		nb_parties ++;
		afficher_separateur();
		printf("\n                         PARTIE %d  \n", nb_parties);
		afficher_separateur();
																					// Les prochaines lignes permettent récupérer les noms des joueurs et leur classemnt dans joueur.txt pour afficher un top 10
		int nbre_joueurs = recuperer_nombre_lignes_fichier_txt("joueur.txt");       // on récupère le nombre de lignes dans joueur.txt
		Joueur* joueurs = malloc(sizeof(Joueur) * nbre_joueurs);                 // on alloue de la mémoire pour notre liste de joueurs
		recuperer_nom_score_joueur_txt(joueurs);                       // ici on récupère une liste de structures de joueurs
		qsort(joueurs, nbre_joueurs, sizeof(Joueur), comparer);        // ensuite on trie cette liste  -   qsort(tableauATrier, longueurTableau, tailleOctetElement, fonctionDeCOmparaison
		afficher_classement(joueurs, nbre_joueurs);                    // et on affiche notre liste triée
		free(joueurs);
		afficher_separateur();
		demander_nom_joueur(nom_joueur);
		
		while(1) {
			afficher_numero_tentative(numero_tentative);
		    afficher_dessin_pendu(numero_tentative);
		    afficher_mot_underscore(mot_underscores);

		    if(strlen(lettres_deja_essayees) > 0) {           // on n'affiche la liste des lettres déjà essayées que si il y en a.
				afficher_lettres_deja_essayees(lettres_deja_essayees);
			}

			lettre_utilisateur = tolower(demander_lettre_utilisateur());      // on récupère la lettre rentrée par l'utilisateur et on la convertit en minuscule.

			if (lettre_est_dans_chaine(lettre_utilisateur, lettres_deja_essayees)) {      // Si la lettre est dans la liste des lettres déjà essayées inutile d'aller plus loin, on reboucle,
		        printf("Vous avez déjà essayé cette lettre.\n");                        //   sans incrémenter le compteur de tentatives.
		        afficher_demi_separateur();
		        continue;
			}

			if (lettre_est_dans_chaine(lettre_utilisateur, mot_a_deviner)) {             // On teste si la lettre est dans le mot à deviner.
		        printf("La lettre '%c' est bien dans le mot.\n", lettre_utilisateur);
		        remplacer_underscore_par_lettre_dans_mot(lettre_utilisateur, mot_a_deviner, mot_underscores);   // Si oui on remplace les underscores par la lettre en question dans le mot_underscores.
			}
			else {
		        printf("La lettre '%c' n'est pas dans le mot.\n", lettre_utilisateur);
		        numero_tentative ++;                                                              // Sinon on incrémente le compteur de tentatives.
			}

			ajouter_lettre_dans_chaine(lettre_utilisateur, lettres_deja_essayees);             // Que la lettre proposée par l'utilisateur soit ou non dans le mot à deviner on l'ajoute à la liste des lettres essayées.

		    afficher_demi_separateur();

			if (strcmp(mot_a_deviner, mot_underscores) == 0){                  //  A chaque fin de boucle on vérifie si le mot à deviner est le même que le mot underscore.
		        printf("\nBravo %s, vous avez gagné en %d tentatives! \n", nom_joueur, numero_tentative);  // si oui c'est que tous les underscores ont été remplacés et on affiche la victoire.
		        stocker_nom_et_score(nom_joueur, numero_tentative);
		        break;
			}

			if (numero_tentative > TENTATIVES_MAX) {                     // Si l'utilisateur n'a pas gagné on teste son nombre nombres de tentatives.
		        afficher_dessin_pendu(numero_tentative);
		        printf("\n%s, vous avez dépassé le nombre maximal de tentatives : vous avez perdu ! \n", nom_joueur); // si le nombre de tentatives est supérieur à 8 c'est qu'il a perdu.
		        break;
			}
		}
		printf("Le mot à trouver était : %s\n\n", mot_a_deviner);
		
		continuer = demander_continuer_a_jouer();
    }
    return 0;
}


void afficher_titre() {
    printf("\n\n");
	printf("**************************************************************\n\n");
	printf("           PPPPP   EEEEE   N   N   DDDD    U   U\n");
    printf("           P   P   E       NN  N   D   D   U   U\n");
    printf("           PPPPP   EEEE    N N N   D   D   U   U\n");
    printf("           P       E       N  NN   D   D   U   U\n");
    printf("           P       EEEEE   N   N   DDDD     UUU\n\n");
    printf("**************************************************************\n\n\n");
}


void afficher_regles() {
    printf("REGLES DU JEU : \n\n");
	printf("Vous avez 8 tentatives pour trouver un mot. \nA chaque tentative vous proposez une lettre.\n");
	printf("Si la lettre est présente dans le mot on ne \ntouche pas à votre nombre de tentatives.\n");
	printf("Si la lettre n'est pas présente dans le mot \non passe à la tentative suivante.\n");
	printf("Si vous proposez une lettre déjà tentée précédemment,\ncela n’augmente pas votre nombre de tentatives.\n\n");
}


void demander_nom_joueur(char nom[]){
	printf("\n");
	do {
		printf("Rentrez votre nom : ");
		scanf("%s", nom);
		if (!nom_est_valide(nom)) {
			printf("Votre nom ne peut contenir que des lettres.\n");
		}
	}
	while(strlen(nom)>LONGUEUR_MAX_NOM-1 || !nom_est_valide(nom));
    printf("\n");
}


int nom_est_valide(char nom[]){    // retourne un booleen
	for (int i=0; i<strlen(nom); i++){
		if(!isalpha(nom[i]))
			return 0;
		}
	return 1;
	}


void recuperer_mot_aleatoire_fichier_txt(char mot_a_deviner[]) {
    int nombre_lignes_fichier_txt = 835;
    int nombre_aleatoire = 0;

    srand(time(NULL));                                            // ici j'initialise la graine de la fonction rand grace à srand
    nombre_aleatoire = (rand() % nombre_lignes_fichier_txt) + 1;      // je récupère un nombre aléatoire entre 1 et le nombre de lignes dans le fichier

    FILE* fichier = NULL;
    fichier = fopen("words.txt", "r");

    if (fichier == NULL) {
        printf("Désolé il y eu un problème lors de l'ouverture du fichier permettant de récupérer un mot alétoire.\n");
        exit(1);
    }

    for (int i = 0; i<nombre_aleatoire; i++){                       // on boucle jusqu'à la ligne qui correspond à notre nombre aléatoire
        fgets(mot_a_deviner, TAILLE_MAX_MOT_A_DEVINER, fichier);      // à la dernière itération de ma boucle je récupère le mot à deviner dans ma variable mot_a_deviner grace à fgets
    }

    int longueur_mot = strlen(mot_a_deviner);               // les 4 lignes qui suivent permettent de retirer le caratère '\n'qui correpsond au retour à la ligne (on le rempalce par '\0' pour marquer la fin de ma chaine de caratère)
    int indice_derniere_lettre = longueur_mot - 1;

    if (mot_a_deviner[indice_derniere_lettre] =='\n') {
        mot_a_deviner[indice_derniere_lettre] = '\0';
    }
    fclose(fichier);
}


void generer_mot_underscores(char mot_a_deviner[], char mot_underscores[]) {
    int longueur_mot = strlen(mot_a_deviner);
for (int i=0; i<longueur_mot; i++){                         // on boucle sur la longeur de mon mot_à_deviner
        mot_underscores[i] = '_';                         // pour chaque lettre de mot_a_devniner au ajoute un underscore dans mot_underscore
    }
}


void afficher_separateur() {
    printf("\n**************************************************************\n");
}


void afficher_demi_separateur() {
    printf("\n--------------------------------------------------------------\n");
}


void afficher_numero_tentative(int numero_tentative){
	printf("\nTENTATIVE %d :\n", numero_tentative);
}

void afficher_mot_underscore(char* mot_underscore) {
	printf("Mot à trouver : ");

	for (int i=0; i<(strlen(mot_underscore)); i++) {
		printf("%c ", mot_underscore[i]);            // particularité : on ajoute un espace après chaque caractère pour qu'on identifie bien le nombre de caractères
	}
	printf("\n\n");
}


void afficher_lettres_deja_essayees(char lettres_deja_essayees[]) {
    printf("Lettre déjà essayées : ");
    for (int i=0; i<strlen(lettres_deja_essayees); i++) {        // on boucle sur ma chaine de caratère : lettre_deja_essayees
        int position_lettre = i+1;
		if (position_lettre == strlen(lettres_deja_essayees)){   // quand on arrive a la derniere lettre : 
			printf("%c.", lettres_deja_essayees[i]);               // on ajoute un point final
        }
		else{
            printf("%c, ", lettres_deja_essayees[i]);           // pour tout autre lettre on ajoute une virgule
		}
		}
    printf("\n");
}


char demander_lettre_utilisateur(){
    char lettre_chaine[20] = {0};         // je passe par une chaine de caratère et non par un caractère pour pouvoir utiliser strlen dessus et ainsi vérifier que l'utilisateur ne rentre q'une et une seule lettre

    while(!(lettre_est_valide(lettre_chaine[0])) || strlen(lettre_chaine) != 1){     // on redemande une saisie tant que le premier caractère de la saisie n'est pas valide et que l'utilisteur rentre un nnbre de lettres  != 1
		printf("Rentrez une (et une seule) lettre : ");
		scanf("%s", lettre_chaine);
    }
    return lettre_chaine[0];    // on retourne la première lettre de la chaine
}


int lettre_est_valide(char lettre) {
    if ((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z')){
        return 1;
    }
    return 0;
}


int lettre_est_dans_chaine(char lettre, char chaine[]) {     // retourne un boléen
    for (int i=0; i<strlen(chaine); i++) {
        if (chaine[i] == lettre) {
            return 1;
        }
    }
    return 0;
}


void remplacer_underscore_par_lettre_dans_mot(char lettre, char mot_a_trouver[], char mot_underscore[]) {
    for (int i=0; i<strlen(mot_a_trouver); i++) {
        if (mot_a_trouver[i] == lettre) {
            mot_underscore[i] = lettre;
        }
    }
}


void ajouter_lettre_dans_chaine(char lettre, char chaine[]) {   // on l'utilise pour ajouter une lettre dans la chaine lettres_deja_essayees
    chaine[strlen(chaine)] = lettre;                          // ici on ajoute simplement un caractère -> pour trouver l'indice auquel rejouter notre lettre on utilise strlen
}


int demander_continuer_a_jouer() {                     // fonction qui renvoie un bolléen
	char reponse_utilisateur_chaine[20] = {0};
	
	while (strlen(reponse_utilisateur_chaine) != 1 || (reponse_utilisateur_chaine[0] != 'y' && reponse_utilisateur_chaine[0] != 'n')){     // on s'assure que l'utilisateur rentre 'y' ou 'n'
		printf("Voulez vous rejouer ? (y/n) : ");
		scanf(" %s", reponse_utilisateur_chaine);
	}
	
	printf("\n\n\n");
	if (reponse_utilisateur_chaine[0] == 'y') {   // si il rentre 'y' la fonction renvoie true(1)
		return 1;
	}
	return 0;	               // sinon la fonction renvoie false(0)
}


void stocker_nom_et_score(char nom[], int score){  // permet de stocker le nom et le score du joueur dans joueur.txt
	FILE* fichier = NULL;
	
	fichier = fopen("joueur.txt", "a");
	
	if (fichier == NULL) {
        printf("Désolé il y eu un problème lors de l'ouverture du fichier permettant de stocker le nom et le score du joueur.\n");
        exit(1);
    }
    
	fprintf(fichier, "%s, %d\n", nom, score);   // on ajoute le nom et le score du joueur à la suite notre fichier "joueur.txt" de manière formatée --> <nom>, <score>  : cela me permet d'avoir mes données stockées toujorus de la même manière
	fclose(fichier);
}

void afficher_dessin_pendu(int tentative) {
	printf("\n");
	if (tentative > 8) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |       /|\\ \n");
    printf("        |        |\n");
    printf("        |       / \\ \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");

    }
	if (tentative == 8) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |       /|\\ \n");
    printf("        |        |\n");
    printf("        |         \\ \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");

    }

    else if (tentative == 7) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |       /|\\ \n");
    printf("        |        |\n");
    printf("        |        \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }

    else if (tentative == 6) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |        |\\ \n");
    printf("        |        |\n");
    printf("        |        \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }

    else if (tentative == 5) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |        | \n");
    printf("        |        |\n");
    printf("        |        \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }
    else if (tentative == 4) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |        |  \n");
    printf("        |         \n");
    printf("        |          \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }
    else if (tentative == 3) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        o\n");
    printf("        |         \n");
    printf("        |        \n");
    printf("        |          \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }
    else if (tentative == 2) {
    printf("         ________\n");
    printf("        |        |\n");
    printf("        |        \n");
    printf("        |         \n");
    printf("        |        \n");
    printf("        |         \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }
    else if (tentative == 1) {
  	printf("         ________\n");
    printf("        |        \n");
    printf("        |        \n");
    printf("        |         \n");
    printf("        |        \n");
    printf("        |        \n");
    printf("       _|_\n");
    printf("      |   |____________\n");
    printf("      |                |\n");
    printf("      |________________|\n");
    }
    printf("\n\n");
}
