#include "Wyrazenie.hpp"

vector<pair<string,double>> Zmienna::tab;

int main()
{
  // nawiasowanie
  Wyrazenie *w = new Dodaj(new Liczba(5), new Mnoz(
    new Odejmij(new Liczba(2), new Liczba(1)),
    new Potega(new Liczba(2),
    new Modulo(new Liczba(8), new Liczba(5)))));
  cout << w->opis() << " = " << w->oblicz() << endl;

 // jedynka trygonometryczna
  Wyrazenie *q = new Dodaj(
    new Potega(new Sin(new Liczba(60)),new Liczba(2)),
    new Potega(new Cos(new Liczba(60)),new Liczba(2)));
  cout << q->opis() << " = " << q->oblicz() << endl;

  // logarytm naturalny z e
  Wyrazenie *e = new Ln(new E());
  cout << e->opis() << " = " << e->oblicz() << endl;

  // przeciwna, odwrotna, bezwzgledna
  Wyrazenie *r = new Przeciwna(new Bezwzgledna(new Odwrotna(new Liczba(-0.5))));
  cout << r->opis() << " = " << r->oblicz() << endl;

  //zmienne
  vector<pair<string,double>> v;
  Wyrazenie *t =
  new Dziel(
    new Mnoz(
      new Odejmij(new Zmienna("x"),new Liczba(1)),
      new Zmienna("x")),
    new Liczba(2));
    Zmienna::dodaj_do_wektora("x",3);
  cout << t->opis() << " = " << t->oblicz();
}
