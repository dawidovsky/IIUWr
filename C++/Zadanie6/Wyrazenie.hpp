#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Wyrazenie
{
  public:
    virtual double oblicz() = 0;
    virtual string opis() = 0;
    virtual int get_prio() = 0;
};

class Liczba : public Wyrazenie
{
  private:
    double wartosc;
    int priorytet = 10;

  public:
    virtual double oblicz();
    virtual string opis();
    virtual get_prio(){return priorytet;};
    Liczba(double a);
};

class Zmienna : public Wyrazenie
{
  private:
    string nazwa;
    int priorytet = 10;
    static vector<pair<string,double>> tab;

  public:
    virtual double oblicz();
    virtual string opis();
    void static dodaj_do_wektora(string a, double war);
    double static szukaj(string x);
    virtual get_prio(){return priorytet;};
    Zmienna(string a);
    Zmienna(vector<pair<string,double>> v);
};

class Stala : public Wyrazenie
{
  public:
    double wartosc;
    string nazwa;
    int priorytet = 10;
    virtual get_prio(){return priorytet;};
};

class Pi : public Stala
{
  public:
    Pi();
    virtual double oblicz();
    virtual string opis();
};

class E : public Stala
{
  public:
    E();
    virtual double oblicz();
    virtual string opis();
};

class Fi : public Stala
{
  public:
    Fi();
    virtual double oblicz();
    virtual string opis();
};

class Dodaj : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 1;

  public:
    Dodaj(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Odejmij : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 1;

  public:
    Odejmij(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Mnoz : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 2;

  public:
    Mnoz(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Dziel : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 2;

  public:
    Dziel(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Potega : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 3;

  public:
    Potega(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Log : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 3;

  public:
    Log(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Modulo : public Wyrazenie
{
  private:
    Wyrazenie *a;
    Wyrazenie *b;
    int priorytet = 2;

  public:
    Modulo(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Ln : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Ln(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Sin : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Sin(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Cos : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Cos(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Exp : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Exp(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Bezwzgledna : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Bezwzgledna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Przeciwna : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Przeciwna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Odwrotna : public Wyrazenie
{
  private:
    Wyrazenie *a;
    int priorytet = 5;

  public:
    Odwrotna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};
