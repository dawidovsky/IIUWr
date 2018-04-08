#include "Wyrazenie.hpp"

Zmienna::Zmienna(string a)
{
  nazwa = a;
}

Zmienna::Zmienna(vector<pair<string,double>> a)
{
  tab = a;
}

string Zmienna::opis()
{
  return nazwa;
}

void Zmienna::dodaj_do_wektora(string a, double war)
{
  tab.push_back(make_pair(a,war));
}

double Zmienna::szukaj(string x)
{
  for(auto i = tab.begin(); i != tab.end(); i++ )
  {
     if(i->first == x)
      return i->second;
  }
}

double Zmienna::oblicz()
{
  return szukaj(nazwa);
}
