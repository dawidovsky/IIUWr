#include "stos.hpp"

Stos::Stos() : Stos(1) {};
Stos::Stos(const int &poj) : pojemnosc(poj) {};
Stos::Stos(const Stos &elem)
{
  int ile = elem.get_ile();
  this->ile = ile;
  this->pojemnosc = elem.get_poj();
  copy(elem.stos, elem.stos + ile, this->stos);
}

Stos::Stos(const Stos && elem)
{
  this->ile = elem.get_ile();
  this->pojemnosc = elem.get_poj();
  this->stos = move(elem.stos);

  elem.stos = nullptr;
}

Stos::Stos(initializer_list<string> list)
{
  this->ile = 0;
  this->pojemnosc = list.size();
  for(auto x : list)
  {
    wloz(x);
  }
}

Stos & Stos::operator =(const Stos & elem)
{
  if(this != &elem)
  {
    delete [] this->stos;

    int ile = elem.get_ile();
    this->stos = new string[elem.get_poj()];

    this->ile = ile;
    this->pojemnosc = elem.get_poj();
    copy(elem.stos, elem.stos + ile, this->stos);

  }
  return *this;
}

Stos & Stos::operator =(const Stos && elem)
{
  if(this != &elem)
  {
    swap(this->stos,elem.stos);
    swap(this->ile,elem.ile);
    swap(this->pojemnosc,elem.pojemnosc);
  }
  return *this;
}

void Stos::wloz(const string &napis)
{
  int ile = get_ile();
  this->stos[ile] = napis;
  ile++;
  set_ile(ile);
}

string Stos::sciagnij()
{
  int ile = get_ile();
  ile--;
  set_ile(ile);
  return stos[ile];
}

int Stos::rozmiar()
{
  return get_ile();
}

string Stos::sprawdz()
{
  int ile = get_ile();
  if(ile == 0) return "Brak elementow na stosie ";
  return stos[ile-1];
}

Stos::~Stos()
{
  delete [] &stos;
}
