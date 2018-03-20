/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 2 Implementacja ze zmianą ułamka
Program uruchamiamy z argumentami wywołania programu podając
dwa ułamki po spacji
w formie "liczba_całkowita/liczba_naturalna"
Język C - kompilator gcc 4.9.2*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Ulamki{
  int licznik;
  int mianownik;
}Ul;

Ul *Skracanie(Ul *ulamek);
Ul *Rozszerzenie(struct Ulamki ul1,struct Ulamki ul2, char znak);
Ul *dodawanie(Ul *ul1,Ul *ul2);
Ul *odejmowanie(Ul *ul1,Ul *ul2);
Ul *mnozenie(Ul *ul1, Ul *ul2);
Ul *dzielenie(Ul *ul1, Ul *ul2);
void Wypisz(Ul *ulamek);
