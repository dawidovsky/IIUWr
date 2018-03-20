//Dawid_Paluszak_Zadanie2
#include "head.h"
int main (int argc, char *argv[])
{
    if(argc>1)
    {
        FILE *f = fopen(argv[1],"r");
        lista *pierwszy;
        char *result,dane[101],nazwa[37];
        float x,y,z;
        result = fgets(dane,101,f);
        pierwszy = malloc(sizeof(lista));
        sscanf(dane,"%f %f %f %[A-Za-z0-9() ]s",&x,&y,&z,nazwa);
        pierwszy->numer=1;
        pierwszy->x=x;
        pierwszy->y=y;
        pierwszy->z=z;
        strcpy(pierwszy->nazwa,nazwa) ;
        pierwszy->next=NULL;
        while(result != NULL && strncmp(dane,"KONIEC",6) != 0)
        {
            result = fgets(dane,101,f);
            sscanf(dane,"%f %f %f %[A-Za-z0-9() ]s",&x,&y,&z,nazwa);
            dodaj(pierwszy,x,y,z,nazwa);
        }
        if(argc == 3)
        {
            if(strcmp(argv[2],"wypisz") == 0)
                WypiszCala(pierwszy);
        }
        if(argc > 3)
        {
            if(strcmp(argv[2],"punkt") == 0)
                WyswietlaniePkt(pierwszy,argv[3]);
            if(strcmp(argv[2],"wyzszy") == 0)
                Wysokosc(pierwszy,argv[3]);
            if(strcmp(argv[2],"szukaj") == 0)
                Szukaj(pierwszy,argv[3]);
        }
    }
}
