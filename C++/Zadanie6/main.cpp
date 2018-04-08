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
  Wyrazenie *t =
  new Dziel(
    new Mnoz(
      new Odejmij(new Zmienna("x"),new Liczba(1)),
      new Zmienna("x")),
    new Liczba(2));
    // for(double i=0.0;i<=1.0;i=i+0.01)
    // {
       Zmienna::dodaj_do_wektora("x",3);
       cout << t->opis() << " = " << t->oblicz() << endl;
    // }

    Wyrazenie *y =
    new Odejmij(
      new Dodaj(
        new Liczba(2),
        new Mnoz(new Zmienna("x"),new Liczba(7))),
      new Dodaj(
        new Mnoz(new Zmienna("y"),new Liczba(3)),
        new Liczba(5)));

      cout << y->opis() << " = " << y->oblicz() << endl;

    // potęgowania
    Wyrazenie *u = new Potega(new Liczba(2),
                              new Potega(new Liczba(2),new Liczba(3)));

    cout << u->opis() << " = " << u->oblicz() << endl;

    // odejmowanie - problem z prawą stroną
    Wyrazenie *i = new Odejmij(
                new Odejmij(new Liczba(1),new Liczba(3)),
                new Odejmij(new Liczba(1),new Liczba(4)));

    cout << i->opis() << " = " << i->oblicz() << endl;

  Wyrazenie * qw = new Odejmij(new Odejmij(new Liczba(2), new Liczba(3)), new Mnoz(new Liczba(4), new Liczba(5)));

  cout << qw->opis() << " = " << qw->oblicz() << endl;
}
