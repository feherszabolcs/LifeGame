#include "create.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../menu/menu.h"

static void Print()
{
    system("cls");
    printf("\n********************************");
    printf("\n*     Jatekter letrehozas      *");
    printf("\n*     1 - Tovabb               *");
    printf("\n*     b - Vissza a menube      *");
    printf("\n********************************\n\n");
}

// matrix allapot kirajzolo fgv
void MxTest(char **mx, int size)
{
    for (int i = 0; i <= size + 1; i++)
    {
        for (int j = 0; j <= size + 1; j++)
        {
            if (i == 0 || j == 0 || i == size + 1 || j == size + 1)
                printf("*");
            else
                printf("%c", mx[i - 1][j - 1]);
        }
        printf("\n");
    }
}

void Creator()
{

    Print();
    int mxSize;
    char input;
    char **mx;

    while (scanf("%c", &input) == 1)
    {
        if (input == '1')
        {
            printf("Adja meg a jatekter meretet (pl.: 5x5 eseten = 5): ");
            while (scanf("%d", &mxSize) != 1)
            {
                while (getchar() != '\n')
                    ;
            }
            printf("\n* A valasztott meret: %d x %d *\n", mxSize, mxSize);

            // jatekter lefoglalasa a memoriaban
            mx = (char **)calloc(mxSize, sizeof(char *));
            for (int i = 0; i < mxSize; i++)
                mx[i] = (char *)calloc(mxSize, sizeof(char));
            sleep_ms(1000);

            for (int i = 1; i <= mxSize; i++)
            {
                char *line = (char *)calloc(mxSize + 1, sizeof(char));
                if (line == NULL)
                    printf("Nem sikerult lefoglalni a memoriat a jatekternek!\n");
                printf("Adja meg a %d. sorban az eletallapotokat (pl.: __X_ , ahol a _ karakter szokozt jelol) es %d oszlopbol alljon!: ", i, mxSize);
                scanf("%s", line);
                // printf("%s", line);
                for (int j = 0; j < mxSize; j++)
                {
                    mx[i - 1][j] = line[j];
                }
            }

            MxTest(mx, mxSize);
            break;
            // jatekter feltoltese TODO

            // jatek kezdete ----
        }
        if (input == 'b')
        {
            // vissza a menube
            system("cls");
            showMenu();
        }
    }
}