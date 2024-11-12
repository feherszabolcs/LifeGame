
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
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
static bool validInput(int c, bool end)
{
    if (end)
    {
        if (c == 1 || c == 9)
            return true;
    }
    else if (c == 1 || c == 2 || c == 9)
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

int saveGrid()
{
    FILE *file = fopen("grid.txt", "w");
    if (file == NULL)
    {
        return -1;
    }
    for (int i = 0; i <= mxSizeX + 1; i++)
    {
        for (int j = 0; j <= mxSizeY + 1; j++)
        {
            if (i == 0 || j == 0 || i == mxSizeX + 1 || j == mxSizeY + 1)
            {
                fprintf(file, "*"); // A keret kirajzolása
            }
            else
            {
                fprintf(file, "%c", mx[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}
// A jatek vegen a matrix fajlba mentése vagy kilepo fgv
void EndGame()
{
    int *input;

    printf("\n********************************");
    printf("\n*         Jatek vege           *");
    printf("\n* 1. Jatekallas mentese fajlba *");
    printf("\n*         9. Kilepes           *");
    printf("\n********************************\n\n");

    while (!validInput((intptr_t)input, true)) // true -> csak 1 vagy 9-es számokat fogad el
    {
        printf("Valasszon a fenti lehetosegek kozul: ");
        input = readMenu(input);
    }

    if ((intptr_t)input == 1) // mentes grid.txt fajlba
    {
        int res = saveGrid();
        if (res != 0) //-1-es visszateres - nem sikerult a mentes
            printf("\nNem sikerult a mentes!\n");
        else
            printf("\nJatekallas mentese fajlba sikeresen.");
    }

    printf("*****Kilepes!*****");
    sleep_ms(500);
    exit(0);
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

    while (!validInput((intptr_t)control, false)) // 2. param false, mert nem a jatek vege eseten vagyunk
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
        printf("Nincs ilyen menupont!\n");
        showMenu();
        break;
    }

    // kezdodik a jatek ---
    while (!kbhit())
    {
        Run();
    }
    EndGame();
}