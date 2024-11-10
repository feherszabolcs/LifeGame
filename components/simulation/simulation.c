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
            if (mx[x + i][y + j] == 'X')
                count++;
        }
    }
    return count;
}

void nexState()
{

    char **tmpMx = mx; // ideiglenes mx módosítása h a valtozasok csak az adott kör végén hajtódjanak végre valójában

    for (int i = 1; i < mxSizeX; i++)
    {
        for (int j = 1; j < mxSizeY; j++)
        {
            // szomszedok szamanak meghatarazosa
            int neighbours = getNeighboursCount(i, j);

            char cell = mx[i][j];
            // a sejt túléli a kört
            if (cell == 'X')
            {
                if (neighbours == 2 || neighbours == 3)
                    tmpMx[i][j] = 'X';
            } // uj sejt szuletik
            else if (neighbours == 3)
                tmpMx[i][j] = 'X';
            else
                tmpMx[i][j] = '_';
        }
    }
    mx = tmpMx;
}

void Run()
{
    system("cls");
    MxTest(mx, mxSizeX, mxSizeY);
    nexState();
    sleep_ms(1000);
}
