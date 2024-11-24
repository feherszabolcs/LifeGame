#ifndef MENU_H
#define MENU_H
#include <stdbool.h>

void showMenu();
void sleep_ms(int milliseconds);
int readMenu(int control);
bool validInput(int c, bool end);
#endif