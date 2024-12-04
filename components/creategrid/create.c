#include "create.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../menu/menu.h"
#include "../../debugmalloc.h"
#include <time.h>
#include <stdbool.h>
#include "../../econio.h"

static void Print()
{
    system("cls");
    printf("\n********************************");
    printf("\n*       Jatekter letrehozas    *");
    printf("\n*     1 - Manualis bevitel     *");
    printf("\n*     2 - Veletlenszeru adatok *");
    printf("\n*     9 - Vissza a menube      *");
    printf("\n********************************\n\n");
}

// matrix allapot kirajzolo fgv
void MxTest(Palya palya)
{
    for (int i = 0; i < palya.mxSizeX + 2; i++)
    {
        for (int j = 0; j < palya.mxSizeY + 2; j++)
        {
            if (i == 0 || j == 0 || i == palya.mxSizeX + 1 || j == palya.mxSizeY + 1)
            {
                econio_textcolor(COL_RED);
                printf("* "); // A keret kirajzolása
                econio_textcolor(COL_WHITE);
            }
            else
            {
                if (palya.mx[i][j] == '_')
                {
                    printf("  ");
                }
                if (palya.mx[i][j] == 'X')
                {
                    econio_textcolor(COL_GREEN);
                    printf("%c ", palya.mx[i][j]);
                    econio_textcolor(COL_WHITE);
                }
            }
        }
        printf("\n");
    }
}

Palya FillMatrix(Palya p)
{
    Palya palya = p;
    for (int i = 1; i <= palya.mxSizeX; i++)
    {
        char line[60];

        bool valid = true;
        do
        {
            valid = true;
            printf("Adja meg a %d. sorban az eletallapotokat (pl.: __X_ ) es %d oszlopbol alljon!: ", i, palya.mxSizeY);
            scanf("%s", line);
            if (strlen(line) != palya.mxSizeY) // adott szamu Y oszlopbol all
            {
                printf("Nem megfelelo formatum!\n");
                valid = false;
            }
            else
            {
                for (int i = 0; line[i] != '\0'; i++)
                {
                    if (toupper(line[i]) != 'X' && line[i] != '_') // csak X és _ van benne
                    {
                        printf("Nem megfelelo formatum!\n");
                        valid = false;
                        break;
                    }
                }
            }
        } while (valid == false);

        for (int j = 1; j <= palya.mxSizeX + 1; j++)
        {
            palya.mx[i][j] = toupper(line[j - 1]);
        }
    }
    return palya;
}

Palya Creator(Palya p)
{
    Palya palya = p;
    srand(time(NULL));
    Print();
    int input = 0;
    while (!validInput(input, false)) // 1, 2 ,9
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        input = readMenu(input);
    }

    if (input == 1 || input == 2)
    {

        while (palya.mxSizeX < 1 || palya.mxSizeY < 1)
        {
            printf("Adja meg a jatekter meretet (pl.: 5x4): ");
            while (scanf("%dx%d", &palya.mxSizeX, &palya.mxSizeY) != 2)
            {
                printf("Nem megfelelo formatum! [MERET]x[MERET]: ");
                while (getchar() != '\n')
                    ;
            }
            palya.mxSizeX < 1 ? printf("A sorok szama nem lehet egynel kisebb!\n") : printf("");
            palya.mxSizeY < 1 ? printf("Az oszlopok szama nem lehet egynel kisebb!\n") : printf("");
            while (getchar() != '\n')
                ;
        }

        printf("\n* A valasztott meret: %d x %d *\n", palya.mxSizeX, palya.mxSizeY);
        // jatekter lefoglalasa a memoriaban
        palya.mx = (char **)calloc(palya.mxSizeX + 2, sizeof(char *));
        for (int i = 0; i < palya.mxSizeX + 2; i++)
            palya.mx[i] = (char *)calloc(palya.mxSizeY + 2, sizeof(char));
        sleep_ms(1000);
    }
    // user altal bevitt adatbol generalas
    if (input == 1)
    {
        palya = FillMatrix(palya);
    }
    // jatekter random generalasa
    if (input == 2)
    {
        for (int i = 1; i <= palya.mxSizeX; i++)
        {
            for (int j = 1; j <= palya.mxSizeY; j++)
            {
                int r = rand() % 2;
                palya.mx[i][j] = r == 0 ? '_' : 'X';
            }
        }
    }
    if (input == 9)
    {
        // vissza a menube
        system("cls");
        return palya;
    }
    return palya;
}