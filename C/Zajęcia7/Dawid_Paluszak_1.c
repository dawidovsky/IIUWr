//Dawid_Paluszak_Zadanie1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct PtList{
    float x;
    float y;
    float z;
    char nazwa[37];
    struct PtList *next;
} lista;
void dodaj(lista *pierwszy,float x,float y,float z,char nazwa[])
{
    lista *wsk=pierwszy,*nowy;
    while(wsk->next != NULL)
        wsk=wsk->next;
    nowy=malloc(sizeof(lista));
    nowy->x=x;
    nowy->y=y;
    nowy->z=z;
    strcpy(nowy->nazwa,nazwa);
    nowy->next=NULL;
    wsk->next=nowy;
}
int sprawdzIlosc(lista *pierwszy)
{
    lista *wsk=pierwszy;
    int licznik=0;
    while(wsk->next != NULL)
    {
        licznik++;
        wsk=wsk->next;
    }

    return licznik;
}
void WypiszPieIOst(lista *pierwszy)
{
    lista *wsk=pierwszy;
    printf("%f %f %f %s\n",pierwszy->x,pierwszy->y,pierwszy->z,pierwszy->nazwa);
    while(wsk->next != NULL)
        wsk=wsk->next;
    printf("%f %f %f %s\n",wsk->x,wsk->y,wsk->z,wsk->nazwa);
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
int main ()
{
    lista *pierwszy;
    char *result,dane[101],nazwa[37],odp[40];
    float x,y,z;
    result = fgets(dane,101,stdin);
    pierwszy = malloc(sizeof(lista));
    sscanf(dane,"%f %f %f %[A-Za-z0-9() ]s",&x,&y,&z,nazwa);
    pierwszy->x=x;
    pierwszy->y=y;
    pierwszy->z=z;
    strcpy(pierwszy->nazwa,nazwa) ;
    pierwszy->next=NULL;
    while(result != NULL && strncmp(dane,"KONIEC",6) != 0)
    {
        result = fgets(dane,101,stdin);
        sscanf(dane,"%f %f %f %[A-Za-z0-9() ]s",&x,&y,&z,nazwa);
        dodaj(pierwszy,x,y,z,nazwa);
    }
    int ilosc = sprawdzIlosc(pierwszy);
    printf("Ilosc: %d\n",ilosc);
    WypiszPieIOst(pierwszy);
    printf("Czy wypisac cala liste?(tak/nie)\n");
    scanf("%s",odp);
    if(strcmp(odp,"tak") == 0)
    {
        WypiszCala(pierwszy);
    }
}
