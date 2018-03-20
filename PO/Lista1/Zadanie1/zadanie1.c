/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 1
Tworzymy figury i wyonujemy operacje poprzez zmianę kodu
Język C - kompilator gcc 4.9.2*/

#include "Figury.h"

int main() {
  int size = 3;
  fig *figury[size];
  figury[0] = createKwadrat(figury[0],0,0,3);
  figury[1] = createTrojkat(figury[1],0,0,3,5);
  figury[2] = createKolo(figury[2],0,0,2,8);
  printf("Pola poszczegolnych figur :\nkwadrat: %f\ntrojkat:%f\nkolo: %f\n",pole(figury[0]),pole(figury[1]),pole(figury[2]));
  printf("Kwadrat zaczyna sie w punkcie (%f,%f)\nPrzesuwamy goo wektor [2,2]\n",figury[0]->poczx,figury[0]->poczy);
  przesun(figury[0],2,2);
  printf("Kwadrat zaczyna sie w punkcie (%f,%f)\n",figury[0]->poczx,figury[0]->poczy);
  printf("Suma pol: %f\n",sumapol(3,figury));
}
