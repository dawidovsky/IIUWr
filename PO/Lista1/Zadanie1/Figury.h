/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 1
Tworzymy figury i wyonujemy operacje poprzez zmianę kodu
Język C - kompilator gcc 4.9.2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846
enum typfig {Kwadrat, Trojkat, Kolo};

typedef struct Figura{
  enum typfig jaka;
  float poczx;
  float poczy;
  float wekx;
  float weky;
}fig;

float pole(fig *f);
void przesun(fig *f, float x, float y);
fig *createKwadrat(fig *kwa,float poczx, float poczy,float wek);
fig *createTrojkat(fig *tro,float poczx, float poczy,float wekx, float weky);
fig *createKolo(fig *kol,float poczx, float poczy,float wekx, float weky);
float sumapol(int size, fig *f[size]);
