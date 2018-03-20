//Dawid_Paluszak_Zadanie2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct PtList{
    int numer;
    float x;
    float y;
    float z;
    char nazwa[37];
    struct PtList *next;
}lista;
void WypiszCala(lista *pierwszy);
void dodaj(lista *pierwszy,float x,float y,float z,char nazwa[]);
void WyswietlaniePkt(lista *pierwszy,char numpkt[]);
void Wysokosc(lista *pierwszy,char liczba[]);
void Szukaj(lista *pierwszy,char napis[]);
