//Dawid_Paluszak_Zadanie2
#include "head.h"
void dodaj(lista *pierwszy,float x,float y,float z,char nazwa[])
{
    lista *wsk=pierwszy,*nowy;
    while(wsk->next != NULL)
        wsk=wsk->next;
    int numer = wsk->numer;
    nowy=malloc(sizeof(lista));
    nowy->numer=++numer;
    nowy->x=x;
    nowy->y=y;
    nowy->z=z;
    strcpy(nowy->nazwa,nazwa);
    nowy->next=NULL;
    wsk->next=nowy;
}
void WypiszCala(lista *pierwszy)
{
    lista *wsk=pierwszy;
    while(wsk->next != NULL)
    {
        printf("%f %f %f %s\n",wsk->x,wsk->y,wsk->z,wsk->nazwa);
        wsk = wsk->next;
    }
}
void WyswietlaniePkt(lista *pierwszy, char numpkt[])
{
    int id = atoi(numpkt);
    lista *wsk=pierwszy;
    while(wsk->next != NULL && wsk->numer != id)
        wsk=wsk->next;
    if(wsk->next != NULL)
    {
        printf("%f %f %f %s\n",wsk->x,wsk->y,wsk->z,wsk->nazwa);
    }
}
void Wysokosc(lista *pierwszy,char liczba[])
{
    lista *wsk = pierwszy;
    int wys = atoi(liczba);
    while(wsk->next != NULL)
    {
        if(wsk->x > wys)
            printf("%f %f %f %s\n",wsk->x,wsk->y,wsk->z,wsk->nazwa);
        wsk=wsk->next;
    }
}
void Szukaj(lista *pierwszy,char napis[])
{
    lista *wsk = pierwszy;
    while(wsk->next != NULL)
    {
        if(strstr(wsk->nazwa,napis) != NULL)
            printf("%f %f %f %s\n",wsk->x,wsk->y,wsk->z,wsk->nazwa);
        wsk=wsk->next;
    }
}
