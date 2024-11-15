#ifndef CREATE_H
#define CREATE_H

void Creator();
void MxTest(char **mx, int sizeX, int sizeY);
typedef struct Palya
{
    int mxSizeX;
    int mxSizeY;
    char **mx;
} Palya;
Palya palya;
extern int mxSizeX;
extern int mxSizeY;
extern char **mx;

#endif