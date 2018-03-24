#include "Data.hpp"

// operator wyjscia
ostream& operator << (ostream& wy, const Data &dt)
{
  return wy << dt.dzien << "-" << dt.miesiac << "-" << dt.rok << "r";
}

// tablice
int Data::dniwmiesiacach[2][13] =
{
  {0,31,28,31,30,31,30,31,31,30,31,30,31}, // lata zwykłe
  {0,31,29,31,30,31,30,31,31,30,31,30,31} // lata przestępne
};

int Data::dniodpoczroku[2][13] =
{
  {0,31,59,90,120,151,181,212,243,273,304,334,365}, // lata zwykłe
  {0,31,60,91,121,152,182,213,244,274,305,335,366} // lata przestępne
};

// konstruktory
Data::Data()
{
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  dzien = ltm->tm_mday;
  miesiac = ltm->tm_mon;
  rok = ltm->tm_year+1900;
}

Data::Data(int dz, int ms, int rk)
{
  dzien = dz;
  miesiac = ms;
  rok = rk;
  if(!czyPoprawna(*this))
  {
    cout << "Bledne dane";
    delete this;
  }
}

// sprawdzanie czy rok jest przestepny
bool Data::czyPrzestepny(const Data &dt)
{
  if(dt.rok%400 == 0) return true;
  if(dt.rok%4 == 0 && dt.rok%100 != 0) return true;
  return false;
}

// sprawdzanie czy data jest poprawna
bool Data::czyPoprawna(const Data &dt)
{
  if(dt.rok < 1582) return false;
  if(dt.miesiac > 12) return false;
  bool prz = czyPrzestepny(dt);
  if(dt.dzien > dniwmiesiacach[prz][dt.miesiac]) return false;
  return true;
}

// ile dni uplynelo od 1 stycznia roku 0
int Data::ileDniOdZera(const Data &dt)
{
  bool prz = czyPrzestepny(dt);
  int ile_przestepnych = dt.rok/4;
  return ile_przestepnych*366 + (dt.rok-ile_przestepnych)*365 + dniodpoczroku[prz][dt.miesiac];
}

//operatory
int Data::operator - (const Data &dt)
{
  int odjemna = ileDniOdZera(*this);
  int odjemnik = ileDniOdZera(dt);
  return abs(odjemna - odjemnik);
}

Data Data::operator ++ (int)
{
  bool prz = czyPrzestepny(*this);
  if(this->dzien == dniwmiesiacach[prz][this->miesiac])
  {
    this->dzien = 1;
    if(this->miesiac == 12)
    {
      this->miesiac = 1;
      this->rok += 1;
    }
    else
      this->miesiac += 1;
  }
  else
    this->dzien += 1;
  return *this;
}

Data Data::operator -- (int)
{
  bool prz = czyPrzestepny(*this);
  if(this->dzien == 1)
  {
    if(this->miesiac == 1)
    {
      this->miesiac = 12;
      this->rok -= 1;
      this->dzien = 31;
    }
    else
    {
      this->miesiac -= 1;
      this->dzien = dniwmiesiacach[prz][this->miesiac];
    }
  }
  else
    this->dzien -= 1;
  return *this;
}

Data & Data::operator += (int dni)
{
  bool prz = czyPrzestepny(*this);
  this->dzien += dni;
  while(this->dzien > dniwmiesiacach[prz][this->miesiac])
  {
    this->dzien -= dniwmiesiacach[prz][this->miesiac];
    this->miesiac += 1;
    if(this->miesiac > 12)
    {
        this->miesiac = 1;
        this->rok += 1;
        prz = czyPrzestepny(*this);
    }
  }
  return *this;
}

Data & Data::operator -= (int dni)
{
  bool prz = czyPrzestepny(*this);
  this->dzien -= dni;
  while(this->dzien < 0)
  {
    this->dzien += dniwmiesiacach[prz][this->miesiac];
    this->miesiac -= 1;
    if(this->miesiac < 1)
    {
        this->miesiac = 12;
        this->rok -= 1;
        prz = czyPrzestepny(*this);
    }
  }
  return *this;
}
