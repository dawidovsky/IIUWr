#include <stdio.h>
#include <string.h>
int main()
{
    char tablica1[6001],tablica2[6001];
    int ilosc_znakow=0,dlugosc,i;
    fgets(tablica1,6001,stdin);
    fgets(tablica2,6001,stdin);
    dlugosc=strlen(tablica1);
    while(dlugosc != 0)
    {
        for(i=0;i<dlugosc;i++)
        {
            if(tablica1[i]==tablica2[i])
            {
                ilosc_znakow++;
            }
        }
        if(dlugosc==ilosc_znakow)
        {
            tablica2[0]='\0';
            fgets(tablica2,6001,stdin);
        }
        else
        {
            for(i=0;i<dlugosc;i++)
            {
                if(tablica1[i]!='\n')
                {
                    putchar(tablica1[i]);
                    tablica1[i]='\0';
                }
            }
            for(i=0;tablica2[i-1]!='\n';i++)
                tablica1[i]=tablica2[i];
            putchar('\n');
            tablica2[0]='\0';
            fgets(tablica2,6001,stdin);
            dlugosc=strlen(tablica1);
        }
        ilosc_znakow=0;
    }
}
