#include "create.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../menu/menu.h"
#include "../../debugmalloc.h"
#include <time.h>
#include <stdbool.h>

int mxSizeX;
int mxSizeY;
char **mx;

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
void MxTest(char **mx, int sizeX, int sizeY)
{
    for (int i = 1; i <= sizeX + 2; i++)
    {
        for (int j = 1; j <= sizeY + 2; j++)
        {
            if (i == 1 || j == 1 || i == sizeX + 2 || j == sizeY + 2)
                printf("*"); // A keret kirajzolása
            else
                printf("%c", mx[i - 1][j - 1]);
        }
        printf("\n");
    }
}

void FillMatrix() // TODO: serult kanari, ha nem megfelelo az input
{
    for (int i = 1; i <= mxSizeX; i++)
    {
        char *line = (char *)calloc(mxSizeY + 1, sizeof(char));
        if (line == NULL)
            printf("Nem sikerult lefoglalni a memoriat a jatekternek!\n");

        bool valid = true;
        do
        {
            valid = true;
            printf("Adja meg a %d. sorban az eletallapotokat (pl.: __X_ ) es %d oszlopbol alljon!: ", i, mxSizeY);
            // scanf("%s", line);
            int count = 0;

            if (strlen(line) != mxSizeY) // adott szamu Y oszlopbol all
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

        for (int j = 1; j <= mxSizeX + 1; j++)
        {
            mx[i][j] = toupper(line[j - 1]);
        }
        free(line);
    }
}

bool validMenu(int input)
{
    if (input == 1 || input == 2 || input == 9)
        return true;
    else
        return false;
}

int *readMenu(int *input)
{
    while (scanf("%d", &input) != 1)
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        while (getchar() != '\n')
            ;
    }
    return input;
}

void Creator()
{
    srand(time(NULL));
    Print();
    int *input = 0;
    while (!validMenu((intptr_t)input))
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        input = readMenu(input);
    }

    if ((intptr_t)input == 1 || (intptr_t)input == 2)
    {

        while (mxSizeX < 1 || mxSizeY < 1)
        {
            printf("Adja meg a jatekter meretet (pl.: 5x4): ");
            while (scanf("%dx%d", &mxSizeX, &mxSizeY) != 2)
            {
                printf("Nem megfelelo formatum! [MERET]x[MERET]: ");
                while (getchar() != '\n')
                    ;
            }
            mxSizeX < 1 ? printf("A sorok szama nem lehet egynel kisebb!\n") : printf("");
            mxSizeY < 1 ? printf("Az oszlopok szama nem lehet egynel kisebb!\n") : printf("");
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
    if ((intptr_t)input == 1)
    {
        FillMatrix();
    }
    // jatekter random generalasa
    if ((intptr_t)input == 2)
    {
        for (int i = 1; i <= mxSizeX; i++)
        {
            for (int j = 1; j <= mxSizeY; j++)
            {
                int r = rand() % 2;
                mx[i][j] = r == 0 ? '_' : 'X';
            }
        }
    }
    if ((intptr_t)input == 9)
    {
        // vissza a menube
        system("cls");
        showMenu();
    }
}