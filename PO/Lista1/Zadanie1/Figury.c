/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 01.03.2018r
Lista 1 Zadanie 1
Tworzymy figury i wyonujemy operacje poprzez zmianę kodu
Język C - kompilator gcc 4.9.2*/

#include "Figury.h"

float pole(fig *f)
{
  float r;
  switch (f->jaka) {
    case Kwadrat: return f->wekx * f->wekx;break;
    case Trojkat: return (f->wekx * f->weky);break;
    case Kolo:
              r = sqrt(f->wekx*f->wekx+f->weky*f->weky);
              return r*r*M_PI;break;
  }
}

void przesun(fig *f, float x, float y)
{
  f->poczx += x;
  f->poczy += y;
}

fig *createKwadrat(fig *kwa,float poczx, float poczy,float wek)
{
  kwa = malloc(sizeof(fig));
  kwa->jaka = Kwadrat;
  kwa->poczx = poczx;
  kwa->poczy = poczy;
  kwa->wekx = wek;
  kwa->weky = wek;
  return kwa;
}

fig *createTrojkat(fig *tro,float poczx, float poczy,float wekx, float weky)
{
  tro = malloc(sizeof(fig));
  tro->jaka = Trojkat;
  tro->poczx = poczx;
  tro->poczy = poczy;
  tro->wekx = wekx;
  tro->weky = weky;
  return tro;
}

fig *createKolo(fig *kol,float poczx, float poczy,float wekx, float weky)
{
  kol = malloc(sizeof(fig));
  kol->jaka = Kolo;
  kol->poczx = poczx;
  kol->poczy = poczy;
  kol->wekx = wekx;
  kol->weky = weky;
  return kol;
}

float sumapol(int size, fig *f[size])
{
  float suma = 0;
  for(int i=0;i<size;i++)
  {
    suma += pole(f[i]);
  }
  return suma;
}
