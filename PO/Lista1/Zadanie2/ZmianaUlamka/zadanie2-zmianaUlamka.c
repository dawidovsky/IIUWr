/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 2 Implementacja ze zmianą ułamka
Program uruchamiamy z argumentami wywołania programu podając
dwa ułamki po spacji
w formie "liczba_całkowita/liczba_naturalna"
Język C - kompilator gcc 4.9.2*/

#include "zadanie2-zmianaUlamka.h"

Ul *Skracanie(Ul *ulamek)
{
  for(int i=2; i<=ulamek->mianownik;i++)
  {
    while(ulamek->licznik%i == 0 && ulamek->mianownik%i == 0)
    {
      ulamek->licznik/=i;
      ulamek->mianownik/=i;
    }
  }
  return ulamek;
}

Ul *Rozszerzenie(struct Ulamki ul1,struct Ulamki ul2, char znak)
{
  Ul *ul3 = malloc(sizeof(Ul));
  int ul1mia = ul1.mianownik;
  int ul2mia = ul2.mianownik;
  ul1.licznik *= ul2mia;
  ul1.mianownik *= ul2mia;
  ul2.licznik *= ul1mia;
  ul2.mianownik *= ul1mia;
  switch (znak) {
    case '+':
      ul3->licznik = ul1.licznik + ul2.licznik;
      ul3->mianownik = ul1.mianownik;
      break;
    case '-':
      ul3->licznik = ul1.licznik - ul2.licznik;
      ul3->mianownik = ul1.mianownik;
      break;
  }
  return ul3;
}

Ul *dodawanie(Ul *ul1,Ul *ul2)
{
  printf("%d/%d + %d/%d =",ul1->licznik,ul1->mianownik,ul2->licznik,ul2->mianownik);
  if(ul1->mianownik == ul2->mianownik)
    ul2->licznik = ul1->licznik + ul2->licznik;
  else
      ul2 = Rozszerzenie(*ul1,*ul2,'+');
  ul2 = Skracanie(ul2);
  return ul2;
}

Ul *odejmowanie(Ul *ul1,Ul *ul2)
{
  printf("%d/%d - %d/%d =",ul1->licznik,ul1->mianownik,ul2->licznik,ul2->mianownik);
  if(ul1->mianownik == ul2->mianownik)
    ul2->licznik = ul1->licznik - ul2->licznik;
  else
    ul2 = Rozszerzenie(*ul1,*ul2,'-');
  ul2 = Skracanie(ul2);
  return ul2;
}

Ul *mnozenie(Ul *ul1, Ul *ul2)
{
  printf("%d/%d * %d/%d =",ul1->licznik,ul1->mianownik,ul2->licznik,ul2->mianownik);
  ul2->licznik = ul1->licznik * ul2->licznik;
  ul2->mianownik = ul1->mianownik * ul2->mianownik;
  ul2 = Skracanie(ul2);
  return ul2;
}

Ul *dzielenie(Ul *ul1, Ul *ul2)
{
  printf("%d/%d / %d/%d =",ul1->licznik,ul1->mianownik,ul2->licznik,ul2->mianownik);
  int temp = ul2->licznik;
  ul2->licznik = ul1->licznik * ul2->mianownik;
  ul2->mianownik = ul1->mianownik * temp;
  ul2 = Skracanie(ul2);
  return ul2;
}

void Wypisz(Ul *ulamek)
{
  if(ulamek->licznik == 0)
    printf(" 0\n");
  else if(ulamek->mianownik == 1)
    printf(" %d\n",ulamek->licznik);
  else
    printf(" %d/%d\n",ulamek->licznik,ulamek->mianownik);
}
