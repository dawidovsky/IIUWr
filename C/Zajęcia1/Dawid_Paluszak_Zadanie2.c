// Dawid Paluszak zadanie 2
#include <stdio.h>
int cyfra(int liczba,int ilosc_cyfr)   // funkcja do wypisywania cyfr z zadania 1
{
    int suma = 0;
    for(int i=0;i<ilosc_cyfr;i++)
        {
            suma = liczba % 10;
        }
    return suma;
}
int zliczacz_cyfr(int liczba)          // funckja która zlicza cyfry w liczbie
{
    int ilosc_cyfr = 0;
    while(liczba >= 1)                 //inkrementuje zmienna ilosc cyfr i zmniejszam liczbe o jedna cyfre
    {
        ilosc_cyfr++;
        liczba = liczba / 10;
    }
    return ilosc_cyfr;
}
int palindrom(int liczba, int ilosc_cyfr)                               //ca³¹ funkcja palindrom oparta jest o zadanie 1,
{                                                                       //ale zamiast wypisywaæ kolejne cyfry
    int nowa_liczba = 0,suma = 0,liczba_pocz = liczba,zmienna = 1;      //tworzy liczbe ktora jest odwrotna.
    for(int i=2;i<=ilosc_cyfr;i++)                                      //Ulatwia to pozniejsze porownanie liczby
        zmienna = zmienna * 10;                                         //poczatkowej z nowa powstala.
    for(int i=1;i<=ilosc_cyfr;i++)
    {
        suma = (liczba % 10)* zmienna;
        liczba = liczba / 10;
        nowa_liczba = nowa_liczba + suma;
        zmienna = zmienna / 10;
    }
    if(liczba_pocz == nowa_liczba)                                      //porownuje liczbe poczatkowa z nowa.
        return 1;
    else
        return 0;
}
int main()
{
    int liczba = 1, ilosc_cyfr,wynik;
    scanf("%d",&liczba);
    ilosc_cyfr = zliczacz_cyfr(liczba);
    wynik = palindrom(liczba,ilosc_cyfr);
    while(liczba != 0 && ilosc_cyfr != 0)
    {
        for(int i=0;i<ilosc_cyfr;i++)
        {
            printf("%d",cyfra(liczba,ilosc_cyfr));
            liczba = liczba /10;
        }
    }
    if(wynik == 1)
        printf("\nLiczba jest palindromem");            //nie pamietam dokladnie tresci dlatego wypisuje dokladnie
    else                                                //czy liczba jest palindromem czy tez nim nie jest
        printf("\nLiczba nie jest palindromem");
}
