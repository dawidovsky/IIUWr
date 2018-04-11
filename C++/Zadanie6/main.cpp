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
  w = new Dodaj(
    new Potega(new Sin(new Liczba(60)),new Liczba(2)),
    new Potega(new Cos(new Liczba(60)),new Liczba(2)));
  cout << w->opis() << " = " << w->oblicz() << endl;

  // logarytm naturalny z e
  w = new Ln(new E());
  cout << w->opis() << " = " << w->oblicz() << endl;

  // przeciwna, odwrotna, bezwzgledna
  w = new Przeciwna(new Bezwzgledna(new Odwrotna(new Liczba(-0.5))));
  cout << w->opis() << " = " << w->oblicz() << endl;

  //zmienne
  w =
  new Dziel(
    new Mnoz(
      new Odejmij(new Zmienna("x"),new Liczba(1)),
      new Zmienna("x")),
    new Liczba(2));
    // for(double i=0.0;i<=1.0;i=i+0.01)
    // {
       Zmienna::dodaj_do_wektora("x",3);
       cout << w->opis() << " = " << w->oblicz() << endl;
    // }

    w =
    new Odejmij(
      new Dodaj(
        new Liczba(2),
        new Mnoz(new Zmienna("x"),new Liczba(7))),
      new Dodaj(
        new Mnoz(new Zmienna("y"),new Liczba(3)),
        new Liczba(5)));

    //  cout << w->opis() << " = " << w->oblicz() << endl;

    // potęgowania
    w = new Potega(new Liczba(2),
                              new Potega(new Liczba(2),new Liczba(3)));

    cout << w->opis() << " = " << w->oblicz() << endl;

    // odejmowanie - problem z prawą stroną
    w = new Odejmij(
                new Odejmij(new Liczba(1),new Liczba(3)),
                new Odejmij(new Liczba(1),new Liczba(4)));

    cout << w->opis() << " = " << w->oblicz() << endl;

  w = new Odejmij(new Odejmij(new Liczba(2), new Liczba(3)), new Mnoz(new Liczba(4), new Liczba(5)));

  cout << w->opis() << " = " << w->oblicz() << endl;
}
