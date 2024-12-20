#include "menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "../creategrid/create.h"
#include "../../debugmalloc.h"
#include "../gridloader/gridloader.h"
#include "../simulation/simulation.h"

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
bool validInput(int c, bool end)
{
    if (end)
    {
        if (c == 1 || c == 9 || c == 8)
            return true;
    }
    else if (c == 1 || c == 2 || c == 9)
        return true;
    return false;
}

// a konzolról beolvasott adatot ellenőrzi, hogy szám-e.
// ha nem szám akkor a fgv újrakéri a felhasználótól a bemenetet.
// int pointerrel tér vissza, ami a beolvasott szám
int readMenu(int control)
{
    while (scanf("%d", &control) != 1)
    {

        printf("Valasszon a fenti menupontok kozul: ");
        while (getchar() != '\n')
            ;
    }
    return control;
}

void Quit() // Bezaras es kilepes
{
    printf("*****Kilepes!*****");
    sleep_ms(500);

    exit(0);
}
// A jatek vegen a matrix fajlba mentése vagy kilepo fgv
int EndGame(Palya p)
{
    Palya palya = p;
    int input;

    printf("\n********************************");
    printf("\n*         Jatek vege           *");
    printf("\n* 1. Jatekallas mentese fajlba *");
    printf("\n*      8. Vissza a menube      *");
    printf("\n*         9. Kilepes           *");
    printf("\n********************************\n\n");

    while (!validInput(input, true)) // true -> csak 1, 8 vagy 9-es számokat fogad el
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        input = readMenu(input);
    }

    if (input == 1) // mentes grid.txt fajlba
    {
        system("cls");
        int res = saveGrid(palya);
        if (res != 0) //-1-es visszateres - nem sikerult a mentes
            printf("\nNem sikerult a mentes!\n");
        else
        {
            printf("\nJatekallas mentese a [grid.txt] fajlba sikeresen.\nVisszateres a menube...\n\n");
            sleep_ms(1000);
        }
    }

    //
    for (int i = 0; i < palya.mxSizeX + 2; i++)
    {
        free(palya.mx[i]);
    }
    free(palya.mx);
    palya.mxSizeY = palya.mxSizeX = 0; // felszabaditas es alaphelyzet

    if (input == 9)
        Quit();
    system("cls");
    return input;
}

// A fuggveny felel a menupontok megjelenitesere, ez amit a főprogram is meghív
// Addig vár a usertől inputot, amíg az nem 1-es, 2-es vagy 9-es. A lehetséges válaszokat a validInput függvény vizsgálja.
void showMenu()
{
    Palya palya = {0, 0, NULL};
    int control = 0;

    while (true)
    {
        printf("\n********************************");
        printf("\n*         Eletjatek            *");
        printf("\n*  1. Uj jatekter letrehozasa  *");
        printf("\n*  2. Jatekallas betoltese     *");
        printf("\n*  9. Kilepes                  *");
        printf("\n********************************\n\n");
        while (!validInput(control, false)) // 2. param false, mert nem a jatek vege eseten vagyunk
        {
            printf("Valasszon a fenti menupontok kozul: ");
            control = readMenu(control);
        }
        switch (control)
        {
        case 1:
            palya = Creator(palya);
            break;
        case 2:
            palya = dialogopener(palya);
            break;
        case 9:
            printf("*****Kilepes!*****");
            sleep_ms(1000);
            exit(0);
            break;

        default:
            printf("Nincs ilyen menupont!\n");
            break;
        }
        if ((control == 2 || control == 1) && palya.mxSizeY != 0 && palya.mxSizeX != 0)
        {
            while (!kbhit())
            {
                Run(palya);
            }
            if (EndGame(palya) == 9)
                break;
        }
        if (control == 9)
            break;
        control = 0;
    }
}