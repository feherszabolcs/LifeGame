#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"
#include "../creategrid/create.h"
#include "../menu/menu.h"

int getNeighboursCount(int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (palya.mx[x + i][y + j] == 'X')
                count++;
        }
    }
    return count;
}

void nexState()
{

    char **tmpMx = palya.mx; // ideiglenes mx módosítása h a valtozasok csak az adott kör végén hajtódjanak végre valójában

    for (int i = 1; i < palya.mxSizeX; i++)
    {
        for (int j = 1; j < palya.mxSizeY; j++)
        {
            // szomszedok szamanak meghatarazosa
            int neighbours = getNeighboursCount(i, j);

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
    palya.mx = tmpMx;
}

void Run()
{
    system("cls");
    MxTest();
    nexState();
    printf("\n\nA jatek befejezesehez nyomjon meg egy billentyut!\n");
    sleep_ms(1000);
}
