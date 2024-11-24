#include "../creategrid/create.h"
#include "gridloader.h"
#include "../menu/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../debugmalloc.h"
#include "../menu/menu.h"

typedef struct FileSize
{
    int rows;
    int cols;
} FileSize;

static FileSize getSize(char filename[])
{
    FileSize fs = {1, 0};

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fs.cols = fs.cols = -1;
        return fs;
    }

    char c;
    for (fs.cols = 0; getc(fp) != '\n'; fs.cols++)
        ;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
        if (c == '\n')
            fs.rows++;

    fclose(fp);
    return fs;
}

int saveGrid(Palya p)
{
    Palya palya = p;
    FILE *file = fopen("grid.txt", "w");
    if (file == NULL)
    {
        return -1;
    }
    for (int i = 0; i <= palya.mxSizeX + 1; i++)
    {
        for (int j = 0; j <= palya.mxSizeY + 1; j++)
        {
            if (i == 0 || j == 0 || i == palya.mxSizeX + 1 || j == palya.mxSizeY + 1)
            {
                fprintf(file, "*"); // A keret kirajzolása
            }
            else
            {
                fprintf(file, "%c", palya.mx[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

Palya dialogopener(Palya p)
{
    Palya palya = p;
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

    int input = 0;

    while (input != 1 && input != 8)
    {
        input = readMenu(input);
    }

    if (input == 1)
    {
        char filename[100];
        FILE *file;
        while (true)
        {
            printf("\nAdja meg a fajl nevet [grid.txt]: ");
            scanf("%s", filename);

            file = fopen(filename, "r");

            if (file == NULL)
            {
                printf("\nNem sikerult megnyitni a fajlt!\n");
                sleep_ms(500);
            }
            else
                break;
        }

        FileSize fs = getSize(filename);
        palya.mxSizeX = fs.rows - 2; // keretek levonasa
        palya.mxSizeY = fs.cols - 2;

        if (palya.mxSizeX == -1 || palya.mxSizeY == -1)
        {
            printf("Hiba tortent: Nem sikerült beállítani a sor és/vagy oszlopszámot!\n");
        }

        palya.mx = (char **)calloc(palya.mxSizeX + 2, sizeof(char *));
        for (int i = 0; i < palya.mxSizeX + 2; i++)
            palya.mx[i] = (char *)calloc(palya.mxSizeY + 3, sizeof(char));

        for (int i = 0; i < palya.mxSizeX + 2; i++)
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
        MxTest(palya);
        fclose(file);
    }

    if (input == 8)
    {
        system("cls");
        return palya;
    }
    return palya;
}