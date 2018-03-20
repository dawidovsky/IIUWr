//Dawid Paluszak Zadanie2
#include <stdio.h>
#include <stdlib.h>

void NumOutput(int x);
int NumInput();
int main()
{
    int x=1;
    while(x != 0)
    {
        x = NumInput();
        NumOutput(x);
    }
}
int NumInput()
{
    int liczba1 = 0, liczba2 = 0,wynik=0,i=0,liczba_znakow_w_tablicy=0;
    char cyfra_char = getchar(),znak = '+',tab[100],tab2[100]; // tablice przechowuj¹ kolejne cyfry liczb
    while(cyfra_char != '.')
    {
            if(cyfra_char != '\n')
            {
                tab[i]=cyfra_char; // przypisanie do tablicy cyfr liczby pierwszej zakonczonej kropka
                i++;
            }

            cyfra_char = getchar();
    }
    liczba_znakow_w_tablicy = i;
    for(i=liczba_znakow_w_tablicy;i>=1;i--)    // zamiana systemu szesnastkowego na dziesietny
    {               //if dla liczb z systemu szesnastkowego
        if(tab[i-1]=='A' || tab[i-1]=='B' || tab[i-1]=='C' || tab[i-1]=='D' || tab[i-1]=='E' || tab[i-1]=='F')
        {
            if(i!=1)            //jezeli jest to ostatnia cyfra to nie mnozymy jej przez baze
                liczba1 = liczba1 + (((tab[i-1]-'0')-7) * (16*(i-1)));
            else
                liczba1 = liczba1 + ((tab[i-1]-'0')-7);
        }
        else    // jezeli jest to system inny niz 16
        {
            if(i!=1)
                liczba1 = liczba1 + ( (tab[i-1]-'0') * (16*(i-1)));
            else
                liczba1 = liczba1 + (tab[i-1]-'0');
        }

    }
    i=0;
    znak = getchar(); // szczytanie znaku
    cyfra_char = getchar();
    if(znak != '!')    // jezeli jest to silnia to nie ma podanej drugiej liczby
    {
        while(cyfra_char != '.')   //analogicznie do liczby 1
        {
                tab2[i]=cyfra_char;
                i++;
                cyfra_char = getchar();
        }
        liczba_znakow_w_tablicy = i;
        for(i=liczba_znakow_w_tablicy;i>=1;i--)
            {
                if(tab2[i-1]=='A' || tab2[i-1]=='B' || tab2[i-1]=='C' || tab2[i-1]=='D' || tab2[i-1]=='E' || tab2[i-1]=='F')
                {
                    if(i!=1)
                        liczba2 = liczba2 + (((tab2[i-1]-'0')-7) * (16*(i-1)));
                    else
                        liczba2 = liczba2 + ((tab2[i-1]-'0')-7);
                }
                else
                {
                    if(i!=1)
                        liczba2 = liczba2 + ( (tab2[i-1]-'0') * (16*(i-1)));
                    else
                        liczba2 = liczba2 +  (tab2[i-1]-'0');
                }
            }
    }
    switch(znak)    // zaleznie od podanego znaku wykonuje sie rozne dzialanie
    {
        case    '+':wynik = liczba1 + liczba2;break;
        case    '-':wynik = liczba1 - liczba2;break;
        case    '*':wynik = liczba1 * liczba2;break;
        case    '/':wynik = liczba1 / liczba2;break;
        case    '!':wynik = 1;
                    for(int i=1;i<=liczba1;i++)    //obliczanie silni
                        wynik = wynik * i;break;
    }
    for(i=0;i<100;i++)  // zerowanie tablic
    {
        tab[i]=0;
        tab2[i]=0;
    }
    return wynik;
}
void NumOutput(int x)
{
    printf("%d\n",x);
}
