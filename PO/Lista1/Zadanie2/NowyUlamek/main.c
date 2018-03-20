/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 2 Implementacja z nowym ułamkiem
Program uruchamiamy z argumentami wywołania programu podając
dwa ułamki po spacji
w formie "liczba_całkowita/liczba_naturalna"
Język C - kompilator gcc 4.9.2*/

#include "zadanie2-nowyUlamek.h"

int main(int argc,char** argv)
{
  Ul *ulamek1,*ulamek2,*ulamek3;
  ulamek1 = malloc(sizeof(Ul));
  ulamek2 = malloc(sizeof(Ul));
  sscanf(argv[1],"%d/%d",&ulamek1->licznik,&ulamek1->mianownik);
  sscanf(argv[2],"%d/%d",&ulamek2->licznik,&ulamek2->mianownik);
  char wybor;
  printf("%s\n%s\n%s\n%s\n%s\n","1.Dodaj","2.Odejmij","3.Pomnoz","4.Dziel","5.Wyjscie");
  while(wybor=getchar()){
      if(ulamek1->mianownik == 0 || ulamek2->mianownik == 0)
        {
            printf("Nie dzielimy przez 0");
            break;
        }
    switch (wybor) {
      case '1':
        ulamek3 = dodawanie(ulamek1,ulamek2);
        Wypisz(ulamek3);
        break;
      case '2':
        ulamek3 = odejmowanie(ulamek1,ulamek2);
        Wypisz(ulamek3);
        break;
      case '3':
        ulamek3 = mnozenie(ulamek1,ulamek2);
        Wypisz(ulamek3);
        break;
      case '4':
        ulamek3 = dzielenie(ulamek1,ulamek2);
        Wypisz(ulamek3);
        break;
      case '5':free(ulamek1); free(ulamek2); exit(0);break;
    }
    free(ulamek3);
  }
}
