/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 2 Implementacja z nowym ułamkiem
Program uruchamiamy z argumentami wywołania programu podając
dwa ułamki po spacji
w formie "liczba_całkowita/liczba_naturalna"
Język C - kompilator gcc 4.9.2*/

#include "zadanie2-zmianaUlamka.h"

int main(int argc,char** argv)
{
  Ul *ulamek1,*ulamek2,*temp;
  ulamek1 = malloc(sizeof(Ul));
  ulamek2 = malloc(sizeof(Ul));
  temp = malloc(sizeof(Ul));
  sscanf(argv[1],"%d/%d",&ulamek1->licznik,&ulamek1->mianownik);
  sscanf(argv[2],"%d/%d",&ulamek2->licznik,&ulamek2->mianownik);
  char wybor;
  printf("%s\n%s\n%s\n%s\n%s\n","1.Dodaj","2.Odejmij","3.Pomnoz","4.Dziel","5.Wyjscie");
  temp->licznik = ulamek2->licznik;
  temp->mianownik = ulamek2->mianownik;
  while(wybor=getchar()){
        if(ulamek1->mianownik == 0 || ulamek2->mianownik == 0)
        {
            printf("Nie dzielimy przez 0");
            break;
        }
    switch (wybor) {
      case '1':
        ulamek2 = dodawanie(ulamek1,ulamek2);
        Wypisz(ulamek2);
        break;
      case '2':
        ulamek2 = odejmowanie(ulamek1,ulamek2);
        Wypisz(ulamek2);
        break;
      case '3':
        ulamek2 = mnozenie(ulamek1,ulamek2);
        Wypisz(ulamek2);
        break;
      case '4':
        ulamek2 = dzielenie(ulamek1,ulamek2);
        Wypisz(ulamek2);
        break;
      case '5':free(ulamek1); free(ulamek2); exit(0);break;
    }
    ulamek2->licznik = temp->licznik;
    ulamek2->mianownik = temp->mianownik;
  }
}
