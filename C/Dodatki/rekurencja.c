//Dawid Paluszak Zadanie 4
#include <stdio.h>
void rekurencja(char* tab, int indeks)  //funkcja void bo nie zwraca niczego, tylko drukuje
{
   printf("%c",tab[indeks]); //wyswietlamy znak
   if(indeks>0) rekurencja(tab,indeks-1); //  funkkcja wywo³uje sam¹ siebie,, tylko z indeksem o jeden mniejszym
}
int main()
{

   char tab[] = "23"; //tworzymy tablice
   rekurencja(tab, sizeof(tab)); //wywolujemy funkcje rekurencja
}
