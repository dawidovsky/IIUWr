//Dawid Paluszak Zadanie1
#include <stdio.h>
void NumOutput(int baza, int x);
int NumInput(int baza);
int main()
{
    int baza=10,x,i;                // baza wejsciowa
    while(x != 0)
    {
        x = NumInput(baza);
        for(i=0;x>0;x=x/10)                     //odwracanie liczby uzyskanej przez NumInput
            i=i*10+(x%10);
        x = i;
        baza = 8;                   // baza wyjsciowa
        NumOutput(baza,x);
    }
}
int NumInput(int baza)
{
    int cyfra_int, liczba = 0, zmienna = 1;                         //cyfra_int - cyfra liczby podanej przedstawiona w int
    char cyfra_char = getchar(),znak = '+';                         //cyfra_char - cyfra liczby podanej przedstawiona w char
    while(cyfra_char != '.')
    {
        if(cyfra_char == '-')
            znak = '-';
        if(cyfra_char >= '0' && cyfra_char < baza + '0')
        {
            cyfra_int = cyfra_char - '0';                           //zamiana char na int i zapisanie cyfr jako jednej liczby
            liczba = liczba + (cyfra_int * zmienna);
            zmienna = zmienna * baza;
        }
        cyfra_char = getchar();
    }
    if(znak == '-')
        return liczba = liczba * -1;
    else
        return liczba;
}
void NumOutput(int baza, int x)
{

    int ilosc_cyfr = 0,i;
    char znak='+';
    if(x<0)
    {
         x *= -1;
         znak = '-';
    }
    int liczba_pocz = x;
    while(liczba_pocz>0)                                            //linijki od 46 do 58 zamieniaja liczbe na tablice char
    {                                                               //dziêki czemu jestem w stanie odwróciæ liczbê
        ilosc_cyfr++;                                               //by odpowiednio j¹ wypisaæ
        liczba_pocz = liczba_pocz / 10;
    }

    liczba_pocz = x;
    char tab[ilosc_cyfr];
    for(i=0;i<ilosc_cyfr;i++)
    {
        tab[i] = (liczba_pocz%10);
        liczba_pocz = liczba_pocz /10;
    }
    if(x != 0)
    {
        int liczba = ilosc_cyfr - 1;
        if(znak=='-')
                putchar('-');
        while(liczba >= 0)                                           //wypisanie liczby w formacie dziesiêtnym
        {
            putchar((tab[liczba] % 10)+'0');
            liczba--;
        }
        putchar('\n');
        if(znak=='-')
                putchar('-');
        while(x > 0)                                                //wypisanie liczby w formacie podanym jako baza
        {
            putchar((x % baza)+'0');
            x = x / baza;
        }
        putchar('.');
        putchar('\n');
    }
}
