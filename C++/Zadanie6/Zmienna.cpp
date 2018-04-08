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
  if(!czyJest(a))
    tab.push_back(make_pair(a,war));
  else
  {
    for(auto i = tab.begin(); i != tab.end(); i++ )
    {
       if(i->first == a)
        i->second = war;
    }
  }
}

double Zmienna::wypisz(string x)
{
  for(auto i = tab.begin(); i != tab.end(); i++ )
  {
     if(i->first == x)
      return i->second;
  }
}

bool Zmienna::czyJest(string x)
{
  for(auto i = tab.begin(); i != tab.end(); i++ )
  {
     if(i->first == x)
      return true;
  }
  return false;
}

double Zmienna::oblicz()
{
  return wypisz(nazwa);
}
