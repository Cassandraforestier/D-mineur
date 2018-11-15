// notre structure reunit les lignes et les colonnes en type int
typedef struct dimensions {
    int lignes;
    int colonnes;
    } Dimensions;
// liste de toutes les fonctions et procedures se trouvant dans le fichier fonctions.c
void initialiserDemineur(char *pseudo[20]);
void afficher (Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int *monTableau2[dimensions.lignes][dimensions.colonnes], char *pseudo[20], int *minesRestantes, int casesRestantes);
int calculScore(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes]);
int calculCasesRestantes(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes]);
void jouerPartie(int *monTableauDeMines, int *monTableauAffichage, Dimensions dimensions, char *nomJoueur[20], int *minesRestantes);
void finJeu(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], char *pseudo[20]);
void ciblerCellule(Dimensions dimensions, int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int colonne, int ligne, int *minesRestantes);
void decouvrirCellule(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int colonne, int ligne, char *pseudo[20], int *nombreMines);
void showResult(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes]);
void discoverVoidCells(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int ligne, int colonne);
void initialiserDemineur(char *pseudo[20]);
int nombreMines (int mode);
void valoriserTableauAvecMines(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes]);
void incrementCellulesAdjacentes(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int ligne, int colonne);
void deposer_mines(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int maxMines);
int selectMode();
void initTableau(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int nombreMines);
