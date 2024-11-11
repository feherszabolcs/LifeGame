#include "create.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../menu/menu.h"
#include <time.h>

int mxSizeX;
int mxSizeY;
char **mx;

static void Print()
{
    system("cls");
    printf("\n********************************");
    printf("\n*     Jatekter letrehozas      *");
    printf("\n*     1 - Manualis bevitel     *");
    printf("\n*     2 - Veletlenszeru adatok *");
    printf("\n*     b - Vissza a menube      *");
    printf("\n********************************\n\n");
}

// matrix allapot kirajzolo fgv
void MxTest(char **mx, int sizeX, int sizeY)
{
    for (int i = 1; i <= sizeX + 2; i++)
    {
        for (int j = 1; j <= sizeY + 2; j++)
        {
            if (i == 1 || j == 1 || i == sizeX + 2 || j == sizeY + 2)
                printf("* "); // A keret kirajzolása
            else
                printf("%c ", mx[i - 1][j - 1]);
        }
        printf("\n");
    }
}

void FillMatrix()
{
    for (int i = 1; i <= mxSizeX; i++)
    {
        char *line = (char *)calloc(mxSizeY + 2, sizeof(char));
        if (line == NULL)
            printf("Nem sikerult lefoglalni a memoriat a jatekternek!\n");
        printf("Adja meg a %d. sorban az eletallapotokat (pl.: __X_ , ahol a _ karakter szokozt jelol) es %d oszlopbol alljon!: ", i, mxSizeY);
        scanf("%s", line);

        // VALOS INPUT ELLENORZES (tenyleg x és _)

        // printf("%s", line);
        for (int j = 1; j <= mxSizeX + 1; j++)
        {
            mx[i][j] = line[j - 1];
        }
    }
}

void Creator()
{
    srand(time(NULL));
    Print();
    char input;

    while (scanf("%c", &input) == 1)
    {
        if (input == '1' || input == '2')
        {
            printf("Adja meg a jatekter meretet (pl.: 5x4): ");
            while (scanf("%dx%d", &mxSizeX, &mxSizeY) != 2)
            {
                while (getchar() != '\n')
                    ;
            }
            printf("\n* A valasztott meret: %d x %d *\n", mxSizeX, mxSizeY);
            // jatekter lefoglalasa a memoriaban
            mx = (char **)calloc(mxSizeX + 2, sizeof(char *));
            for (int i = 0; i < mxSizeX + 2; i++)
                mx[i] = (char *)calloc(mxSizeY + 2, sizeof(char));
            sleep_ms(1000);
        }
        // user altal bevitt adatbol generalas
        if (input == '1')
        {
            FillMatrix();
            break;
        }
        // jatekter random generalasa
        if (input == '2')
        {
            for (int i = 1; i <= mxSizeX; i++)
            {
                for (int j = 1; j <= mxSizeY; j++)
                {
                    int r = rand() % 2;
                    mx[i][j] = r == 0 ? '_' : 'X';
                }
            }

            break;
        }
        if (input == 'b')
        {
            // vissza a menube
            system("cls");
            showMenu();
        }
    }
}