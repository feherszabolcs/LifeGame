
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "components/menu/menu.h"
#include "components/creategrid/create.h"

int main()
{
    showMenu();

    for (int i = 0; i < mxSizeX; i++)
    {
        free(mx[i]);
    }
    free(mx);

    system("pause");
    return 0;
}