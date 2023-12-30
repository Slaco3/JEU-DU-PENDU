typedef struct Joueur Joueur;
struct Joueur {
	char nom[100];
	int score;
};

int comparer(const void* a_void, const void* b_void);
void recuperer_nom_score_joueur_txt(Joueur* joueurs);
int recuperer_nombre_lignes_fichier_txt(char nom_fichier[]);
void afficher_classement(Joueur joueurs[], int nbre_joueurs);
