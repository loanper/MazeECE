//Code couleur :  https://www.jetbrains.com/help/clion/configuring-colors-and-fonts.html
//Code reset console : https://stackoverflow.com/questions/74620248/how-can-i-clear-console-while-running-program-in-clion
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TAILLE 23
#define MUR 220
#define PASSAGE 255
#define Tresor 24 //nombre de tresor


//declaration variable globale :
int tresor_trouve_joueur1 = 0;
int tresor_trouve_joueur2 = 0;
int tresor_trouve_joueur3 = 0;
int tresor_trouve_joueur4 = 0;

void Menu();

void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void ClearScreen() {
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Afficher_Plateau_De_Jeu(int matrice[TAILLE][TAILLE]) {
    ClearScreen();
    int i;
    int j;
    int k;
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            Color(9, 0);
            if ((i == 0 && j == 5) || (i == 0 && j == 11) || (i == 0 && j == 17) || (i == 22 && j == 5) ||
                (i == 22 && j == 11) || (i == 22 && j == 17) || (i == 5 && j == 0) || (i == 11 && j == 0) ||
                (i == 17 && j == 0) || (i == 5 && j == 22) || (i == 11 && j == 22) || (i == 17 && j == 22)) {
                Color(4, 0);
            }
            for (k = 65; k <= 89; k++) {
                if (matrice[i][j] == k) {
                    Color(6, 0);
                }
            }
            if (matrice[i][j] == '1') {
                Color(10, 0);
            } else if (matrice[i][j] == '2') {
                Color(13, 0);
            } else if (matrice[i][j] == '3') {
                Color(15, 0);
            } else if (matrice[i][j] == '4') {
                Color(12, 0);
            }
            printf("%c ", matrice[i][j]);
        }
        printf("\n");
    }
}

void Remplir_les_cases_vides(
        int matrice[TAILLE][TAILLE]) {   //utile pour afficher des vides entre les fleches sans ce sous programe il y aurai des symboles random de la table ascii entre les fleches
    int i;
    int j;
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            matrice[i][j] = 256;
        }
    }
}



/////////////////////////////////////////////////////////DECALAGE DES LIGNES////////////////////////////////////////////
////////////////////////////////////////////VERS LA DROITE//////////////////////////////////////////////////////////////
void Decaler_a_droite_ligne_1(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 4; x < 7; x++) {
        for (int y = 19; y < 22; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 19;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[4][19];
    matrice_qui_sort[0][1] = matrice[4][20];
    matrice_qui_sort[0][2] = matrice[4][21];
    matrice_qui_sort[1][0] = matrice[5][19];
    matrice_qui_sort[1][1] = matrice[5][20];
    matrice_qui_sort[1][2] = matrice[5][21];
    matrice_qui_sort[2][0] = matrice[6][19];
    matrice_qui_sort[2][1] = matrice[6][20];
    matrice_qui_sort[2][2] = matrice[6][21];


    for (compteur = 0; compteur < 7; compteur++) {
        matrice[4][j] = matrice[4][j - 3];
        matrice[4][j + 1] = matrice[4][j - 2];
        matrice[4][j + 2] = matrice[4][j - 1];
        matrice[5][j] = matrice[5][j - 3];
        matrice[5][j + 1] = matrice[5][j - 2];
        matrice[5][j + 2] = matrice[5][j - 1];
        matrice[6][j] = matrice[6][j - 3];
        matrice[6][j + 1] = matrice[6][j - 2];
        matrice[6][j + 2] = matrice[6][j - 1];
        j = j - 3;
        //Sleep(1000);
        //Afficher_Plateau_De_Jeu(matrice);
    }
    matrice[4][1] = matrice_en_plus[0][0];
    matrice[4][2] = matrice_en_plus[1][0];
    matrice[4][3] = matrice_en_plus[2][0];
    matrice[5][1] = matrice_en_plus[0][1];
    matrice[5][2] = matrice_en_plus[1][1];
    matrice[5][3] = matrice_en_plus[2][1];
    matrice[6][1] = matrice_en_plus[0][2];
    matrice[6][2] = matrice_en_plus[1][2];
    matrice[6][3] = matrice_en_plus[2][2];

    if (e == 1) { matrice[5][2] = '1'; }
    if (e == 2) { matrice[5][2] = '2'; }
    if (e == 3) { matrice[5][2] = '3'; }
    if (e == 4) { matrice[5][2] = '4'; }

    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }

}

void Decaler_a_droite_ligne_2(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 10; x < 13; x++) {
        for (int y = 19; y < 22; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 19;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[10][19];
    matrice_qui_sort[0][1] = matrice[10][20];
    matrice_qui_sort[0][2] = matrice[10][21];
    matrice_qui_sort[1][0] = matrice[11][19];
    matrice_qui_sort[1][1] = matrice[11][20];
    matrice_qui_sort[1][2] = matrice[11][21];
    matrice_qui_sort[2][0] = matrice[12][19];
    matrice_qui_sort[2][1] = matrice[12][20];
    matrice_qui_sort[2][2] = matrice[12][21];


    for (compteur = 0; compteur < 6; compteur++) {
        matrice[10][j] = matrice[10][j - 3];
        matrice[10][j + 1] = matrice[10][j - 2];
        matrice[10][j + 2] = matrice[10][j - 1];
        matrice[11][j] = matrice[11][j - 3];
        matrice[11][j + 1] = matrice[11][j - 2];
        matrice[11][j + 2] = matrice[11][j - 1];
        matrice[12][j] = matrice[12][j - 3];
        matrice[12][j + 1] = matrice[12][j - 2];
        matrice[12][j + 2] = matrice[12][j - 1];
        j = j - 3;

    }
    matrice[10][1] = matrice_en_plus[0][0];
    matrice[10][2] = matrice_en_plus[1][0];
    matrice[10][3] = matrice_en_plus[2][0];
    matrice[11][1] = matrice_en_plus[0][1];
    matrice[11][2] = matrice_en_plus[1][1];
    matrice[11][3] = matrice_en_plus[2][1];
    matrice[12][1] = matrice_en_plus[0][2];
    matrice[12][2] = matrice_en_plus[1][2];
    matrice[12][3] = matrice_en_plus[2][2];
    if (e == 1) { matrice[11][2] = '1'; }
    if (e == 2) { matrice[11][2] = '2'; }
    if (e == 3) { matrice[11][2] = '3'; }
    if (e == 4) { matrice[11][2] = '4'; }

    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_a_droite_ligne_3(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 16; x < 19; x++) {
        for (int y = 19; y < 22; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 19;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[16][19];
    matrice_qui_sort[0][1] = matrice[16][20];
    matrice_qui_sort[0][2] = matrice[16][21];
    matrice_qui_sort[1][0] = matrice[17][19];
    matrice_qui_sort[1][1] = matrice[17][20];
    matrice_qui_sort[1][2] = matrice[17][21];
    matrice_qui_sort[2][0] = matrice[18][19];
    matrice_qui_sort[2][1] = matrice[18][20];
    matrice_qui_sort[2][2] = matrice[18][21];


    for (compteur = 0; compteur < 6; compteur++) {
        matrice[16][j] = matrice[16][j - 3];
        matrice[16][j + 1] = matrice[16][j - 2];
        matrice[16][j + 2] = matrice[16][j - 1];
        matrice[17][j] = matrice[17][j - 3];
        matrice[17][j + 1] = matrice[17][j - 2];
        matrice[17][j + 2] = matrice[17][j - 1];
        matrice[18][j] = matrice[18][j - 3];
        matrice[18][j + 1] = matrice[18][j - 2];
        matrice[18][j + 2] = matrice[18][j - 1];
        j = j - 3;

    }
    matrice[16][1] = matrice_en_plus[0][0];
    matrice[16][2] = matrice_en_plus[1][0];
    matrice[16][3] = matrice_en_plus[2][0];
    matrice[17][1] = matrice_en_plus[0][1];
    matrice[17][2] = matrice_en_plus[1][1];
    matrice[17][3] = matrice_en_plus[2][1];
    matrice[18][1] = matrice_en_plus[0][2];
    matrice[18][2] = matrice_en_plus[1][2];
    matrice[18][3] = matrice_en_plus[2][2];
    if (e == 1) { matrice[17][2] = '1'; }
    if (e == 2) { matrice[17][2] = '2'; }
    if (e == 3) { matrice[17][2] = '3'; }
    if (e == 4) { matrice[17][2] = '4'; }

    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }

}
/////////////////////////////////////////////////////////DECALAGE DES LIGNES////////////////////////////////////////////
////////////////////////////////////////////VERS LA GAUCHE//////////////////////////////////////////////////////////////

void Decaler_a_gauche_ligne_1(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 4; x < 7; x++) {
        for (int y = 1; y < 4; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[4][1];
    matrice_qui_sort[0][1] = matrice[4][2];
    matrice_qui_sort[0][2] = matrice[4][3];
    matrice_qui_sort[1][0] = matrice[5][1];
    matrice_qui_sort[1][1] = matrice[5][2];
    matrice_qui_sort[1][2] = matrice[5][3];
    matrice_qui_sort[2][0] = matrice[6][1];
    matrice_qui_sort[2][1] = matrice[6][2];
    matrice_qui_sort[2][2] = matrice[6][3];

    for (compteur = 0; compteur < 7; compteur++) {
        matrice[4][j] = matrice[4][j + 3];
        matrice[4][j + 1] = matrice[4][j + 4];
        matrice[4][j + 2] = matrice[4][j + 5];
        matrice[5][j] = matrice[5][j + 3];
        matrice[5][j + 1] = matrice[5][j + 4];
        matrice[5][j + 2] = matrice[5][j + 5];
        matrice[6][j] = matrice[6][j + 3];
        matrice[6][j + 1] = matrice[6][j + 4];
        matrice[6][j + 2] = matrice[6][j + 5];
        j = j + 3;
    }
    matrice[4][19] = matrice_en_plus[0][0];
    matrice[4][20] = matrice_en_plus[1][0];
    matrice[4][21] = matrice_en_plus[2][0];
    matrice[5][19] = matrice_en_plus[0][1];
    matrice[5][20] = matrice_en_plus[1][1];
    matrice[5][21] = matrice_en_plus[2][1];
    matrice[6][19] = matrice_en_plus[0][2];
    matrice[6][20] = matrice_en_plus[1][2];
    matrice[6][21] = matrice_en_plus[2][2];
    if (e == 1) { matrice[5][20] = '1'; }
    if (e == 2) { matrice[5][20] = '2'; }
    if (e == 3) { matrice[5][20] = '3'; }
    if (e == 4) { matrice[5][20] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_a_gauche_ligne_2(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 10; x < 13; x++) {
        for (int y = 1; y < 4; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[10][1];
    matrice_qui_sort[0][1] = matrice[10][2];
    matrice_qui_sort[0][2] = matrice[10][3];
    matrice_qui_sort[1][0] = matrice[11][1];
    matrice_qui_sort[1][1] = matrice[11][2];
    matrice_qui_sort[1][2] = matrice[11][3];
    matrice_qui_sort[2][0] = matrice[12][1];
    matrice_qui_sort[2][1] = matrice[12][2];
    matrice_qui_sort[2][2] = matrice[12][3];


    for (compteur = 0; compteur < 7; compteur++) {
        matrice[10][j] = matrice[10][j + 3];
        matrice[10][j + 1] = matrice[10][j + 4];
        matrice[10][j + 2] = matrice[10][j + 5];
        matrice[11][j] = matrice[11][j + 3];
        matrice[11][j + 1] = matrice[11][j + 4];
        matrice[11][j + 2] = matrice[11][j + 5];
        matrice[12][j] = matrice[12][j + 3];
        matrice[12][j + 1] = matrice[12][j + 4];
        matrice[12][j + 2] = matrice[12][j + 5];
        j = j + 3;
    }
    matrice[10][19] = matrice_en_plus[0][0];
    matrice[10][20] = matrice_en_plus[1][0];
    matrice[10][21] = matrice_en_plus[2][0];
    matrice[11][19] = matrice_en_plus[0][1];
    matrice[11][20] = matrice_en_plus[1][1];
    matrice[11][21] = matrice_en_plus[2][1];
    matrice[12][19] = matrice_en_plus[0][2];
    matrice[12][20] = matrice_en_plus[1][2];
    matrice[12][21] = matrice_en_plus[2][2];
    if (e == 1) { matrice[11][20] = '1'; }
    if (e == 2) { matrice[11][20] = '2'; }
    if (e == 3) { matrice[11][20] = '3'; }
    if (e == 4) { matrice[11][20] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_a_gauche_ligne_3(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 16; x < 19; x++) {
        for (int y = 1; y < 4; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int j = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[16][1];
    matrice_qui_sort[0][1] = matrice[16][2];
    matrice_qui_sort[0][2] = matrice[16][3];
    matrice_qui_sort[1][0] = matrice[17][1];
    matrice_qui_sort[1][1] = matrice[17][2];
    matrice_qui_sort[1][2] = matrice[17][3];
    matrice_qui_sort[2][0] = matrice[18][1];
    matrice_qui_sort[2][1] = matrice[18][2];
    matrice_qui_sort[2][2] = matrice[18][3];

    for (compteur = 0; compteur < 7; compteur++) {
        matrice[16][j] = matrice[16][j + 3];
        matrice[16][j + 1] = matrice[16][j + 4];
        matrice[16][j + 2] = matrice[16][j + 5];
        matrice[17][j] = matrice[17][j + 3];
        matrice[17][j + 1] = matrice[17][j + 4];
        matrice[17][j + 2] = matrice[17][j + 5];
        matrice[18][j] = matrice[18][j + 3];
        matrice[18][j + 1] = matrice[18][j + 4];
        matrice[18][j + 2] = matrice[18][j + 5];
        j = j + 3;
    }
    matrice[16][19] = matrice_en_plus[0][0];
    matrice[16][20] = matrice_en_plus[1][0];
    matrice[16][21] = matrice_en_plus[2][0];
    matrice[17][19] = matrice_en_plus[0][1];
    matrice[17][20] = matrice_en_plus[1][1];
    matrice[17][21] = matrice_en_plus[2][1];
    matrice[18][19] = matrice_en_plus[0][2];
    matrice[18][20] = matrice_en_plus[1][2];
    matrice[18][21] = matrice_en_plus[2][2];
    if (e == 1) { matrice[17][20] = '1'; }
    if (e == 2) { matrice[17][20] = '2'; }
    if (e == 3) { matrice[17][20] = '3'; }
    if (e == 4) { matrice[17][20] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

/////////////////////////////////////////////////////////DECALAGE DES LIGNES////////////////////////////////////////////
////////////////////////////////////////////VERS LE HAUT/////////////////////////////////////////////////////////////////
void Decaler_en_haut_ligne_1(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 1; x < 4; x++) {
        for (int y = 4; y < 7; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[1][4];
    matrice_qui_sort[0][1] = matrice[1][5];
    matrice_qui_sort[0][2] = matrice[1][6];
    matrice_qui_sort[1][0] = matrice[2][4];
    matrice_qui_sort[1][1] = matrice[2][5];
    matrice_qui_sort[1][2] = matrice[2][6];
    matrice_qui_sort[2][0] = matrice[3][4];
    matrice_qui_sort[2][1] = matrice[3][5];
    matrice_qui_sort[2][2] = matrice[3][6];


    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][4] = matrice[i + 3][4];
        matrice[i + 1][4] = matrice[i + 4][4];
        matrice[i + 2][4] = matrice[i + 5][4];
        matrice[i][5] = matrice[i + 3][5];
        matrice[i + 1][5] = matrice[i + 4][5];
        matrice[i + 2][5] = matrice[i + 5][5];
        matrice[i][6] = matrice[i + 3][6];
        matrice[i + 1][6] = matrice[i + 4][6];
        matrice[i + 2][6] = matrice[i + 5][6];
        i = i + 3;
    }
    matrice[19][4] = matrice_en_plus[0][0];
    matrice[19][5] = matrice_en_plus[1][0];
    matrice[19][6] = matrice_en_plus[2][0];
    matrice[20][4] = matrice_en_plus[0][1];
    matrice[20][5] = matrice_en_plus[1][1];
    matrice[20][6] = matrice_en_plus[2][1];
    matrice[21][4] = matrice_en_plus[0][2];
    matrice[21][5] = matrice_en_plus[1][2];
    matrice[21][6] = matrice_en_plus[2][2];
    if (e == 1) { matrice[20][5] = '1'; }
    if (e == 2) { matrice[20][5] = '2'; }
    if (e == 3) { matrice[20][5] = '3'; }
    if (e == 4) { matrice[20][5] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_en_haut_ligne_2(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 1; x < 4; x++) {
        for (int y = 10; y < 13; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[1][10];
    matrice_qui_sort[0][1] = matrice[1][11];
    matrice_qui_sort[0][2] = matrice[1][12];
    matrice_qui_sort[1][0] = matrice[2][10];
    matrice_qui_sort[1][1] = matrice[2][11];
    matrice_qui_sort[1][2] = matrice[2][12];
    matrice_qui_sort[2][0] = matrice[3][10];
    matrice_qui_sort[2][1] = matrice[3][11];
    matrice_qui_sort[2][2] = matrice[3][12];


    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][10] = matrice[i + 3][10];
        matrice[i + 1][10] = matrice[i + 4][10];
        matrice[i + 2][10] = matrice[i + 5][10];
        matrice[i][11] = matrice[i + 3][11];
        matrice[i + 1][11] = matrice[i + 4][11];
        matrice[i + 2][11] = matrice[i + 5][11];
        matrice[i][12] = matrice[i + 3][12];
        matrice[i + 1][12] = matrice[i + 4][12];
        matrice[i + 2][12] = matrice[i + 5][12];
        i = i + 3;
    }
    matrice[19][10] = matrice_en_plus[0][0];
    matrice[19][11] = matrice_en_plus[1][0];
    matrice[19][12] = matrice_en_plus[2][0];
    matrice[20][10] = matrice_en_plus[0][1];
    matrice[20][11] = matrice_en_plus[1][1];
    matrice[20][12] = matrice_en_plus[2][1];
    matrice[21][10] = matrice_en_plus[0][2];
    matrice[21][11] = matrice_en_plus[1][2];
    matrice[21][12] = matrice_en_plus[2][2];
    if (e == 1) { matrice[20][11] = '1'; }
    if (e == 2) { matrice[20][11] = '2'; }
    if (e == 3) { matrice[20][11] = '3'; }
    if (e == 4) { matrice[20][11] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_en_haut_ligne_3(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 1; x < 4; x++) {
        for (int y = 16; y < 19; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 1;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[1][16];
    matrice_qui_sort[0][1] = matrice[1][17];
    matrice_qui_sort[0][2] = matrice[1][18];
    matrice_qui_sort[1][0] = matrice[2][16];
    matrice_qui_sort[1][1] = matrice[2][17];
    matrice_qui_sort[1][2] = matrice[2][18];
    matrice_qui_sort[2][0] = matrice[3][16];
    matrice_qui_sort[2][1] = matrice[3][17];
    matrice_qui_sort[2][2] = matrice[3][18];

    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][16] = matrice[i + 3][16];
        matrice[i + 1][16] = matrice[i + 4][16];
        matrice[i + 2][16] = matrice[i + 5][16];
        matrice[i][17] = matrice[i + 3][17];
        matrice[i + 1][17] = matrice[i + 4][17];
        matrice[i + 2][17] = matrice[i + 5][17];
        matrice[i][18] = matrice[i + 3][18];
        matrice[i + 1][18] = matrice[i + 4][18];
        matrice[i + 2][18] = matrice[i + 5][18];
        i = i + 3;
    }
    matrice[19][16] = matrice_en_plus[0][0];
    matrice[19][17] = matrice_en_plus[1][0];
    matrice[19][18] = matrice_en_plus[2][0];
    matrice[20][16] = matrice_en_plus[0][1];
    matrice[20][17] = matrice_en_plus[1][1];
    matrice[20][18] = matrice_en_plus[2][1];
    matrice[21][16] = matrice_en_plus[0][2];
    matrice[21][17] = matrice_en_plus[1][2];
    matrice[21][18] = matrice_en_plus[2][2];
    if (e == 1) { matrice[20][17] = '1'; }
    if (e == 2) { matrice[20][17] = '2'; }
    if (e == 3) { matrice[20][17] = '3'; }
    if (e == 4) { matrice[20][17] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

/////////////////////////////////////////////////////////DECALAGE DES LIGNES////////////////////////////////////////////
////////////////////////////////////////////VERS LE BAS//////////////////////////////////////////////////////////////////
void Decaler_en_bas_ligne_1(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 19; x < 22; x++) {
        for (int y = 4; y < 7; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 19;
    int matrice_qui_sort[3][3];

    matrice_qui_sort[0][0] = matrice[19][4];
    matrice_qui_sort[0][1] = matrice[19][5];
    matrice_qui_sort[0][2] = matrice[19][6];
    matrice_qui_sort[1][0] = matrice[20][4];
    matrice_qui_sort[1][1] = matrice[20][5];
    matrice_qui_sort[1][2] = matrice[20][6];
    matrice_qui_sort[2][0] = matrice[21][4];
    matrice_qui_sort[2][1] = matrice[21][5];
    matrice_qui_sort[2][2] = matrice[21][6];

    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][4] = matrice[i - 3][4];
        matrice[i + 1][4] = matrice[i - 2][4];
        matrice[i + 2][4] = matrice[i - 1][4];
        matrice[i][5] = matrice[i - 3][5];
        matrice[i + 1][5] = matrice[i - 2][5];
        matrice[i + 2][5] = matrice[i - 1][5];
        matrice[i][6] = matrice[i - 3][6];
        matrice[i + 1][6] = matrice[i - 2][6];
        matrice[i + 2][6] = matrice[i - 1][6];
        i = i - 3;
    }
    matrice[1][4] = matrice_en_plus[0][0];
    matrice[1][5] = matrice_en_plus[1][0];
    matrice[1][6] = matrice_en_plus[2][0];
    matrice[2][4] = matrice_en_plus[0][1];
    matrice[2][5] = matrice_en_plus[1][1];
    matrice[2][6] = matrice_en_plus[2][1];
    matrice[3][4] = matrice_en_plus[0][2];
    matrice[3][5] = matrice_en_plus[1][2];
    matrice[3][6] = matrice_en_plus[2][2];
    if (e == 1) { matrice[2][5] = '1'; }
    if (e == 2) { matrice[2][5] = '2'; }
    if (e == 3) { matrice[2][5] = '3'; }
    if (e == 4) { matrice[2][5] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_en_bas_ligne_2(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 19; x < 22; x++) {
        for (int y = 10; y < 13; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 19;
    int matrice_qui_sort[3][3];
    matrice_qui_sort[0][0] = matrice[19][10];
    matrice_qui_sort[0][1] = matrice[19][11];
    matrice_qui_sort[0][2] = matrice[19][12];
    matrice_qui_sort[1][0] = matrice[20][10];
    matrice_qui_sort[1][1] = matrice[20][11];
    matrice_qui_sort[1][2] = matrice[20][12];
    matrice_qui_sort[2][0] = matrice[21][10];
    matrice_qui_sort[2][1] = matrice[21][11];
    matrice_qui_sort[2][2] = matrice[21][12];

    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][10] = matrice[i - 3][10];
        matrice[i + 1][10] = matrice[i - 2][10];
        matrice[i + 2][10] = matrice[i - 1][10];
        matrice[i][11] = matrice[i - 3][11];
        matrice[i + 1][11] = matrice[i - 2][11];
        matrice[i + 2][11] = matrice[i - 1][11];
        matrice[i][12] = matrice[i - 3][12];
        matrice[i + 1][12] = matrice[i - 2][12];
        matrice[i + 2][12] = matrice[i - 1][12];
        i = i - 3;
    }
    matrice[1][10] = matrice_en_plus[0][0];
    matrice[1][11] = matrice_en_plus[1][0];
    matrice[1][12] = matrice_en_plus[2][0];
    matrice[2][10] = matrice_en_plus[0][1];
    matrice[2][11] = matrice_en_plus[1][1];
    matrice[2][12] = matrice_en_plus[2][1];
    matrice[3][10] = matrice_en_plus[0][2];
    matrice[3][11] = matrice_en_plus[1][2];
    matrice[3][12] = matrice_en_plus[2][2];
    if (e == 1) { matrice[2][11] = '1'; }
    if (e == 2) { matrice[2][11] = '2'; }
    if (e == 3) { matrice[2][11] = '3'; }
    if (e == 4) { matrice[2][11] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void Decaler_en_bas_ligne_3(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int e = 0;
    for (int x = 19; x < 22; x++) {
        for (int y = 16; y < 19; y++) {
            if (matrice[x][y] == '1') {
                e = 1;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '2') {
                e = 2;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '3') {
                e = 3;
                matrice[x][y] = PASSAGE;
            }
            if (matrice[x][y] == '4') {
                e = 4;
                matrice[x][y] = PASSAGE;
            }
        }
    }
    int compteur;
    int i = 19;
    int matrice_qui_sort[3][3];
    matrice_qui_sort[0][0] = matrice[19][16];
    matrice_qui_sort[0][1] = matrice[19][17];
    matrice_qui_sort[0][2] = matrice[19][18];
    matrice_qui_sort[1][0] = matrice[20][16];
    matrice_qui_sort[1][1] = matrice[20][17];
    matrice_qui_sort[1][2] = matrice[20][18];
    matrice_qui_sort[2][0] = matrice[21][16];
    matrice_qui_sort[2][1] = matrice[21][17];
    matrice_qui_sort[2][2] = matrice[21][18];
    for (compteur = 0; compteur < 7; compteur++) {
        matrice[i][16] = matrice[i - 3][16];
        matrice[i + 1][16] = matrice[i - 2][16];
        matrice[i + 2][16] = matrice[i - 1][16];
        matrice[i][17] = matrice[i - 3][17];
        matrice[i + 1][17] = matrice[i - 2][17];
        matrice[i + 2][17] = matrice[i - 1][17];
        matrice[i][18] = matrice[i - 3][18];
        matrice[i + 1][18] = matrice[i - 2][18];
        matrice[i + 2][18] = matrice[i - 1][18];
        i = i - 3;
    }
    matrice[1][16] = matrice_en_plus[0][0];
    matrice[1][17] = matrice_en_plus[1][0];
    matrice[1][18] = matrice_en_plus[2][0];
    matrice[2][16] = matrice_en_plus[0][1];
    matrice[2][17] = matrice_en_plus[1][1];
    matrice[2][18] = matrice_en_plus[2][1];
    matrice[3][16] = matrice_en_plus[0][2];
    matrice[3][17] = matrice_en_plus[1][2];
    matrice[3][18] = matrice_en_plus[2][2];
    if (e == 1) { matrice[2][17] = '1'; }
    if (e == 2) { matrice[2][17] = '2'; }
    if (e == 3) { matrice[2][17] = '3'; }
    if (e == 4) { matrice[2][17] = '4'; }
    Afficher_Plateau_De_Jeu(matrice);
    int c;
    int d;
    for (c = 0; c < 3; c++) {
        for (d = 0; d < 3; d++) {
            matrice_en_plus[d][c] = matrice_qui_sort[c][d];
        }
    }
}

void victoire_fin_de_jeu(int *victoire) {
    ClearScreen();
    printf("-------------------------------------\n-------------------------------------\n\n");
    switch (*victoire) {
        case 1:
            printf("Le joueur 1 remporte la partie");
            break;
        case 2:
            printf("Le joueur 2 remporte la partie");
            break;
        case 3:
            printf("Le joueur 3 remporte la partie");
            break;
        case 4:
            printf("Le joueur 4 remporte la partie");
            break;
    }
    printf("\n\n-------------------------------------\n-------------------------------------\n\n");


    Sleep(100000000);
}

void initialisation_matrice(int matrice[TAILLE][TAILLE]) {
    int i;
    int j;

    // Tuile immobile 1:
    matrice[1][1] = MUR;
    matrice[1][2] = MUR;
    matrice[1][3] = MUR;
    matrice[2][1] = MUR;
    matrice[3][1] = MUR;
    matrice[3][3] = MUR;
    matrice[2][2] = PASSAGE;
    matrice[2][3] = PASSAGE;
    matrice[3][2] = PASSAGE;
    // Tuile immobile 2 :
    matrice[1][7] = MUR;
    matrice[1][8] = MUR;
    matrice[1][9] = MUR;
    matrice[3][7] = MUR;
    matrice[3][9] = MUR;
    matrice[3][8] = PASSAGE;
    matrice[2][7] = PASSAGE;
    matrice[2][8] = 77;
    matrice[2][9] = PASSAGE;
    // Tuile immobile 3 :
    matrice[1][13] = MUR;
    matrice[1][14] = MUR;
    matrice[1][15] = MUR;
    matrice[3][13] = MUR;
    matrice[3][15] = MUR;
    matrice[3][14] = PASSAGE;
    matrice[2][13] = PASSAGE;
    matrice[2][14] = 78;
    matrice[2][15] = PASSAGE;
    // Tuile immobile 4 :
    matrice[1][19] = MUR;
    matrice[1][20] = MUR;
    matrice[1][21] = MUR;
    matrice[3][19] = MUR;
    matrice[3][21] = MUR;
    matrice[3][20] = PASSAGE;
    matrice[2][19] = PASSAGE;
    matrice[2][20] = PASSAGE;
    matrice[2][21] = MUR;
    // Tuile immobile 5:
    matrice[7][1] = MUR;
    matrice[7][2] = PASSAGE;
    matrice[7][3] = MUR;
    matrice[8][1] = MUR;
    matrice[9][1] = MUR;
    matrice[9][3] = MUR;
    matrice[8][2] = 79;
    matrice[8][3] = PASSAGE;
    matrice[9][2] = PASSAGE;
    // Tuile immobile 6 :
    matrice[7][7] = MUR;
    matrice[7][8] = PASSAGE;
    matrice[7][9] = MUR;
    matrice[8][7] = MUR;
    matrice[8][9] = PASSAGE;
    matrice[8][8] = 80;
    matrice[9][7] = MUR;
    matrice[9][8] = PASSAGE;
    matrice[9][9] = MUR;
    // Tuile immobile 7 :
    matrice[7][13] = MUR;
    matrice[7][14] = MUR;
    matrice[7][15] = MUR;
    matrice[9][13] = MUR;
    matrice[9][15] = MUR;
    matrice[9][14] = PASSAGE;
    matrice[8][13] = PASSAGE;
    matrice[8][14] = 81;
    matrice[8][15] = PASSAGE;
    // Tuile immobile 8 :
    matrice[7][19] = MUR;
    matrice[7][20] = PASSAGE;
    matrice[7][21] = MUR;
    matrice[9][19] = MUR;
    matrice[9][21] = MUR;
    matrice[9][20] = PASSAGE;
    matrice[8][19] = PASSAGE;
    matrice[8][20] = 82;
    matrice[8][21] = MUR;
    // Tuile immobile 9:
    matrice[13][1] = MUR;
    matrice[13][2] = PASSAGE;
    matrice[13][3] = MUR;
    matrice[14][1] = MUR;
    matrice[15][1] = MUR;
    matrice[15][3] = MUR;
    matrice[14][2] = 83;
    matrice[14][3] = PASSAGE;
    matrice[15][2] = PASSAGE;
    // Tuile immobile 10 :
    matrice[13][7] = MUR;
    matrice[13][8] = PASSAGE;
    matrice[13][9] = MUR;
    matrice[14][7] = PASSAGE;
    matrice[14][9] = PASSAGE;
    matrice[14][8] = 84;
    matrice[15][7] = MUR;
    matrice[15][8] = MUR;
    matrice[15][9] = MUR;
    // Tuile immobile 11 :
    matrice[13][13] = MUR;
    matrice[13][14] = PASSAGE;
    matrice[13][15] = MUR;
    matrice[15][13] = MUR;
    matrice[15][15] = MUR;
    matrice[15][14] = PASSAGE;
    matrice[14][13] = PASSAGE;
    matrice[14][14] = 85;
    matrice[14][15] = MUR;
    // Tuile immobile 12 :
    matrice[13][19] = MUR;
    matrice[13][20] = PASSAGE;
    matrice[13][21] = MUR;
    matrice[15][19] = MUR;
    matrice[15][21] = MUR;
    matrice[15][20] = PASSAGE;
    matrice[14][19] = PASSAGE;
    matrice[14][20] = 86;
    matrice[14][21] = MUR;
    // Tuile immobile 13:
    matrice[19][1] = MUR;
    matrice[19][2] = PASSAGE;
    matrice[19][3] = MUR;
    matrice[20][1] = MUR;
    matrice[21][1] = MUR;
    matrice[21][3] = MUR;
    matrice[20][2] = PASSAGE;
    matrice[20][3] = PASSAGE;
    matrice[21][2] = MUR;
    // Tuile immobile 14 :
    matrice[19][7] = MUR;
    matrice[19][8] = PASSAGE;
    matrice[19][9] = MUR;
    matrice[20][7] = PASSAGE;
    matrice[20][9] = PASSAGE;
    matrice[20][8] = 87;
    matrice[21][7] = MUR;
    matrice[21][8] = MUR;
    matrice[21][9] = MUR;
    // Tuile immobile 15 :
    matrice[19][13] = MUR;
    matrice[19][14] = PASSAGE;
    matrice[19][15] = MUR;
    matrice[20][13] = PASSAGE;
    matrice[20][15] = PASSAGE;
    matrice[20][14] = 88;
    matrice[21][13] = MUR;
    matrice[21][14] = MUR;
    matrice[21][15] = MUR;
    // Tuile immobile 16 :
    matrice[19][19] = MUR;
    matrice[19][20] = PASSAGE;
    matrice[19][21] = MUR;
    matrice[21][19] = MUR;
    matrice[21][21] = MUR;
    matrice[21][20] = MUR;
    matrice[20][19] = PASSAGE;
    matrice[20][20] = PASSAGE;
    matrice[20][21] = MUR;
    //fleche indicative vers le haut :
    matrice[0][5] = 25; //25 représente flèche vers le bas table ascii
    matrice[0][11] = 25;
    matrice[0][17] = 25;
    //fleche indicative vers le bas :
    matrice[22][5] = 24; //24 représente flèche vers le haut table ascii
    matrice[22][11] = 24;
    matrice[22][17] = 24;
    //fleche indicative vers la droite :
    matrice[5][0] = 26; //26 représente flèche vers la droite table ascii
    matrice[11][0] = 26;
    matrice[17][0] = 26;
    //fleche indicative vers la gauche :
    matrice[5][22] = 27; //27 représente flèche vers la gauche table ascii
    matrice[11][22] = 27;
    matrice[17][22] = 27;
}

void matrice_en_pluss(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {

    //while (1) {
    Color(9, 0);
    printf("\n\n Voici la piece en plus : \n\n");
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            Color(4, 0);
            printf("%c ", matrice_en_plus[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");
    Color(9, 0);
    printf("Vous pouvez desormais choisir de faire rentrer la piece en plus ou de lui faire faire une rotation\n\n");
    int choix_Rotation_ou_insertion = 0;
    while (choix_Rotation_ou_insertion != 2) {
        printf("1. Rotation\n");
        printf("2. Inserer la piece\n");
        printf("3. Retour au Menu\n");
        scanf("%d", &choix_Rotation_ou_insertion);
        switch (choix_Rotation_ou_insertion) {
            case 3:
                ClearScreen();
                Menu();
                Afficher_Plateau_De_Jeu(matrice);
                Color(9, 0);
                printf("\n\n Voici la piece en plus : \n\n");
                int i;
                int j;
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        Color(4, 0);
                        printf("%c ", matrice_en_plus[j][i]);
                    }
                    printf("\n");
                    Color(9,0);
                }

                break;
            case 1: // le probleme ici est qu'on doit appliquer un ordre dans la rotation sinon on perd la valeur des cases des matrices
                //c'est pourquoi on utilise deux cases temporaires pour se souvenir de la valeur de deux case "en haut de chaine"

                matrice_en_plus[3][3] = matrice_en_plus[0][0];

                matrice_en_plus[0][0] = matrice_en_plus[2][0];
                matrice_en_plus[2][0] = matrice_en_plus[2][2];
                matrice_en_plus[2][2] = matrice_en_plus[0][2];
                matrice_en_plus[0][2] = matrice_en_plus[3][3]; //on utilise la case vide 3 3 pour stocker la valeur de la case 0 0 modifié juste au dessus


                matrice_en_plus[3][2] = matrice_en_plus[0][1]; //idem

                matrice_en_plus[0][1] = matrice_en_plus[1][0];
                matrice_en_plus[1][0] = matrice_en_plus[2][1];
                matrice_en_plus[2][1] = matrice_en_plus[1][2];
                matrice_en_plus[1][2] = matrice_en_plus[3][2];

                matrice_en_plus[1][1] = matrice_en_plus[1][1];

                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        Color(4, 0);
                        printf("%c ", matrice_en_plus[j][i]);
                    }
                    printf("\n");
                }
                printf("\n\n");
                Color(9, 0);
                break;
        }
    }


    //ici l'utilisateur choisi d'insérer la pièce.


    int choix_direction;
    int choix_deplacement;
    printf("Ou voulez vous inserer la piece ? \n\n");
    printf("1. Sur le cote gauche\n");
    printf("2. Sur le cote droit\n");
    printf("3. Sur le bas\n");
    printf("4. Sur le haut\n");
    scanf("%d", &choix_direction);
    while (choix_direction < 1 || choix_direction > 4) {
        printf("Erreur : La valeur saisie est trop petite ou trop grande\n Saisissez une valeur comprise entre 1 et 4 SVP\n");
        scanf("%d", &choix_direction);
    }
    if (choix_direction == 1) {
        printf("Sur quelle ligne voulez vous placer la piece ? \n");
        printf("1. La premiere ligne \n");
        printf("2. La deuxieme ligne \n");
        printf("3. La troisieme ligne \n");
        scanf("%d", &choix_deplacement);
        while (choix_deplacement < 1 || choix_deplacement > 3) {
            printf("Erreur : La valeur saisie est trop petite ou trop grande\n Saisissez une valeur comprise entre 1 et 3 SVP\n");
            scanf("%d", &choix_deplacement);
        }


        if (choix_deplacement == 1) {
            Decaler_a_droite_ligne_1(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 2) {
            Decaler_a_droite_ligne_2(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 3) {
            Decaler_a_droite_ligne_3(matrice, matrice_en_plus);
        }
    }
    if (choix_direction == 2) {
        printf("Sur quelle ligne voulez vous placer la piece ? \n");
        printf("1. La premiere ligne \n");
        printf("2. La deuxieme ligne \n");
        printf("3. La troisieme ligne \n");
        scanf("%d", &choix_deplacement);
        while (choix_deplacement < 1 || choix_deplacement > 3) {
            printf("Erreur : La valeur saisie est trop petite ou trop grande\n Saisissez une valeur comprise entre 1 et 3 SVP\n");
            scanf("%d", &choix_deplacement);
        }


        if (choix_deplacement == 1) {
            Decaler_a_gauche_ligne_1(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 2) {
            Decaler_a_gauche_ligne_2(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 3) {
            Decaler_a_gauche_ligne_3(matrice, matrice_en_plus);
        }
    }
    if (choix_direction == 3) {
        printf("Sur quelle colonne voulez vous placer la piece ? \n");
        printf("1. La premiere colone \n");
        printf("2. La deuxieme colone \n");
        printf("3. La troisieme colone \n");
        scanf("%d", &choix_deplacement);
        while (choix_deplacement < 1 || choix_deplacement > 3) {
            printf("Erreur : La valeur saisie est trop petite ou trop grande\n Saisissez une valeur comprise entre 1 et 3 SVP\n");
            scanf("%d", &choix_deplacement);
        }

        if (choix_deplacement == 1) {
            Decaler_en_haut_ligne_1(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 2) {
            Decaler_en_haut_ligne_2(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 3) {
            Decaler_en_haut_ligne_3(matrice, matrice_en_plus);
        }

    }
    if (choix_direction == 4) {
        printf("Sur quelle colonne voulez vous placer la piece ? \n");
        printf("1. La premiere colone \n");
        printf("2. La deuxieme colone \n");
        printf("3. La troisieme colone \n");
        scanf("%d", &choix_deplacement);
        while (choix_deplacement < 1 || choix_deplacement > 3) {
            printf("Erreur : La valeur saisie est trop petite ou trop grande\n Saisissez une valeur comprise entre 1 et 3 SVP\n");
            scanf("%d", &choix_deplacement);
        }


        if (choix_deplacement == 1) {
            Decaler_en_bas_ligne_1(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 2) {
            Decaler_en_bas_ligne_2(matrice, matrice_en_plus);
        }
        if (choix_deplacement == 3) {
            Decaler_en_bas_ligne_3(matrice, matrice_en_plus);
        }
    }
}
//}

int temp1 = PASSAGE;
int temp2 = PASSAGE;
int temp3 = PASSAGE;
int temp4 = PASSAGE;

void joueur_1(int matrice[TAILLE][TAILLE], int joueur1[12], int *nombre_de_tresor, int matrice_en_plus[3][3]) {
    // Affiche les valeurs des joueurs
    printf("\nLe tresor a recuperer est le tresor : %c", joueur1[tresor_trouve_joueur1]);

    matrice_en_pluss(matrice, matrice_en_plus);



    char deplacement;
    printf("C'est au tour du joueur 1");


    while (deplacement != 'a') {

        printf("\nLe tresor a recuperer est le tresor : %c", joueur1[tresor_trouve_joueur1]);
        /*printf("\nLes tresors du joueurs 1 sont :");
        for (int i = 0; i < *nombre_de_tresor; i++) {
            printf("%c ", joueur1[i]);
        }*/
        printf("\n");
        printf("\n z : En haut");
        printf("\n s : En bas");
        printf("\n q : A gauche");
        printf("\n d : A droite\n");
        printf("\n a : Arreter le deplacement");

        fflush(stdin);
        scanf("%c", &deplacement);


        if (deplacement == 'z') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '1') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a - 1][b] == joueur1[tresor_trouve_joueur1]) {
                tresor_trouve_joueur1 = tresor_trouve_joueur1 + 1;
            }


            if (matrice[a - 1][b] != MUR && matrice[a - 1][b] != 24 && matrice[a - 1][b] != 25 &&
                matrice[a - 1][b] != 26 && matrice[a - 1][b] != 27) {

                if (temp1 != PASSAGE) {
                    matrice[a - 1][b] = '1';
                    matrice[a][b] = temp1;
                    temp1 = PASSAGE;
                } else if (matrice[a - 1][b] != PASSAGE) {
                    temp1 = matrice[a - 1][b];
                    matrice[a - 1][b] = '1';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a - 1][b] = '1';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'q') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '1') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b - 1] == joueur1[tresor_trouve_joueur1]) {
                tresor_trouve_joueur1 = tresor_trouve_joueur1 + 1;
            }
            if (matrice[a][b - 1] != MUR && matrice[a][b - 1] != 24 && matrice[a][b - 1] != 25 &&
                matrice[a][b - 1] != 26 && matrice[a][b - 1] != 27) {

                if (temp1 != PASSAGE) {
                    matrice[a][b - 1] = '1';
                    matrice[a][b] = temp1;
                    temp1 = PASSAGE;
                } else if (matrice[a][b - 1] != PASSAGE) {
                    temp1 = matrice[a][b - 1];
                    matrice[a][b - 1] = '1';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b - 1] = '1';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 's') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '1') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a + 1][b] == joueur1[tresor_trouve_joueur1]) {
                tresor_trouve_joueur1 = tresor_trouve_joueur1 + 1;
            }
            if (matrice[a + 1][b] != MUR && matrice[a + 1][b] != 24 && matrice[a + 1][b] != 25 &&
                matrice[a + 1][b] != 26 && matrice[a + 1][b] != 27) {

                if (temp1 != PASSAGE) {
                    matrice[a + 1][b] = '1';
                    matrice[a][b] = temp1;
                    temp1 = PASSAGE;
                } else if (matrice[a + 1][b] != PASSAGE) {
                    temp1 = matrice[a + 1][b];
                    matrice[a + 1][b] = '1';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a + 1][b] = '1';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'd') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '1') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b + 1] == joueur1[tresor_trouve_joueur1]) {
                tresor_trouve_joueur1 = tresor_trouve_joueur1 + 1;
            }
            if (matrice[a][b + 1] != MUR && matrice[a][b + 1] != 24 && matrice[a][b + 1] != 25 &&
                matrice[a][b + 1] != 26 && matrice[a][b + 1] != 27) {

                if (temp1 != PASSAGE) {
                    matrice[a][b + 1] = '1';
                    matrice[a][b] = temp1;
                    temp1 = PASSAGE;
                } else if (matrice[a][b + 1] != PASSAGE) {
                    temp1 = matrice[a][b + 1];
                    matrice[a][b + 1] = '1';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b + 1] = '1';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (tresor_trouve_joueur1 == *nombre_de_tresor) {
            printf("\nLe joueur doit maintenant retourner sur sa case d'origine pour gagner");
            if(matrice[2][2]=='1'){
                printf("gg wp");
                Sleep(1000);
                int victoire = 1;
                victoire_fin_de_jeu(&victoire);
            }

        }
        printf(" Nombre de tresor du joueur 1 : %d", tresor_trouve_joueur1);
        Afficher_Plateau_De_Jeu(matrice);

    }
}

void joueur_2(int matrice[TAILLE][TAILLE], int joueur2[12], int *nombre_de_tresor, int matrice_en_plus[3][3]) {
    printf("\nLe tresor a recuperer est le tresor : %c", joueur2[tresor_trouve_joueur2]);

    matrice_en_pluss(matrice, matrice_en_plus);
    printf("Joueur 2: ");

    char deplacement;
    printf("C'est au tour du joueur 2");

    //int temp = PASSAGE;

    while (deplacement != 'a') {
        printf("\nLe tresor a recuperer est le tresor : %c", joueur2[tresor_trouve_joueur1]);
        printf("\n");
        printf("\n z : En haut");
        printf("\n s : En bas");
        printf("\n q : A gauche");
        printf("\n d : A droite\n");
        printf("\n a : Arreter le deplacement");

        fflush(stdin);
        scanf("%c", &deplacement);

        if (deplacement == 'z') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '2') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a - 1][b] == joueur2[tresor_trouve_joueur1]) {
                tresor_trouve_joueur2 = tresor_trouve_joueur2 + 1;
            }
            if (matrice[a - 1][b] != MUR && matrice[a - 1][b] != 24 && matrice[a - 1][b] != 25 &&
                matrice[a - 1][b] != 26 && matrice[a - 1][b] != 27) {

                if (temp2 != PASSAGE) {
                    matrice[a - 1][b] = '2';
                    matrice[a][b] = temp2;
                    temp2 = PASSAGE;
                } else if (matrice[a - 1][b] != PASSAGE) {
                    temp2 = matrice[a - 1][b];
                    matrice[a - 1][b] = '2';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a - 1][b] = '2';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'q') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '2') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b - 1] == joueur2[tresor_trouve_joueur1]) {
                tresor_trouve_joueur2 = tresor_trouve_joueur2 + 1;
            }
            if (matrice[a][b - 1] != MUR && matrice[a][b - 1] != 24 && matrice[a][b - 1] != 25 &&
                matrice[a][b - 1] != 26 && matrice[a][b - 1] != 27) {

                if (temp2 != PASSAGE) {
                    matrice[a][b - 1] = '2';
                    matrice[a][b] = temp2;
                    temp2 = PASSAGE;
                } else if (matrice[a][b - 1] != PASSAGE) {
                    temp2 = matrice[a][b - 1];
                    matrice[a][b - 1] = '2';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b - 1] = '2';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 's') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '2') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a + 1][b] == joueur2[tresor_trouve_joueur1]) {
                tresor_trouve_joueur2 = tresor_trouve_joueur2 + 1;
            }
            if (matrice[a + 1][b] != MUR && matrice[a + 1][b] != 24 && matrice[a + 1][b] != 25 &&
                matrice[a + 1][b] != 26 && matrice[a + 1][b] != 27) {

                if (temp2 != PASSAGE) {
                    matrice[a + 1][b] = '2';
                    matrice[a][b] = temp2;
                    temp2 = PASSAGE;
                } else if (matrice[a + 1][b] != PASSAGE) {
                    temp2 = matrice[a + 1][b];
                    matrice[a + 1][b] = '2';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a + 1][b] = '2';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'd') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '2') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b + 1] == joueur2[tresor_trouve_joueur1]) {
                tresor_trouve_joueur2 = tresor_trouve_joueur2 + 1;
            }
            if (matrice[a][b + 1] != MUR && matrice[a][b + 1] != 24 && matrice[a][b + 1] != 25 &&
                matrice[a][b + 1] != 26 && matrice[a][b + 1] != 27) {

                if (temp2 != PASSAGE) {
                    matrice[a][b + 1] = '2';
                    matrice[a][b] = temp2;
                    temp2 = PASSAGE;
                } else if (matrice[a][b + 1] != PASSAGE) {
                    temp2 = matrice[a][b + 1];
                    matrice[a][b + 1] = '2';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b + 1] = '2';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        printf(" \nNombre de tresor du joueur 2 : %d", tresor_trouve_joueur2);
        Afficher_Plateau_De_Jeu(matrice);

        if (tresor_trouve_joueur2 == *nombre_de_tresor) {
            printf("\nLe joueur doit maintenant retourner sur sa case d'origine pour gagner");
            if(matrice[20][2]=='2'){
                printf("gg wp");
                Sleep(1000);
                int victoire = 2;
                victoire_fin_de_jeu(&victoire);
            }
        }
    }
}

void joueur_3(int matrice[TAILLE][TAILLE], int joueur3[12], int *nombre_de_tresor, int matrice_en_plus[3][3]) {
    printf("\nLe tresor a recuperer est le tresor : %c", joueur3[tresor_trouve_joueur3]);

    matrice_en_pluss(matrice, matrice_en_plus);
    char deplacement;
    printf("C'est au tour du joueur 3");

    while (deplacement != 'a') {
        printf("\nLe tresor a recuperer est le tresor : %c", joueur3[tresor_trouve_joueur1]);
        printf("\n z : En haut");
        printf("\n s : En bas");
        printf("\n q : A gauche");
        printf("\n d : A droite\n");
        printf("\n a : Arreter le deplacement");

        fflush(stdin);
        scanf("%c", &deplacement);

        if (deplacement == 'z') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '3') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a - 1][b] == joueur3[tresor_trouve_joueur1]) {
                tresor_trouve_joueur3 = tresor_trouve_joueur3 + 1;
            }
            if (matrice[a - 1][b] != MUR && matrice[a - 1][b] != 24 && matrice[a - 1][b] != 25 &&
                matrice[a - 1][b] != 26 && matrice[a - 1][b] != 27) {

                if (temp3 != PASSAGE) {
                    matrice[a - 1][b] = '3';
                    matrice[a][b] = temp3;
                    temp3 = PASSAGE;
                } else if (matrice[a - 1][b] != PASSAGE) {
                    temp3 = matrice[a - 1][b];
                    matrice[a - 1][b] = '3';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a - 1][b] = '3';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'q') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '3') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b - 1] == joueur3[tresor_trouve_joueur1]) {
                tresor_trouve_joueur3 = tresor_trouve_joueur3 + 1;
            }
            if (matrice[a][b - 1] != MUR && matrice[a][b - 1] != 24 && matrice[a][b - 1] != 25 &&
                matrice[a][b - 1] != 26 && matrice[a][b - 1] != 27) {

                if (temp3 != PASSAGE) {
                    matrice[a][b - 1] = '3';
                    matrice[a][b] = temp3;
                    temp3 = PASSAGE;
                } else if (matrice[a][b - 1] != PASSAGE) {
                    temp3 = matrice[a][b - 1];
                    matrice[a][b - 1] = '3';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b - 1] = '3';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 's') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '3') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a + 1][b] == joueur3[tresor_trouve_joueur1]) {
                tresor_trouve_joueur3 = tresor_trouve_joueur3 + 1;
            }
            if (matrice[a + 1][b] != MUR && matrice[a + 1][b] != 24 && matrice[a + 1][b] != 25 &&
                matrice[a + 1][b] != 26 && matrice[a + 1][b] != 27) {

                if (temp3 != PASSAGE) {
                    matrice[a + 1][b] = '3';
                    matrice[a][b] = temp3;
                    temp3 = PASSAGE;
                } else if (matrice[a + 1][b] != PASSAGE) {
                    temp3 = matrice[a + 1][b];
                    matrice[a + 1][b] = '3';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a + 1][b] = '3';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'd') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '3') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b + 1] == joueur3[tresor_trouve_joueur1]) {
                tresor_trouve_joueur3 = tresor_trouve_joueur3 + 1;
            }
            if (matrice[a][b + 1] != MUR && matrice[a][b + 1] != 24 && matrice[a][b + 1] != 25 &&
                matrice[a][b + 1] != 26 && matrice[a][b + 1] != 27) {

                if (temp3 != PASSAGE) {
                    matrice[a][b + 1] = '3';
                    matrice[a][b] = temp3;
                    temp3 = PASSAGE;
                } else if (matrice[a][b + 1] != PASSAGE) {
                    temp3 = matrice[a][b + 1];
                    matrice[a][b + 1] = '3';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b + 1] = '3';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        printf(" \nNombre de tresor du joueur 3 : %d", tresor_trouve_joueur3);
        Afficher_Plateau_De_Jeu(matrice);
        if (tresor_trouve_joueur3 == *nombre_de_tresor) {
            printf("\nLe joueur doit maintenant retourner sur sa case d'origine pour gagner");
            if(matrice[2][20]=='3'){
                printf("gg wp");
                Sleep(1000);
                int victoire = 3;
                victoire_fin_de_jeu(&victoire);
            }
        }
    }
}

void joueur_4(int matrice[TAILLE][TAILLE], int joueur4[12], int *nombre_de_tresor, int matrice_en_plus[3][3]) {
    printf("\nLe tresor a recuperer est le tresor : %c", joueur4[tresor_trouve_joueur2]);

    matrice_en_pluss(matrice, matrice_en_plus);

    char deplacement;
    printf("C'est au tour du joueur 4");

    // int temp4 = PASSAGE;

    while (deplacement != 'a') {
        printf("\nLe tresor a recuperer est le tresor : %c", joueur4[tresor_trouve_joueur1]);
        printf("\n z : En haut");
        printf("\n s : En bas");
        printf("\n q : A gauche");
        printf("\n d : A droite\n");
        printf("\n a : Arreter le deplacement");

        fflush(stdin);
        scanf("%c", &deplacement);

        if (deplacement == 'z') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '4') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a - 1][b] == joueur4[tresor_trouve_joueur1]) {
                tresor_trouve_joueur4 = tresor_trouve_joueur4 + 1;
            }
            if (matrice[a - 1][b] != MUR && matrice[a - 1][b] != 24 && matrice[a - 1][b] != 25 &&
                matrice[a - 1][b] != 26 && matrice[a - 1][b] != 27) {

                if (temp4 != PASSAGE) {
                    matrice[a - 1][b] = '4';
                    matrice[a][b] = temp4;
                    temp4 = PASSAGE;
                } else if (matrice[a - 1][b] != PASSAGE) {
                    temp4 = matrice[a - 1][b];
                    matrice[a - 1][b] = '4';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a - 1][b] = '4';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'q') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '4') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b - 1] == joueur4[tresor_trouve_joueur1]) {
                tresor_trouve_joueur4 = tresor_trouve_joueur4 + 1;
            }
            if (matrice[a][b - 1] != MUR && matrice[a][b - 1] != 24 && matrice[a][b - 1] != 25 &&
                matrice[a][b - 1] != 26 && matrice[a][b - 1] != 27) {

                if (temp4 != PASSAGE) {
                    matrice[a][b - 1] = '4';
                    matrice[a][b] = temp4;
                    temp4 = PASSAGE;
                } else if (matrice[a][b - 1] != PASSAGE) {
                    temp4 = matrice[a][b - 1];
                    matrice[a][b - 1] = '4';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b - 1] = '4';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 's') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '4') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a + 1][b] == joueur4[tresor_trouve_joueur1]) {
                tresor_trouve_joueur4 = tresor_trouve_joueur4 + 1;
            }
            if (matrice[a + 1][b] != MUR && matrice[a + 1][b] != 24 && matrice[a + 1][b] != 25 &&
                matrice[a + 1][b] != 26 && matrice[a + 1][b] != 27) {
                if (temp4 != PASSAGE) {
                    matrice[a + 1][b] = '4';
                    matrice[a][b] = temp4;
                    temp4 = PASSAGE;
                } else if (matrice[a + 1][b] != PASSAGE) {
                    temp4 = matrice[a + 1][b];
                    matrice[a + 1][b] = '4';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a + 1][b] = '4';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        if (deplacement == 'd') {
            int i;
            int j;
            int a;
            int b;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    if (matrice[i][j] == '4') {
                        a = i;
                        b = j;
                    }
                }
            }
            if (matrice[a][b + 1] == joueur4[tresor_trouve_joueur1]) {
                tresor_trouve_joueur4 = tresor_trouve_joueur4 + 1;
            }
            if (matrice[a][b + 1] != MUR && matrice[a][b + 1] != 24 && matrice[a][b + 1] != 25 &&
                matrice[a][b + 1] != 26 && matrice[a][b + 1] != 27) {

                if (temp4 != PASSAGE) {
                    matrice[a][b + 1] = '4';
                    matrice[a][b] = temp4;
                    temp4 = PASSAGE;
                } else if (matrice[a][b + 1] != PASSAGE) {
                    temp4 = matrice[a][b + 1];
                    matrice[a][b + 1] = '4';
                    matrice[a][b] = PASSAGE;
                } else {
                    matrice[a][b + 1] = '4';
                    matrice[a][b] = PASSAGE;
                }
            }
        }
        printf(" \nNombre de tresor du joueur 4 : %d", tresor_trouve_joueur4);
        Afficher_Plateau_De_Jeu(matrice);

        if (tresor_trouve_joueur4 == *nombre_de_tresor) {
            printf("\nLe joueur doit maintenant retourner sur sa case d'origine pour gagner");
            if(matrice[20][20]=='4'){
                printf("gg wp");
                Sleep(1000);
                int victoire = 4;
                victoire_fin_de_jeu(&victoire);
            }
        }
    }
}

void choix_joueur(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3]) {
    int nombre_de_joueur = 0;
    while (nombre_de_joueur < 1 || nombre_de_joueur > 4) {
        printf("Veuillez choisir le nombre de joueur\nPour rappel une partie ce joue de 2 a 4 joueurs \n\nAppuyez sur 1 pour revenir au menu\n");
        scanf("%d", &nombre_de_joueur);
    }
    printf("Vous avez choisi de jouer a %d joueurs\n\n", nombre_de_joueur);

    switch (nombre_de_joueur) {
        case 1:
            ClearScreen();
            Menu();
            break;
        case 2:
            printf("il y a 2 personnages : 1 et 2\n");
            break;
        case 3:
            printf("il y a 3 personnages : 1, 2 et 3\n");
            break;
        case 4:
            printf("il y a 4 personnages : 1, 2, 3 et 4\n");
            break;
    }
    matrice[2][2] = '1';
    matrice[20][2] = '2';
    if (nombre_de_joueur == 3 || nombre_de_joueur == 4) {
        matrice[2][20] = '3';
    }
    if (nombre_de_joueur == 4) {
        matrice[20][20] = '4';
    }
    Afficher_Plateau_De_Jeu(matrice);
    int joueur = 87; //87 = W table ASCII


    if (nombre_de_joueur == 2) {
        int nombre_de_tresor = 12;
        //Distribution des tresor aux joueurs
        int joueur1[nombre_de_tresor];
        int joueur2[nombre_de_tresor];
        int Numero[Tresor] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
                              87, 88}; // tableau de valeurs possibles

        // Mélange les valeurs du tableau
        for (int i = 0; i < Tresor; i++) {
            int j = rand() % Tresor;
            int temp = Numero[i];
            Numero[i] = Numero[j];
            Numero[j] = temp;
        }
        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur1[i] = Numero[i];

        }
        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur2[i] = Numero[i + nombre_de_tresor];
        }

        /*// Affiche les valeurs des joueurs
        printf("Joueur 1: ");
        for (int i = 0; i < 12; i++) {
            printf("%c ", joueur1[i]);
        }
        printf("\n");
        printf("Joueur 2: ");
        for (int i = 0; i < 12; i++) {
            printf("%c ", joueur2[i]);
        }
        printf("\n");*/

        while (1) {
            printf("\nC'est au tour du joueur 1");
            //matrice_en_pluss(matrice, matrice_en_plus);
            joueur_1(matrice, joueur1, &nombre_de_tresor, matrice_en_plus);
            printf("\nC'est au tour du joueur 2");
            printf("\n\n\n\n\n---------");
            //matrice_en_pluss(matrice, matrice_en_plus);
            joueur_2(matrice, joueur2, &nombre_de_tresor, matrice_en_plus);
        }
    }
    if (nombre_de_joueur == 3) {
        int nombre_de_tresor = 8;
        //Distribution des tresor aux joueurs
        int joueur1[nombre_de_tresor];
        int joueur2[nombre_de_tresor];
        int joueur3[nombre_de_tresor];
        int Numero[Tresor] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
                              87, 88}; // tableau de valeurs possibles

        // Mélange les valeurs du tableau
        for (int i = 0; i < Tresor; i++) {
            int j = rand() % Tresor;
            int temp = Numero[i];
            Numero[i] = Numero[j];
            Numero[j] = temp;
        }

        // Distribue les valeurs aux joueurs
        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur1[i] = Numero[i];

        }

        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur2[i] = Numero[i + nombre_de_tresor];
        }

        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur3[i] = Numero[i + nombre_de_tresor + nombre_de_tresor];
        }


        // Affiche les valeurs des joueurs
        /*printf("Joueur 1: ");
        for (int i = 0; i < nombre_de_tresor; i++) {
            printf("%c ", joueur1[i]);
        }
        printf("\n");

        printf("Joueur 2: ");
        for (int i = 0; i < nombre_de_tresor; i++) {
            printf("%c ", joueur2[i]);
        }
        printf("\n");

        printf("Joueur 3: ");
        for (int i = 0; i < nombre_de_tresor; i++) {
            printf("%c ", joueur3[i]);
        }*/
        printf("\n");

        while (1) {
            printf("\nC'est au tour du joueur 1");
            joueur_1(matrice, joueur1, &nombre_de_tresor, matrice_en_plus);
            printf("\n\n\n\n\n---------");
            printf("\nC'est au tour du joueur 2");
            joueur_2(matrice, joueur2, &nombre_de_tresor, matrice_en_plus);
            printf("\n\n\n\n\n---------");
            printf("\nC'est au tour du joueur 3");
            joueur_3(matrice, joueur3, &nombre_de_tresor, matrice_en_plus);
        }
    }
    if (nombre_de_joueur == 4) {
        int nombre_de_tresor = 6;
        int joueur1[nombre_de_tresor];
        int joueur2[nombre_de_tresor];
        int joueur3[nombre_de_tresor];
        int joueur4[nombre_de_tresor];
        int Numero[Tresor] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
                              87, 88}; // tableau de valeurs possibles

        // Mélange les valeurs du tableau
        for (int i = 0; i < Tresor; i++) {
            int j = rand() % Tresor;
            int temp = Numero[i];
            Numero[i] = Numero[j];
            Numero[j] = temp;
        }

        // Distribue les valeurs aux joueurs
        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur1[i] = Numero[i];

        }

        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur2[i] = Numero[i + nombre_de_tresor];
        }

        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur3[i] = Numero[i + nombre_de_tresor + nombre_de_tresor];
        }
        for (int i = 0; i < nombre_de_tresor; i++) {
            joueur4[i] = Numero[i + nombre_de_tresor + nombre_de_tresor + nombre_de_tresor];
        }

        while (1) {
            printf("\n");
            printf("\nC'est au tour du joueur 1");
            joueur_1(matrice, joueur1, &nombre_de_tresor, matrice_en_plus);
            printf("\n\n\n\n\n---------");
            printf("\nC'est au tour du joueur 2");
            joueur_2(matrice, joueur2, &nombre_de_tresor, matrice_en_plus);
            printf("\n\n\n\n\n---------");
            printf("\nC'est au tour du joueur 3");
            joueur_3(matrice, joueur3, &nombre_de_tresor, matrice_en_plus);
            printf("\n\n\n\n\n---------");
            printf("\nC'est au tour du joueur 4");
            joueur_4(matrice, joueur4, &nombre_de_tresor, matrice_en_plus);
        }
    }
}

void premiere_matrice_en_plus(int matrice[TAILLE][TAILLE], int matrice_en_plus[3][3], int *a) {
    switch (*a) {
        case 0:
            //printf("La tuile en moins est une tuile en L");
            matrice_en_plus[0][0] = MUR;
            matrice_en_plus[0][1] = MUR;
            matrice_en_plus[0][2] = MUR;
            matrice_en_plus[1][0] = PASSAGE;
            matrice_en_plus[1][1] = PASSAGE;
            matrice_en_plus[1][2] = MUR;
            matrice_en_plus[2][0] = MUR;
            matrice_en_plus[2][1] = PASSAGE;
            matrice_en_plus[2][2] = MUR;

            break;
        case 1:
            //printf("La tuile en moins est une tuile en I");
            matrice_en_plus[0][0] = MUR;
            matrice_en_plus[0][1] = PASSAGE;
            matrice_en_plus[0][2] = MUR;
            matrice_en_plus[1][0] = MUR;
            matrice_en_plus[1][1] = PASSAGE;
            matrice_en_plus[1][2] = MUR;
            matrice_en_plus[2][0] = MUR;
            matrice_en_plus[2][1] = PASSAGE;
            matrice_en_plus[2][2] = MUR;
            break;
        case 2:
            //printf("La tuile en moins est une tuile en T");
            matrice_en_plus[0][0] = MUR;
            matrice_en_plus[0][1] = PASSAGE;
            matrice_en_plus[0][2] = MUR;
            matrice_en_plus[1][0] = PASSAGE;
            matrice_en_plus[1][1] = 70;
            matrice_en_plus[1][2] = MUR;
            matrice_en_plus[2][0] = MUR;
            matrice_en_plus[2][1] = PASSAGE;
            matrice_en_plus[2][2] = MUR;
            break;
        case 3:
            //printf("La tuile en moins est une tuile en L avec bonus");
            matrice_en_plus[0][0] = MUR;
            matrice_en_plus[0][1] = MUR;
            matrice_en_plus[0][2] = MUR;
            matrice_en_plus[1][0] = PASSAGE;
            matrice_en_plus[1][1] = 76;
            matrice_en_plus[1][2] = MUR;
            matrice_en_plus[2][0] = MUR;
            matrice_en_plus[2][1] = PASSAGE;
            matrice_en_plus[2][2] = MUR;
            break;
    }

    printf("\n\n Voici la piece en plus : \n\n");
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            Color(4, 0);
            printf("%c ", matrice_en_plus[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");
    Color(9, 0);

    choix_joueur(matrice, matrice_en_plus);


}

void Initialisation_tuile_en_mouvement(int matrice[TAILLE][TAILLE]) {

    //Choix (aleatoire) de la tuile qui ne va pas etre sur le plateau au depart

    int Tuile_pas_sur_le_plateau = 0;

    Tuile_pas_sur_le_plateau = rand() % 4;

    int Nombre_Tuile_En_T = 6;
    int Nombre_Tuile_En_L_Bonus = 6;
    int Nombre_Tuile_En_L = 10;
    int Nombre_Tuile_En_I = 12;


    switch (Tuile_pas_sur_le_plateau) {
        case 0:
            Nombre_Tuile_En_T = Nombre_Tuile_En_T - 1;
            break;
        case 1:
            Nombre_Tuile_En_L_Bonus = Nombre_Tuile_En_L_Bonus - 1;
            break;
        case 2:
            Nombre_Tuile_En_L = Nombre_Tuile_En_L - 1;
            break;
        case 3:
            Nombre_Tuile_En_I = Nombre_Tuile_En_I - 1;
            break;
    }

    //-------------------------Tuile en T---------------------------
    int comptage_T = 0;
    int Bonus = 65;
    while (comptage_T < Nombre_Tuile_En_T) {
        int orientation_T;
        orientation_T = rand() % 4;
        int random_j;
        int random_i;
        int i;
        int j;
        switch (orientation_T) {
            case 0:
                //--------------------orientation vers le HAUT :--------------------------
                random_i = rand() % 7;

                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                }
                break;
            case 1:        //--------------------orienté vers le BAS :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                }
                break;
            case 2: //--------------------orienté vers la GAUCHE :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                }
                break;
            case 3:         //--------------------orienté vers la DROITE :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE || matrice[i][j] != MUR) {
                            comptage_T = comptage_T + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus = Bonus + 1;
                        }
                        break;
                }
                break;
        }
    }
    //-------------------------Tuile en I----------------------
    int comptage_I = 0;
    while (comptage_I < Nombre_Tuile_En_I) {
        int orientation_I;
        orientation_I = rand() % 2;
        int random_j;
        int random_i;
        int i;
        int j;
        switch (orientation_I) {
            case 0:
                //--------------------orienté à la verticale :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) { // LEL MOMENT OU CA DECONNE
                    // LEL MOMENT OU CA DECONNE
                    // LEL MOMENT OU CA DECONNE
                    // LEL MOMENT OU CA DECONNE
                    // LEL MOMENT OU CA DECONNE
                    // LEL MOMENT OU CA DECONNE
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;

            case 1:
                //--------------------orienté horizontal :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_I = comptage_I + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;
        }
    }
//----------------------------Tuile en L (sans bonus)---------------------------------------------------------------
    int comptage_L = 0;
    while (comptage_L < Nombre_Tuile_En_L) {
        int orientation_L;
        orientation_L = rand() % 4;
        //orientation_J=3;
        int random_j;
        int random_i;
        int i;
        int j;
        switch (orientation_L) {
            case 0:
                //--------------------orienté à la verticale :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;

            case 1:
                //--------------------orienté horizontal :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;
            case 2:
                //--------------------orienté à la verticale :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;

            case 3:
                //--------------------orientation en bas a droite :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L = comptage_L + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = PASSAGE;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                        }
                        break;
                }
                break;
        }
    }
    //------------------------------Tuile en L BONUS--------------------------------
    int comptage_L_Bonus = 0;
    int Bonus_L = 71;
    while (comptage_L_Bonus < Nombre_Tuile_En_L_Bonus) {
        int orientation_L_Bonus;
        orientation_L_Bonus = rand() % 4;
        //orientation_J=3;
        int random_j;
        int random_i;
        int i;
        int j;

        switch (orientation_L_Bonus) {
            case 0:
                //--------------------orienté à la verticale :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                }
                break;

            case 1:
                //--------------------orienté horizontal :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = PASSAGE;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = MUR;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                }
                break;
            case 2:
                //--------------------orienté à la verticale :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = PASSAGE;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = MUR;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                }
                break;

            case 3:
                //--------------------orientation en bas a droite :--------------------------
                random_i = rand() % 7;
                switch (random_i) {
                    case 0:
                        i = 1;
                        break;
                    case 1:
                        i = 4;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 10;
                        break;
                    case 4:
                        i = 13;
                        break;
                    case 5:
                        i = 16;
                        break;
                    case 6:
                        i = 19;
                        break;
                }
                random_j = rand() % 7;
                switch (random_j) {
                    case 0:
                        j = 1;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 1:
                        j = 4;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 2:
                        j = 7;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 3:
                        j = 10;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 4:
                        j = 13;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 5:
                        j = 16;
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                    case 6:
                        j = 19;
                        if (i == 1 || i == 7) {
                            i = i + 3;
                        }
                        if (i == 13 || i == 19) {
                            i = 16;
                        }
                        if (matrice[i][j] != PASSAGE && matrice[i][j] != MUR) {
                            comptage_L_Bonus = comptage_L_Bonus + 1;
                            matrice[i][j] = MUR;
                            matrice[i][j + 1] = MUR;
                            matrice[i][j + 2] = MUR;
                            matrice[i + 1][j] = MUR;
                            matrice[i + 1][j + 1] = Bonus_L;
                            matrice[i + 1][j + 2] = PASSAGE;
                            matrice[i + 2][j] = MUR;
                            matrice[i + 2][j + 1] = PASSAGE;
                            matrice[i + 2][j + 2] = MUR;
                            Bonus_L = Bonus_L + 1;
                        }
                        break;
                }
                break;
        }
    }

    Afficher_Plateau_De_Jeu(matrice);

    int matrice_tuile_en_rab[3][3];
    int a; //la variable a permet de savoir quel tuile est en supplement
    Color(15, 0);
    printf("\n\n------------------------------------------------------------------\n\n");
    Color(9, 0);
    if (Nombre_Tuile_En_L == 9) {
        a = 0;
        premiere_matrice_en_plus(matrice, matrice_tuile_en_rab, &a);
    }
    if (Nombre_Tuile_En_I == 11) {
        a = 1;
        premiere_matrice_en_plus(matrice, matrice_tuile_en_rab, &a);
    }
    if (Nombre_Tuile_En_T == 5) {
        a = 2;
        premiere_matrice_en_plus(matrice, matrice_tuile_en_rab, &a);
    }
    if (Nombre_Tuile_En_L_Bonus == 5) {
        a = 3;
        premiere_matrice_en_plus(matrice, matrice_tuile_en_rab, &a);
    }
    printf("\n");
}

void Regle_du_jeu(){
    ClearScreen();
    int retour_au_menu=0;
    while(retour_au_menu==0){
        do {
            printf("Voici les regles du jeu\n\n ");

            Color(2, 0);
            printf("ENTREZ DANS LE LABIRYNTHE\n\n");
            printf("But du jeu :\n");
            Color(15, 0);
            printf("Vous penetrez dans un labyrinthe enchante a la\n");
            printf("recherche de fabuleux tresors et de mysterieuses\n");
            printf("creatures. Chacun de vous essaye de creer des\n");
            printf("chemins pour atteindre le tresor qui le convoite en faisant\n");
            printf("coulisser astucieusement les couloirs.\n");
            printf("Le joueur qui aura trouve tous ses tresors et rejoint sa\n");
            printf("case depart le premier sera declare vainqueur.\n\n");
            Color(2, 0);
            printf("COMMENT JOUER : \n\n");
            Color(3, 0);
            printf("1. Modification des couloirs\n\n");
            Color(15, 0);
            printf("Tout autour du plateau figurent 12 fleches. Elles\n""indiquent les endroits ou peut etre inseree la plaque\n""supplementaire.\n""Quand vient son tour, le joueur choisit une rangee et\n""y pousse la plaque supplementaire vers l interieur  du\n""plateau jusqu a ce que une et une seule plaque a oppose soit expulsee\n");
            Color(3, 0);
            printf("\n\n2. DEPLACEMENT DU PION\n\n");
            Color(15, 0);
            printf("Apres avoir modifie le labyrinthe, le joueur peut deplacer\n""son pion jusque a n importe quelle case en suivant un\n""couloir ininterrompu. Il peut se deplacer aussi loin que il\n""veut. Il est aussi permis de rester sur place.\n\n");
            Color(3, 0);
            printf("FIN DE LA PARTIE\n\n");
            Color(15, 0);
            printf("Le vainqueur est le premier joueur a avoir retourne toutes\n" "ses cartes et a ramener son pion a son point de depart.\n\n");
            Color(2, 0);
            printf("Il ne reste plus que a vous lancez dans ce labirynthe :)");

            printf("\n\nAppuyer sur 1 pour retourner au menu");
            scanf("%d", &retour_au_menu);
            ClearScreen();
        }while (retour_au_menu != 1);

    }
}

void Menu() {
    int Labirynthe = 0;
    while (Labirynthe==0) {
        Color(2, 0);
        printf("\n\n\n");
        printf("-----------------------------------------");
//ligne 1
        printf("\n\n");
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);

        //-----------------------------------ligne 2
        printf("\n");
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);


        //-----------------------------------ligne 3
        printf("\n");
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);

        //-----------------------------------ligne 4
        printf("\n");
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        printf("%c", 254);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);


        //-----------------------------------ligne 2
        printf("\n");
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(0, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        Color(2, 0);
        printf("%c", 254);
        printf("\n\n");
        printf("-----------------------------------------");

        printf("\n\n\n\n");


        Color(11, 0);
        do {
            printf("\n1. Jouer une nouvelle partie\n");
            printf("2. Afficher les regles\n");
            printf("3. Quitter\n");
            scanf("%d", &Labirynthe);
        }while(Labirynthe != 1 && Labirynthe != 2 && Labirynthe != 3);

        if (Labirynthe == 1) {
            int matrice[TAILLE][TAILLE];
            Remplir_les_cases_vides(matrice);
            initialisation_matrice(matrice);
            Initialisation_tuile_en_mouvement(matrice);
            system("pause");
        }
        if (Labirynthe == 2) {
            Regle_du_jeu();
            Labirynthe=0;
        }
        if (Labirynthe == 3){

        }
    }
}

int main() {
    srand(time(NULL));
    Menu();
    int matrice[TAILLE][TAILLE];
    Remplir_les_cases_vides(matrice);
    initialisation_matrice(matrice);
    Initialisation_tuile_en_mouvement(matrice);
    system("pause");
    Sleep(1000);
}