#include "../creategrid/create.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"
#include "../menu/menu.h"

int getNeighboursCount(Palya palya, int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((j != 0 || i != 0) && palya.mx[x + i][y + j] == 'X')
                count++;
        }
    }
    return count;
}

void nexState(Palya palya)
{
    char **tmpMx = (char **)malloc(palya.mxSizeX * sizeof(char *));
    for (int i = 0; i < palya.mxSizeX; i++)
    {
        tmpMx[i] = (char *)malloc(palya.mxSizeY * sizeof(char));
        for (int j = 0; j < palya.mxSizeY; j++)
        {
            tmpMx[i][j] = palya.mx[i][j];
        }
    }
    for (int i = 1; i < palya.mxSizeX; i++)
    {
        for (int j = 1; j < palya.mxSizeY; j++)
        {
            // szomszedok szamanak meghatarazosa
            int neighbours = getNeighboursCount(palya, i, j);

            char cell = palya.mx[i][j];
            // a sejtes cellák (túléli vagy elpusztul)
            if (cell == 'X')
            {
                if (neighbours == 2 || neighbours == 3)
                    tmpMx[i][j] = 'X';
                if (neighbours < 2 || neighbours > 3)
                    tmpMx[i][j] = '_';
            } // uj sejt szuletik
            else if (cell == '_' && neighbours == 3)
                tmpMx[i][j] = 'X';
        }
    }
    for (int i = 0; i < palya.mxSizeX; i++)
    {
        for (int j = 0; j < palya.mxSizeY; j++)
        {
            palya.mx[i][j] = tmpMx[i][j];
        }
        free(tmpMx[i]);
    }
    free(tmpMx);
}

void Run(Palya palya)
{
    system("cls");
    MxTest(palya);
    nexState(palya);
    printf("\n\nA jatek befejezesehez nyomjon meg egy billentyut!\n");
    sleep_ms(1000);
}
