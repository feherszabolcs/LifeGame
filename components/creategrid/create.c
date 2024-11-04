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

void Creator()
{

    Print();
    int mxSize;
    char input;

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
            printf("\n* A valasztott meret: %d x %d *", mxSize, mxSize);
            break;
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