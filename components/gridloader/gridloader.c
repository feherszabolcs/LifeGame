#include "gridloader.h"
#include "../menu/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../debugmalloc.h"
#include "../creategrid/create.h"
#include "../menu/menu.h"

static int getRows()
{
    int rows = 0;
    FILE *fp = fopen("grid.txt", "r");
    if (fp == NULL)
        return -1;
    char buffer[1000] = {'\0'};
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        rows++;
    }
    return rows - 2; // = MxSizeX
}
static int getCols()
{
    int cols = 0;
    FILE *fp = fopen("grid.txt", "r");
    if (fp == NULL)
        return -1;
    char buffer[1000] = {'\0'};
    while (fgets(buffer, sizeof(buffer), fp) != NULL) // Kod otlete: stackoverflow
    {
        cols = strlen(buffer) - 1;
    }
    return cols - 2; // = MxSizeY
}

void dialogopener()
{
    palya.mxSizeY = palya.mxSizeX = 0;

    system("cls");
    printf("\n*********************************");
    printf("\n* A txt megnyitasahoz a fajlnak *");
    printf("\n* a program konyvtaraban kell   *");
    printf("\n*          lennie!!             *");
    printf("\n*********************************");

    printf("\n*********************************");
    printf("\n*           TALLOZAS            *");
    printf("\n*     1 - Fajlnev megadasa      *");
    printf("\n*         8 - Vissza            *");
    printf("\n*********************************\n");

    int *input = 0;

    while ((intptr_t)input != 1 && (intptr_t)input != 8)
    {
        input = readMenu(input);
    }

    if ((intptr_t)input == 1)
    {
        char filename[100];
        printf("\nAdja meg a fajl nevet [grid.txt]: ");
        scanf("%s", filename);

        FILE *file;
        file = fopen(filename, "r");

        if (file == NULL)
        {
            printf("\nNem sikerult megnyitni a fajlt!\n");
            sleep_ms(500);
            dialogopener();
            return;
        }

        palya.mxSizeX = getRows(); // sorok es oszlopok beállítása a fájl alapján
        palya.mxSizeY = getCols();

        if (palya.mxSizeX == -1 || palya.mxSizeY == -1)
        {
            printf("Hiba tortent: Nem sikerült beállítani a sor és/vagy oszlopszámot!\n");
            return;
        }

        palya.mx = (char **)calloc(palya.mxSizeX + 2, sizeof(char *));
        for (int i = 0; i < palya.mxSizeX + 2; i++)
            palya.mx[i] = (char *)calloc(palya.mxSizeY + 3, sizeof(char));

        for (int i = 0; i < palya.mxSizeX + 3; i++)
        {
            for (int j = 0; j < palya.mxSizeY + 3; j++)
            {
                if (fscanf(file, "%c", &palya.mx[i][j]) != 1)
                {
                    fprintf(stderr, "hibas input: mx[%d][%d]\n", i, j);
                }
            }
        }

        printf("\nA fajl sikeresen betoltotta a jatekteret!\n");
        MxTest();
        fclose(file);
    }

    if ((intptr_t)input == 8)
    {
        system("cls");
        showMenu();
        return;
    }
}