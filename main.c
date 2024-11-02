
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"

bool validInput(int c)
{
    if (c == 1 || c == 2 || c == 9)
        return true;
    return false;
}

int *readMenu(int *control)
{
    // while (scanf("%d", &control) != 1)
    // {
    //     printf("Hibas input, szamot adjon meg!\n");
    //     while (getchar() != '\n')
    //         ;
    // };
    // printf("%d", (scanf("%d", &control) != 1 && !validInput((int)control) == true ? 1 : 0));
    while (scanf("%d", &control) != 1)
    {

        printf("Szamot adjon meg!\n");
        printf("Valasszon a fenti menupontok kozul: ");
        while (getchar() != '\n')
            ;
    }
    return control;
}

int main()
{
    int *control = 0;

    printf("\n********************************");
    printf("\n* Eletjatek *");
    printf("\n* 1. Uj jatekter letrehozasa *");
    printf("\n* 2. Jatekallas betoltese *");
    printf("\n* 9. Kilepes *");
    printf("\n********************************\n\n");

    while (!validInput((int)control))
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        control = readMenu(control);
    }

    printf("%d", control);
    system("pause");
    return 0;
}