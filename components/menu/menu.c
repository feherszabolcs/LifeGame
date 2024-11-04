
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
#include "../gridloader/gridloader.h"
#include "../creategrid/create.h"

/**
 * Linuxon és Windowson is működű sleep függvény - rafaelglikis' githubjáról merítve az implementációt!
 */
void sleep_ms(int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000)
#endif
}

// Csak a 1, 2, 9-es számokat fogadja el a függvény, ezek esetén lesz valid az input.
// a vizsgálandó számot paraméterként kapja meg.
static bool validInput(int c)
{
    if (c == 1 || c == 2 || c == 9)
        return true;
    return false;
}

// a konzolról beolvasott adatot ellenőrzi, hogy szám-e.
// ha nem szám akkor a fgv újrakéri a felhasználótól a bemenetet.
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

// A fuggveny felel a menupontok megjelenitesere, ez amit a főprogram is meghív
// Addig vár a usertől inputot, amíg az nem 1-es, 2-es vagy 9-es. A lehetséges válaszokat a validInput függvény vizsgálja.
void showMenu()
{
    int *control = 0;

    printf("\n********************************");
    printf("\n*         Eletjatek            *");
    printf("\n*  1. Uj jatekter letrehozasa  *");
    printf("\n*  2. Jatekallas betoltese     *");
    printf("\n*  9. Kilepes                  *");
    printf("\n********************************\n\n");

    while (!validInput((intptr_t)control))
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        control = readMenu(control);
    }

    switch ((intptr_t)control)
    {
    case 1:
        Creator();
        break;
    case 2:
        dialogopener();
        break;
    case 9:
        printf("*****Kilepes!*****");
        sleep_ms(1000);
        exit(0);
        break;

    default:
        printf("Nem jo a valasztas!");
        break;
    }
}