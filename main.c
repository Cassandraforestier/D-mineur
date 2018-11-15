#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "names.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    //To reset the random values
    srand (time(NULL));

    //Declarations
    char pseudo[20];

    //TITRE
    couleurs(11,0);
    printf("\t\t-------------------\n");
    printf("\t\t|    DEMINEUR     |\n");
    printf("\t\t-------------------\n");
    couleurs(15,0);

    //Definition
    couleurs(3,0);
    printf("\n\nComment jouer au Demineur ?\n\n");
    couleurs(5,0);
    printf("Vous devez deminer ce champ de mines!\n");
    couleurs(3,0);
    printf("Au debut, les mines, enterrees, ne sont bien evidement pas visibles.\n");
    couleurs(5,0);
    printf("Pour gagner, il faut determiner l'emplacement de toutes les mines avec les drapeaux X.\n");
    couleurs(3,0);
    printf("Si jamais vous cliquez sur une case contenant une mine, celle-ci explose  et vous perdez.\n");
    couleurs(5,0);
    printf("Si la case selectionnee est vide, toutes les cases vides adjacentes s'ouvriront recursivement.\n\n");
    couleurs(12,0);
    printf("ATTENTION : ");
    couleurs(3,0);
    printf("Pour gagner, il ne doit pas y avoir de mines incorrectement marquees avec un drapeau.\n\n");

    //Entrer du pseudonyme du joueur
    couleurs(15,0);
    printf("\nVeuillez entrer votre pseudonyme : ");
    couleurs(5,0);
    scanf("%s",&pseudo);
    couleurs(15,0);
    printf("\n");
    system("cls");
    //Lancement du jeu grace a la procedure ci-dessous
    initialiserDemineur(pseudo);
}
