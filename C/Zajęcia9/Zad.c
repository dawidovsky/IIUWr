//Dawid Paluszak Zadanie 1 Lista 9

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_PI 3.14159265358979323846

typedef struct PtList{
    int size;
    float x;
    float y;
    float z;
    struct PtList *next;
}lista;

void DodaniePierwszegoDoListy(float x,float y,float z,lista *pierwszy)
{
    pierwszy->x=x;
    pierwszy->y=y;
    pierwszy->z=z;
    pierwszy->size = 1;
    pierwszy->next = NULL;
}

void DodawanieDoListy(float x,float y,float z,lista *pierwszy)
{
    lista *wsk=pierwszy,*nowy;
    (pierwszy->size)++;
    while(wsk->next != NULL)
        wsk=wsk->next;
    nowy=malloc(sizeof(lista));
    nowy->x=x;
    nowy->y=y;
    nowy->z=z;
    nowy->next=NULL;
    wsk->next=nowy;
}

void Zczytanie(char linia[],lista *pierwszy)
{
    char liczba1[13],liczba2[13];
    int dlugosc=strlen(linia),j=0;
    for(int i=1;i<dlugosc;i++)
    {
        if(linia[i] == 't' && linia[i-1] == 'p' && linia[i-2] == 'k' && linia[i-3] == 'r' && linia[i-4] == 't' && linia[i-5] != '/')
           {
               while(linia[i] != '"')
                        i++;
                if(linia[i]=='"')
                {
                    i++;
                    while(linia[i] != '"')
                    {
                        liczba1[j]=linia[i];
                        j++;
                        i++;
                    }
                    j=0;
                    i++;
                    while(linia[i] != '"')
                        i++;
                    i++;
                    while(linia[i] != '"')
                    {
                        liczba2[j]=linia[i];
                        j++;
                        i++;
                    }
                }
                float szer_geo = atof(liczba1);
                float dlu_geo = atof(liczba2);
                printf("%f %f\n",dlu_geo,szer_geo);
                szer_geo = M_PI * szer_geo / 180;
                dlu_geo = M_PI * dlu_geo / 180;
                int r=6378;
                float x = r*cos(szer_geo)*cos(dlu_geo);
                float y = r*cos(szer_geo)*sin(dlu_geo);
                float z = r*sin(szer_geo);
                if(pierwszy->size == 0)
                    DodaniePierwszegoDoListy(x,y,z,pierwszy);
                else
                DodawanieDoListy(x,y,z,pierwszy);
           }
    }
}

float LiczenieTrasy(lista *pierwszy)
{
    float suma = 0.0;
    lista *wsk = pierwszy,*drugi = pierwszy->next;
    while(drugi != NULL)
    {
        float ax = (drugi->x) - (wsk->x);
        float ay = (drugi->y) - (wsk->y);
        float az = (drugi->z) - (wsk->z);
        float wynik = (ax*ax) + (ay*ay) + (az*az);
        suma += sqrt(wynik);
        wsk = drugi;
        drugi = drugi -> next;
    }
    return suma;
}

int Przeciecia(lista *pierwszy)
{
    lista *pocz_1 = pierwszy,*kon_1 = pierwszy->next;
    lista *pocz_2 = kon_1->next, *kon_2 = pocz_2->next;
    float a1,b1,a2,b2;
    float x,y;
    int suma=0;
    for(int i=4 ;i<pierwszy->size;i++)
    {
        a1 = (kon_1->y - pocz_1->y)/(kon_1->x - pocz_1->x);
        b1 = (pocz_1->y) - (a1 * pocz_1->x);
        do
        {
            a2 = (kon_2->y - pocz_2->y)/(kon_2->x - pocz_2->x);
            b2 = pocz_2->y - (a2 * pocz_2->x);
            x = (-b1+b2)/(a1-a2);
            y = a1*x + b1;
            if((a1*x - y + b1) == 0 && (a2*x - y +b2) == 0)
                    suma++;
            pocz_2 = pocz_2->next;
            kon_2 = kon_2->next;
        }while(kon_2->next != NULL);
        if(kon_1->next != NULL)
        {
            pocz_1 = pocz_1->next;
            kon_1 = kon_1->next;
            pocz_2 = kon_1->next;
            kon_2 = pocz_2->next;
        }
    }
    return suma;
}

int main(int argc,char **argv)
{
    if(argc>1)
    {
        lista *pierwszy;
        char linia[201];
        int ilosc_wierszy=0;
        pierwszy=malloc(sizeof(lista));
        pierwszy->size = 0;
        FILE *f = fopen(argv[1],"r");
        while(!feof(f))
        {
            fgets(linia,201,f);
            ilosc_wierszy++;
            Zczytanie(linia,pierwszy);
        }
        float trasa = LiczenieTrasy(pierwszy);
        int ilosc_przeciec = Przeciecia(pierwszy);
        fpos_t dlugosc;
        fgetpos (f, &dlugosc);
        printf ("Rozmiar pliku: %d\n",dlugosc);
        printf("Ilosc wierszy: %d\n",ilosc_wierszy);
        printf("Ilosc wspolrzednych: %d\n",pierwszy->size);
        printf("Dlugosc trasy: %f\n",trasa);
        printf("Ilosc samoprzeciec: %d",ilosc_przeciec);
    }
}
