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
    ~Wyrazenie() = default;
};

class operator1arg : public Wyrazenie
{
  public:
    Wyrazenie *a;
    ~operator1arg();
};

class operator2arg : public operator1arg
{
  public:
    Wyrazenie *b;
    ~operator2arg();
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
    bool static czyJest(string x);
    double static wypisz(string x);
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

class Dodaj : public operator2arg
{
  private:
    int priorytet = 1;

  public:
    Dodaj(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Odejmij : public operator2arg
{
  private:
    int priorytet = 1;

  public:
    Odejmij(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Mnoz : public operator2arg
{
  private:
    int priorytet = 2;

  public:
    Mnoz(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Dziel : public operator2arg
{
  private:
    int priorytet = 2;

  public:
    Dziel(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Potega : public operator2arg
{
  private:
    int priorytet = 3;

  public:
    Potega(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Log : public operator2arg
{
  private:
    int priorytet = 3;

  public:
    Log(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Modulo : public operator2arg
{
  private:
    int priorytet = 2;

  public:
    Modulo(Wyrazenie *lewa, Wyrazenie *prawa);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Ln : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Ln(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Sin : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Sin(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Cos : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Cos(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Exp : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Exp(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Bezwzgledna : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Bezwzgledna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Przeciwna : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Przeciwna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};

class Odwrotna : public operator1arg
{
  private:
    int priorytet = 5;

  public:
    Odwrotna(Wyrazenie *wyr);
    virtual get_prio(){return priorytet;};
    virtual double oblicz();
    virtual string opis();
};
