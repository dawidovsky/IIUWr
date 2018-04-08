#include "Wyrazenie.hpp"

double Liczba::oblicz()
{
  return wartosc;
}

string Liczba::opis()
{
  if(wartosc == (int)wartosc)
    return to_string((int)wartosc);
  string str = to_string(wartosc);
  str.erase (str.find_last_not_of('0') + 1, string::npos); // npos - do końca stringa
  return str;
}

Liczba::Liczba(double a)
{
  wartosc = a;
}

Dodaj::Dodaj(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Dodaj::oblicz()
{
  return a->oblicz() + b->oblicz();
}

string Dodaj::opis()
{
  string lewa = a->opis();
  string prawa = b->opis();
  // if(b->get_prio() == priorytet)
  //   prawa = "(" + prawa + ")";
  return lewa + " + " + prawa;
}

Odejmij::Odejmij(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Odejmij::oblicz()
{
  return a->oblicz() - b->oblicz();
}

string Odejmij::opis()
{
  string lewa = a->opis();
  string prawa = b->opis();
  if(b->get_prio() == priorytet)
     prawa = "(" + prawa + ")";
  return lewa + " - " + prawa;
}

Mnoz::Mnoz(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Mnoz::oblicz()
{
  return a->oblicz() * b->oblicz();
}

string Mnoz::opis()
{
  string lewa = a->opis();
  if(a->get_prio() < priorytet)
    lewa = "(" + lewa + ")";
  string prawa = b->opis();
  if(b->get_prio() < priorytet)
    prawa = "(" + prawa + ")";
  return lewa + " * " + prawa;
}

Dziel::Dziel(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Dziel::oblicz()
{
  if(b->oblicz() == 0)
    throw "Nie dzielimy przez zero";
  return a->oblicz() / b->oblicz();
}

string Dziel::opis()
{
  string lewa = a->opis();
  if(a->get_prio() < priorytet)
    lewa = "(" + lewa + ")";
  string prawa = b->opis();
  if(b->get_prio() < priorytet)
    prawa = "(" + prawa + ")";
  return lewa + " / " + prawa;
}

Potega::Potega(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Potega::oblicz()
{
  return pow(a->oblicz(),b->oblicz());
}

string Potega::opis()
{
  string lewa = a->opis();
  if(a->get_prio() < priorytet)
    lewa = "(" + lewa + ")";
  string prawa = b->opis();
  if(b->get_prio() < priorytet)
    prawa = "(" + prawa + ")";
  return lewa + " ^ " + prawa;
}

Log::Log(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Log::oblicz()
{
  return (log(b->oblicz())/log(a->oblicz()));
}

string Log::opis()
{
  string lewa = a->opis();
  if(a->get_prio() <= priorytet)
    lewa = "(" + lewa + ")";
  string prawa = b->opis();
  if(b->get_prio() <= priorytet)
    prawa = "(" + prawa + ")";
  return "log" + lewa + "z" + prawa;
}

Modulo::Modulo(Wyrazenie *lewa, Wyrazenie *prawa)
{
    a = lewa;
    b = prawa;
}

double Modulo::oblicz()
{
  return fmod(a->oblicz(),b->oblicz());
}

string Modulo::opis()
{
  string lewa = a->opis();
  if(a->get_prio() < priorytet)
    lewa = "(" + lewa + ")";
  string prawa = b->opis();
  if(b->get_prio() < priorytet)
    prawa = "(" + prawa + ")";
  return lewa + "%" + prawa;
}

Ln::Ln(Wyrazenie *wyr)
{
    a = wyr;
}

double Ln::oblicz()
{
  return log(a->oblicz());
}

string Ln::opis()
{
  return "log(" + a->opis() + ")";
}

Sin::Sin(Wyrazenie *wyr)
{
    a = wyr;
}

double Sin::oblicz()
{
  return sin(a->oblicz());
}

string Sin::opis()
{
  return "sin(" + a->opis() + ")";
}

Cos::Cos(Wyrazenie *wyr)
{
    a = wyr;
}

double Cos::oblicz()
{
  return cos(a->oblicz());
}

string Cos::opis()
{
  return "cos(" + a->opis() + ")";
}

Exp::Exp(Wyrazenie *wyr)
{
    a = wyr;
}

double Exp::oblicz()
{
  return exp(a->oblicz());
}

string Exp::opis()
{
  return "exp(" + a->opis() + ")";
}

Przeciwna::Przeciwna(Wyrazenie *wyr)
{
    a = wyr;
}

double Przeciwna::oblicz()
{
  return a->oblicz() * -1;
}

string Przeciwna::opis()
{
  return "przeciwna(" + a->opis() + ")";
}

Odwrotna::Odwrotna(Wyrazenie *wyr)
{
    a = wyr;
}

double Odwrotna::oblicz()
{
  if(a->oblicz() == 0)
    throw "Nie dzielimy przez zero";
  return 1/a->oblicz();
}

string Odwrotna::opis()
{
  return "odwrotna(" + a->opis() + ")";
}

Bezwzgledna::Bezwzgledna(Wyrazenie *wyr)
{
    a = wyr;
}

double Bezwzgledna::oblicz()
{
  return abs(a->oblicz());
}

string Bezwzgledna::opis()
{
  return "|" + a->opis() + "|";
}
