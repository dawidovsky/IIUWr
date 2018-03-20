#include <stdio.h>
int main()
{
    int liczba, suma = 0, cyfra, wykladnik, ilosc_cyfr=1, zliczacz_cyfr, liczba_pocz;
    scanf("%d",&liczba);
    zliczacz_cyfr = liczba;
    liczba_pocz = liczba;
    while( (zliczacz_cyfr = zliczacz_cyfr/10) != 0 )
        ilosc_cyfr++;
    for(int i = 0;i < ilosc_cyfr;i++)
        {
            cyfra = liczba%10;
            wykladnik = cyfra;
            for(int j = 1;j < ilosc_cyfr;j++)
            {
                if(cyfra != 1 )
                    cyfra = cyfra * wykladnik;
                else
                    cyfra = 1;
            }
            suma = suma + cyfra;
            liczba = liczba/10;
        }
    if(suma==liczba_pocz) printf("TAK\n");
    else printf("NIE\n");
}
