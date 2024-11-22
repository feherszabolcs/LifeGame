#ifndef CREATE_H
#define CREATE_H
typedef struct Palya
{
    int mxSizeX;
    int mxSizeY;
    char **mx;
} Palya;
Palya Creator(Palya p);
void MxTest(Palya palya);

#endif