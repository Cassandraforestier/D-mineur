    #include "names.h"
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>

    //Fonction affichage:
    void afficher (Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int *monTableau2[dimensions.lignes][dimensions.colonnes], char *pseudo[20], int *minesRestantes, int casesRestantes)
    {
        system("cls"); // permet de "raffraichir" l'affichage (supprime ce qui a été fait avant)
        int i,j, cpt=0;
        char caract = 'A';
            printf("\tPseudo : ");
            couleurs(5,0);
            printf("%s\t", pseudo);
            couleurs(15,0);
            printf("\tMines restantes : ");
            couleurs(12,0);
            printf("%i\n\n", *minesRestantes);
            couleurs(15,0);
            printf("\t\tCases restantes : ");
            couleurs(3,0);
            printf("%i\n\n", casesRestantes);
            couleurs(15,0);
            //Mise en place des lettres sur chaque colonnes en fonction de sa taille
            printf("\t\t");
        do{
            couleurs(6,0);
            printf("%c ", caract);
            couleurs(15,0);
            caract++;
            cpt++;
        }while(cpt<dimensions.colonnes);
            printf("\n\n");
        for (i=0;i<dimensions.lignes;i++)
        {
        //mise en place des numeros sur chaque lignes
        couleurs(6,0);
        printf("\t%d\t",i);
        couleurs(15,0);
            //tout l'affichage visuelle en fonction de ce que contient la case
            for (j=0;j<dimensions.colonnes;j++)
                {
                if(monTableau[i][j] == -1) // s'il y a une mine sur la case
                {
                    couleurs(8,0);
                    printf("* ");
                    couleurs(15,0);
                }

                else if(monTableau[i][j] == 0)
                {// Quand il n'y a aucune mine sur la case
                    couleurs(8,0);
                    printf("- ");
                    couleurs(15,0);
                }
                else if(monTableau[i][j] == -2)
                {
                    // Lier a l'option du drapeau.
                    couleurs(4,0);
                    printf("X ");
                    couleurs(15,0);
                }
                else
                    printf("%d ", monTableau[i][j]);
                }
                printf("\n");
        }

        // Pour le mode test : permet de voir en plus le visuel des cases ( 0 = pas de mine; 1-2-3... = 1 ou plus ; -1 = il y a une mine).
        if(dimensions.colonnes ==5){
            printf("\n");
            caract = 'A';
            cpt=0;
            printf("\t");
            do{
                printf("%c ", caract);
                caract++;
                cpt++;
            }while(cpt<dimensions.colonnes);
                printf("\n\n");
        for (i=0;i<dimensions.lignes;i++)
        { //Mise en place des numeros sur chaque lignes
            printf("%d\t",i);

            for (j=0;j<dimensions.colonnes;j++){
                printf("%d ", monTableau2[i][j]);
            }
            printf("\n\n");
        }
        }
    }

    void couleurs (int couleurTexte, int couleurFond) // Procedure permettant d'ajouter des couleurs lors du lancement du demineur.
    {
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurFond*16+couleurTexte);
    }

    int calculScore(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes])
    {
    //Parcourir le tableau et en fonction de ce que le joueur trouve avec l'option drapeau, incrementer la variable score.
    int i,j, score = 0;
        for (i=0;i<dimensions.lignes;i++)
        {
            for (j=0;j<dimensions.colonnes;j++)
            {
                if(monTableauAffichage[i][j] == -2 && monTableauDeMines[i][j] == -1)
                    score++;

            }
        }
    return score;
    }

    int calculCasesRestantes(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes])
    {
    // Parcourir le tableau et en fonction de ce que le joueur a decouvert, incrementer la variable count pour connaitre le nombre de cases restantes.
        int i,j, count = 0;
            for (i=0;i<dimensions.lignes;i++)
            {
                for (j=0;j<dimensions.colonnes;j++)
                {
                    if((monTableauAffichage[i][j] == -1 || monTableauAffichage[i][j] == -2) && monTableauDeMines[i][j] != -1)
                        count++;
                }
            }
    return count;
    }

    void jouerPartie(int *monTableauDeMines, int *monTableauAffichage, Dimensions dimensions, char *nomJoueur[20], int *minesRestantes)
    {
    //Lancer la fonction casesRestantes et les procedures affichees.
    char colonne;
    int ligne, mode;
        int casesRestantes = calculCasesRestantes(dimensions, monTableauDeMines, monTableauAffichage);
        afficher(dimensions, monTableauAffichage, monTableauDeMines, nomJoueur, minesRestantes, casesRestantes);
    //En fonction de la fonction caseRestantes (si 0 case) alors lancer la procedure finJeu
            if(casesRestantes == 0)
            {
            finJeu(dimensions, monTableauDeMines, monTableauAffichage, nomJoueur);
            return;
            }
    //Menu pour cibler ou decouvrir une case
    couleurs(5,0);
    printf("\n\tSouhaitez-vous :\n\n");
    couleurs(3,0);
    printf("\tDeposer un drapeau :");
    couleurs(9,0);
    printf(" 1\n");
    couleurs(3,0);
    printf("\tDecouvrir une cellule :");
    couleurs(9,0);
    printf(" 2\n");
    printf("\t\t");
    scanf("%i", &mode);
    couleurs(15,0);
        while(mode != 1 && mode != 2) {
            couleurs(4,0);
            printf("Mauvaise touche veuillez reessayer : ");
            scanf("%i", &mode);
        }
    // pour indiquer une cellule, on se doit d'indiquer la colonne puis la ligne
    couleurs(3,0);
    printf("Indiquez une colonne : ");
    couleurs(9,0);
    scanf("%s",&colonne);
    couleurs(3,0);
    printf("Indiquez une ligne : ");
    couleurs(9,0);
    scanf("%d",&ligne);
    couleurs(15,0);
    //comparer la valeur char ( A ) et la valeur scannée. Exemple pour B: A = 65; B = 66;
    //Donc le resultat va etre : 66-65 = 1 -> Ce qui correspond a la seconde colonne (le debut commencant a 0)
    char c = 'A';
    int intColonne = colonne - c;

    //Pour s'assurer que les dimensions sont inclues dans le tableau.
        if(ligne < 0 || ligne >= dimensions.lignes || intColonne >= dimensions.colonnes || intColonne < 0)
        {
            couleurs(4,0);
            printf("/!\\ Cellule introuvable veuillez saisir d'autres coordonnees /!\\ \n");
            jouerPartie(monTableauDeMines, monTableauAffichage, dimensions, nomJoueur, minesRestantes);
            return;
        }

        if(mode == 1)
        {
        ciblerCellule(dimensions, monTableauAffichage, intColonne, ligne, minesRestantes);
        jouerPartie(monTableauDeMines, monTableauAffichage, dimensions, nomJoueur, minesRestantes);
        }
        else if (mode == 2)
        {
        decouvrirCellule(dimensions, monTableauDeMines, monTableauAffichage, intColonne, ligne, nomJoueur, minesRestantes);
        }
    }

    void finJeu(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], char *pseudo[20])
    {
        int mode, score;
        // on recupere localement la fonction calculScore pour pouvoir l'utiliser dans le fichier.
        score = calculScore(dimensions, monTableauDeMines, monTableauAffichage);
        //Recuperation des scores dans un fichier.
        FILE* monFichier;
        monFichier=fopen("lesScores.txt", "a");
            printf("Pseudo : %s", score);
            printf("Nombres de mines decouvertes : %d \n", score);
            fseek(monFichier, 0, SEEK_END);
            fprintf(monFichier, "Nombre de mines decouvertes : %d \n", pseudo, score);
        fclose(monFichier);
        //Pour relancer le jeu depuis le menu des differents modes.
        couleurs(3,0);
        printf("Souhaitez vous rejouer ?\n");
        printf("Oui : 1\n");
        couleurs(4,0);
        printf("Non : 2\n");
        couleurs(15,0);
        scanf("%i", &mode);
            while(mode != 1 && mode != 2)
            {
                couleurs(4,0);
                printf("Mauvaise touche veuillez reessayer :");
                couleurs(15,0);
                scanf("%i", &mode);
            }

            if(mode == 1)
                initialiserDemineur(pseudo);
    }

    // ciblerCellule permet de mieux gerer les minesRestantes
    void ciblerCellule(Dimensions dimensions, int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int colonne, int ligne, int *minesRestantes)
    {
        if(monTableauAffichage[ligne][colonne] == -2) {
            monTableauAffichage[ligne][colonne] = -1;
            *minesRestantes = *minesRestantes + 1;
        }else if (monTableauAffichage[ligne][colonne] == -1) {
            monTableauAffichage[ligne][colonne] = -2;
            *minesRestantes = *minesRestantes - 1;
        }
    }

    void decouvrirCellule(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int colonne, int ligne, char *pseudo[20], int *nombreMines)
    {
        printf("\n\n");
        //Obtenir la valeur de la cellule ciblee
        int valeur = monTableauDeMines[ligne][colonne];
        discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, ligne, colonne);
        //Verifier si c'est une autre bombe ou autre chose
            if(valeur == -1) {
                showResult(dimensions, monTableauDeMines, monTableauAffichage);
                couleurs(4,0);
                printf("\n\t/!\\ BOOOOM, Game over /!\\\n\n");
                couleurs(15,0);
                finJeu(dimensions, monTableauDeMines, monTableauAffichage, pseudo);
            } else
                jouerPartie(monTableauDeMines, monTableauAffichage, dimensions, pseudo, nombreMines);
    }

    void showResult(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes])
    {
        system("cls");
        int i,j, cpt=0;
        char caract = 'A';
        //Mise en place des lettres sur chaque colonnes en fonction de sa taille.
        printf("\t");
            do{
                printf("%c ", caract);
                caract++;
                cpt++;
            }while(cpt<dimensions.colonnes);
        printf("\n\n");
            for (i=0;i<dimensions.lignes;i++)
            {
            //mise en place des numeros sur chaque lignes.
                printf("%d\t",i);
                for (j=0;j<dimensions.colonnes;j++)
                {
                //Montrer les mines avec un X graphique, sinon montrer l'affichage classique.
                    if(monTableauDeMines[i][j] == -1)
                    {
                        couleurs(4,0);
                        printf("X ");
                        couleurs(15,0);
                    }
                    else if(monTableauAffichage[i][j] == -1)
                        printf("* ");
                    else if(monTableauAffichage[i][j] == 0)
                    {
                        couleurs(8,0);
                        printf("- ");
                        couleurs(15,0);
                    }
                    else
                        printf("%d ", monTableauAffichage[i][j]);
                }
        printf("\n");
            }
    }


    void discoverVoidCells(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int ligne, int colonne)
    {
        //s'assurer que la cellule n'est pas deja decouverte
            if(monTableauAffichage[ligne][colonne] != -1 && monTableauAffichage[ligne][colonne] != -2)
                return;
        // Permet d'aller voir ce qui se passe autour de la cellule
        int left = colonne -1;
        int right = colonne +1;
        int up = ligne -1;
        int down = ligne +1;
        int valeur = monTableauDeMines[ligne][colonne];
        monTableauAffichage[ligne][colonne] = valeur;

        //Ne pas decouvrir les cellules quand ce n'est pas une cellule vide
            if(valeur != 0)
                return;
            // verifie que la valeur est bien comprise dans le tableau
            if(left >= 0 && left < dimensions.colonnes) {
            if(up >= 0 && up < dimensions.lignes)
                    valeur = monTableauDeMines[up][left];
            if(valeur != -1) // si il y a une mine : lancer la procedure ci-dessous

                    discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, up, left);
            }
            if(down >= 0 && down < dimensions.lignes) {
                valeur = monTableauDeMines[down][left];
                if(valeur != -1)
                    discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, down, left);
            }
            valeur = monTableauDeMines[ligne][left];
            if(valeur != -1)
                discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, ligne, left);
            if(right >= 0 && right < dimensions.colonnes) {
                if(up >= 0 && up < dimensions.lignes) {
                    valeur = monTableauDeMines[up][right];
                    if(valeur != -1)
                            discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, up, right);
                }

            if(down >= 0 && down < dimensions.lignes) {
                valeur = monTableauDeMines[down][right];
                if(valeur != -1)
                    discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, down, right);
            }
            valeur = monTableauDeMines[ligne][right];
            if(valeur != -1)
                discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, ligne, right);
            }

            if(up >= 0 && up < dimensions.lignes) {
                valeur = monTableauDeMines[up][colonne];
                if(valeur != -1)
                    discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, up, colonne);
            }

            if(down >= 0 && down < dimensions.lignes) {
                valeur = monTableauDeMines[down][colonne];
                if(valeur != -1)
                    discoverVoidCells(dimensions, monTableauDeMines, monTableauAffichage, down, colonne);
            }
    }

    void initialiserDemineur(char *pseudo[20])
    {
        system("cls");
        int* monTableauDeMines;
        int* monTableauAffichage;
        int* mines;
        int mode = selectMode();
        Dimensions dimensions;
        //Determine le nombre de lignes et de colonnes (grace au typedef struct dimension)
        if (mode==1)
        {
            dimensions.lignes = 9;
            dimensions.colonnes = 9;
        }
        else if (mode==2)
        {
            dimensions.lignes = 16;
            dimensions.colonnes = 16;
        }
        else if (mode==3)
        {
            dimensions.lignes = 40;
            dimensions.colonnes = 16;
        }
        else if (mode==0) // Notre mode de test
        {
            dimensions.lignes = 5;
            dimensions.colonnes = 5;
        }
        else if (mode==4)
        { // mode 4 : joueur choisi son nombre de lignes/colonnes : mode personnalise; les valeurs recuperees dans la structure dimensions.
            couleurs(3,0);
            printf("Veuillez choisir le nombre de colonnes : ");
            scanf("%d", &dimensions.colonnes);
            printf("\nVeuillez choisir le nombre de lignes : ");
            scanf("%d", &dimensions.lignes);
        }
        else
        {
            couleurs(4,0);
            printf("Veuillez entrer une valeur indiquee : ");
            scanf("%d", &mode);
            couleurs(15,0);
        }
    //Allocation des tableaux dynamiques
    monTableauDeMines = malloc(dimensions.lignes * dimensions.colonnes * sizeof(int));
    monTableauAffichage = malloc(dimensions.lignes * dimensions.colonnes * sizeof(int));
    mines = malloc(sizeof(int));
    *mines = nombreMines(mode);
    initTableau(dimensions, monTableauDeMines, monTableauAffichage, *mines);
    jouerPartie(monTableauDeMines, monTableauAffichage, dimensions, pseudo, mines);
    }

    int nombreMines (int mode)
    { //Choix des mines en fonction du mode choisi.
        int Nb_mines;

        if (mode==1)
            Nb_mines=10;
        else if (mode==2)
            Nb_mines=40;
        else if (mode==3)
            Nb_mines=99;
        else if (mode==0)
            Nb_mines=1;
        else if (mode==4)
        { //le mode 4 est le mode personnalise, permet au joueur de choisir son nombre de mines, cela stocke de la meme maniere dans le variable Nb_mines.
            couleurs(5,0);
            printf("Veuillez choisir le nombre de mines : ");
            scanf("%d", &Nb_mines);
            couleurs(15,0);
        }
        else
        {
            couleurs(4,0);
            printf("Nous ne pouvons pas intialiser le jeu.");
            couleurs(15,0);
        }
    return Nb_mines;
    }
    // Si il y a une mine : on lance la procedure pour incrementer les cellules adjacentes
    void valoriserTableauAvecMines(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes])
    {
    int i, j;
        for(i = 0; i < dimensions.lignes; i++)
        {
            for(j = 0; j < dimensions.colonnes; j++)
            {
                if(monTableau[i][j] == -1)
                    incrementCellulesAdjacentes(dimensions, monTableau, i, j);
            }
        }
    }
    //Permet d'incrementer les cellules adjacentes en fonction d'une mine ou plusieurs ( regarde ce  qui se passe dans les huits cases autours)
    void incrementCellulesAdjacentes(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int ligne, int colonne)
    {
        int left = colonne -1;
        int right = colonne +1;
        int up = ligne -1;
        int down = ligne +1;
        int valeur;

        if(left >= 0 && left < dimensions.colonnes) {
        if(up >= 0 && up < dimensions.lignes) {
            valeur = monTableau[up][left];
                if(valeur > -1)
                    monTableau[up][left] = valeur + 1;
        }
        if(down >= 0 && down < dimensions.lignes) {
            valeur = monTableau[down][left];
                if(valeur > -1)
                    monTableau[down][left] = valeur + 1;
        }
        valeur = monTableau[ligne][left];
        if(valeur > -1)
            monTableau[ligne][left] = valeur + 1;
        }
        if(right >= 0 && right < dimensions.colonnes) {
        if(up >= 0 && up < dimensions.lignes) {
            valeur = monTableau[up][right];
                if(valeur > -1)
                    monTableau[up][right] = valeur + 1;
        }
        if(down >= 0 && down < dimensions.lignes) {
            valeur = monTableau[down][right];
                if(valeur > -1)
                    monTableau[down][right] = valeur + 1;
        }
        valeur = monTableau[ligne][right];
        if(valeur > -1)
            monTableau[ligne][right] = valeur + 1;
        }
        if(up >= 0 && up < dimensions.lignes) {
            valeur = monTableau[up][colonne];
                if(valeur > -1)
                    monTableau[up][colonne] = valeur + 1;
        }
        if(down >= 0 && down < dimensions.lignes) {
            valeur = monTableau[down][colonne];
                if(valeur > -1)
                    monTableau[down][colonne] = valeur + 1;
        }
    }

    void deposer_mines(Dimensions dimensions, int *monTableau[dimensions.lignes][dimensions.colonnes], int maxMines)//Cette fonction sert a generer les mines aleatoirement
    { //Cette fonction sert a generer les mines aleatoirement
        int compteurMines,ligne,colonne;
        compteurMines = 0;

        while(compteurMines < maxMines) {
            ligne=rand()%dimensions.lignes;//on choisit la ligne aleatoirement
            colonne=rand()%dimensions.colonnes;//on choisit la colonne aleatoirement

            if(monTableau[ligne][colonne] == 0) {
                monTableau[ligne][colonne] = -1;
                compteurMines ++;
            }
        }

    valoriserTableauAvecMines(dimensions, monTableau);
    }

    int selectMode()
    {
        int mode;
    // Selection du mode
        couleurs(15,0);
        printf("\nQuel mode voulez-vous jouer ? : \n\n");
        couleurs(3,0);
        couleurs(15,0);
        printf("--------------------------------------\n\n");
        couleurs(8,0);
        printf("MODE 1 : Mode facile - 9x9 cases avec 10 mines\n\n");
        couleurs(5,0);
        printf("MODE 2 : Mode intermediaire - 16x16 cases avec 40 mines\n\n");
        couleurs(4,0);
        printf("MODE 3 : Mode difficile - 16x40 cases avec 99 mines\n\n");
        couleurs(3,0);
        couleurs(15,0);
        printf("MODE 4 : Mode personnalise - Vous choisissez la taille de votre demineur\n\n");
        printf("--------------------------------------\n\n");
        couleurs(6,0);
        printf("MODE 0 : 5x5 cases avec 1 mine (Pour les tests)\n\n");
        couleurs(15,0);

        scanf("%d",&mode);

        while(mode != 0 && mode != 1 && mode != 2 && mode != 3 && mode !=4) {
            couleurs(4,0);
            printf("Mauvaise touche veuillez reessayer : ");
            couleurs(15,0);
            scanf("%d", &mode);
        }

    return mode;
    }

    //initialise la table de jeu et la table de mines
    void initTableau(Dimensions dimensions, int *monTableauDeMines[dimensions.lignes][dimensions.colonnes], int *monTableauAffichage[dimensions.lignes][dimensions.colonnes], int nombreMines)
    {
        int i, j, Compt;
            for(i = 0; i < dimensions.lignes; i++)
            {
                for(j = 0; j < dimensions.colonnes; j++)
                {
                    monTableauDeMines[i][j]= 0;
                    monTableauAffichage[i][j]= -1;
                }
            }
    deposer_mines(dimensions, monTableauDeMines, nombreMines);
    }
