#include "wymierne.hpp"

using namespace obliczenia;

Wymierna::Wymierna(int l, int m)
{
  if(m == 0)
    throw NieDzielPrzezZero("Nie dziel przez zero");
  if(m < 0)
  {
    licz = -l;
    mian = -m;
  }
  else
  {
    licz = l;
    mian = m;
  }
  Skroc();
}

Wymierna::Wymierna(int x) : licz(x), mian(1) {
  Skroc();
}

Wymierna::NWD(int a, int b)
{
  while(a!=b)
  {
    if(a>b)
        a-=b;
    else
        b-=a;
  }
  return a;
}

Wymierna::NWW(int a, int b)
{
  int c = NWD(a,b);
  return a/c * b;
}

Wymierna::Skroc()
{
  int a;
  if(this->licz < 0)
    a = -this->licz;
  else
    a = this->licz;
  a = NWD(a,this->mian);
  this->licz /= a;
  this->mian /= a;
}

int Wymierna::Skroc(int64_t a, int64_t b)
{
  if(a < 0)
    a = -a;
  while(a!=b)
  {
    if(a>b)
    a-=b;
    else
      b-=a;
  }
  if(a > INT_MAX)
    throw PrzekroczonoZakres("Przekroczono zakres inta");
  return a;
}

Wymierna & Wymierna::operator + (const Wymierna & w1)
{
  int64_t r = NWW(this->mian,w1.get_m());
  int64_t l = this->licz * (r/this->mian) + w1.get_l() * (r/w1.get_m());
  int x = Skroc(l,r);
  if(r/x > INT_MAX || l/x > INT_MAX)
    throw PrzekroczonoZakres("Przekroczono zakres inta");
  int li = l/x;
  int mi = r/x;
  Wymierna w2(li,mi);
  return w2;
}

Wymierna & Wymierna::operator - (const Wymierna & w1)
{
  int64_t r = NWW(this->mian,w1.get_m());
  int64_t l = this->licz * (r/this->mian) - w1.get_l() * (r/w1.get_m());
  int x = Skroc(l,r);
  if(r/x > INT_MAX || l/x > INT_MAX)
    throw PrzekroczonoZakres("Przekroczono zakres inta");
  int li = l/x;
  int mi = r/x;
  Wymierna w2(li,mi);
  return w2;
}

Wymierna & Wymierna::operator * (const Wymierna & w1)
{
  if(this->licz * w1.get_l() > INT_MAX || this->mian * w1.get_m() > INT_MAX)
    throw PrzekroczonoZakres("Przekroczono zakres inta");
  int l = this->licz * w1.get_l();
  int r = this->mian * w1.get_m();
  Wymierna w2(l, r);
  return w2;
}

Wymierna & Wymierna::operator / (const Wymierna & w1)
{
  if(this->licz * w1.get_m() > INT_MAX || this->mian * w1.get_l() > INT_MAX)
    throw PrzekroczonoZakres("Przekroczono zakres inta");
  if(w1.get_l() == 0)
    throw NieDzielPrzezZero("Nie dziel przez zero");
  int l = this->licz * w1.get_m();
  int r = this->mian * w1.get_l();
  Wymierna w2(l, r);
  return w2;
}

Wymierna Wymierna::operator ! ()
{
  if(this->licz == 0)
    throw NieDzielPrzezZero("Nie dziel przez zero");
  if(this->licz < 0)
  {
    int temp = -this->licz;
    this->licz = -this->mian;
    this->mian = temp;
  }
  else
  {
    int temp = this->licz;
    this->licz = this->mian;
    this->mian = temp;
  }
  return *this;
}

Wymierna Wymierna::operator - ()
{
  this->licz = -this->licz;
  return *this;
}

Wymierna::operator double()
{
  return (double)this->licz/this->mian;
}

Wymierna::operator int()
{
  return this->licz/this->mian;
}

NieDzielPrzezZero::NieDzielPrzezZero(const char* t)
{
  tresc = t;
}

const char* NieDzielPrzezZero::what()
{
  return tresc.c_str();
}

PrzekroczonoZakres::PrzekroczonoZakres(const char* t)
{
  tresc = t;
}

const char* PrzekroczonoZakres::what()
{
  return tresc.c_str();
}
