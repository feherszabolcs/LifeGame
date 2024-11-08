#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include "../debugmalloc.h"
#include "../creategrid/create.h"

void nexState()
{
    for (int i = 1; i < mxSizeX; i++)
    {
        for (int j = 1; j < mxSizeY; j++)
        {
            int neighbours = getNeighboursCount(i, j);
        }
    }
}

int getNeighboursCount(int x, int y)
{
    // elso sor eseten
    if (x == 0)

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                /* code */
            }
        }
}