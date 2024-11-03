
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "../../debugmalloc.h"
#include "menu.h"

/**
 * Cross-platform sleep function for C
 * Code copied from rafaelglikis' github!!
 */
static void sleep_ms(int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000)
#endif
}

static bool validInput(int c)
{
    if (c == 1 || c == 2 || c == 9)
        return true;
    return false;
}

static int *readMenu(int *control)
{
    while (scanf("%d", &control) != 1)
    {

        printf("Szamot adjon meg!\n");
        printf("Valasszon a fenti menupontok kozul: ");
        while (getchar() != '\n')
            ;
    }
    return control;
}

void showMenu()
{
    int *control = 0;

    printf("\n********************************");
    printf("\n* Eletjatek *");
    printf("\n* 1. Uj jatekter letrehozasa *");
    printf("\n* 2. Jatekallas betoltese *");
    printf("\n* 9. Kilepes *");
    printf("\n********************************\n\n");

    while (!validInput((intptr_t)control))
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        control = readMenu(control);
    }

    switch ((intptr_t)control)
    {
    case 9:
        printf("*****Kilepes!*****");
        sleep_ms(1000);
        exit(0);
        break;

    default:
        printf("Nem jo a valasztas!");
        break;
    }

    system("pause");
}