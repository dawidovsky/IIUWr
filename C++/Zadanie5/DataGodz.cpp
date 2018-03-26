#include "Data.hpp"

// operator wyjscia
ostream& operator << (ostream& wy, const DataGodz &dt)
{
  wy << dt.dzien << "-" << dt.miesiac << "-" << dt.rok << "r ";
  wy << dt.godziny << ":" << dt.minuty << ":" << dt.sekundy;
  return wy;
}

// konstruktory
DataGodz::DataGodz()
{
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  dzien = ltm->tm_mday;
  miesiac = ltm->tm_mon;
  rok = ltm->tm_year+1900;
  godziny = ltm->tm_hour;
  minuty = ltm->tm_min;
  sekundy = ltm->tm_sec;
}

DataGodz::DataGodz(int dz, int mi, int rk, int god, int min, int sek)
{
  dzien = dz;
  miesiac = mi;
  rok = rk;
  godziny = god;
  minuty = min;
  sekundy = sek;
}

//przeciazenia operatorow
DataGodz DataGodz::operator ++ (int)
{
  this->sekundy++;
  if(this->sekundy == 60)
    {
      this->sekundy = 0;
      this->minuty++;
      if(this->minuty == 60)
        {
          this->minuty = 0;
          this->godziny++;
          if(this->godziny == 24)
            {
              this->godziny = 0;
              this->dzien++;
              bool prz = czyPrzestepny(*this);
              if(this->dzien > dniwmiesiacach[prz][this->miesiac])
                {
                  this->dzien = 1;
                  this->miesiac++;
                  if(this->miesiac == 13)
                    {
                      this->miesiac = 1;
                      this->rok++;
                    }
                }
            }
        }
    }
    return *this;
}

DataGodz DataGodz::operator -- (int)
{
  this->sekundy--;
  if(this->sekundy == -1)
    {
      this->sekundy = 59;
      this->minuty--;
      if(this->minuty == -1)
        {
          this->minuty = 59;
          this->godziny--;
          if(this->godziny == -1)
            {
              this->godziny = 23;
              this->dzien--;
              bool prz = czyPrzestepny(*this);
              if(this->dzien < 1)
                {
                  this->dzien = dniwmiesiacach[prz][this->miesiac];
                  this->miesiac--;
                  if(this->miesiac < 1)
                    {
                      this->miesiac = 12;
                      this->rok--;
                    }
                }
            }
        }
    }
    return *this;
}

DataGodz & DataGodz::operator += (int czas)
{
  this->sekundy += czas;
  while(this->sekundy > 59)
  {
    this->sekundy -= 60;
    this->minuty += 1;
    if(this->minuty > 59)
    {
        this->minuty = 0;
        this->godziny += 1;
        bool prz = czyPrzestepny(*this);
        if(this->godziny > 23)
        {
          this->godziny = 0;
          this->dzien++;
          if(this->dzien > dniwmiesiacach[prz][this->miesiac])
          {
            this->dzien = 1;
            this->miesiac++;
            if(this->miesiac == 13)
              {
                this->miesiac = 1;
                this->rok++;
              }
          }
        }
    }
  }
  return *this;
}

DataGodz & DataGodz::operator -= (int czas)
{
  this->sekundy -= czas;
  while(this->sekundy < 0)
  {
    this->sekundy += 60;
    this->minuty -= 1;
    if(this->minuty < 0)
    {
        this->minuty = 59;
        this->godziny -= 1;
        bool prz = czyPrzestepny(*this);
        if(this->godziny < 0)
        {
          this->godziny = 12;
          this->dzien--;
          if(this->dzien < 1)
          {
            this->dzien = dniwmiesiacach[prz][this->miesiac];
            this->miesiac--;
            if(this->miesiac < 1)
              {
                this->miesiac = 12;
                this->rok--;
              }
          }
        }
    }
  }
  return *this;
}

bool DataGodz::operator < (const DataGodz &dt)
{
  if(this->rok < dt.rok) return true;
  if(this->rok == dt.rok)
  {
    if(this->miesiac < dt.miesiac) return true;
    if(this->miesiac == dt.miesiac)
    {
      if(this->dzien < dt.dzien) return true;
      if(this->dzien == dt.dzien)
      {
        if(this->godziny < dt.godziny) return true;
        if(this->godziny == dt.godziny)
        {
          if(this->minuty < dt.minuty) return true;
          if(this->minuty == dt.minuty)
          {
            if(this->sekundy < dt.sekundy) return true;
          }
        }
      }
    }
  }

  return false;
}

bool DataGodz::operator == (const DataGodz &dt)
{
  if(this->rok != dt.rok) return false;
  if(this->miesiac != dt.miesiac) return false;
  if(this->dzien != dt.dzien) return false;
  if(this->godziny != dt.godziny) return false;
  if(this->minuty != dt.minuty) return false;
  if(this->sekundy != dt.sekundy) return false;
  return true;
}

//odejmowanie globalne
int operator - (const DataGodz &dt, const DataGodz &dt2)
{
  Data obj;
  bool czy_przestepny = dt.get_r()%4 == 0 ? 1 : 0;
  int ile_przestepnych = dt.get_r()/4 - dt.get_r()/100 + dt.get_r()/400;
  int iledni = ile_przestepnych*366 + (dt.get_r()-ile_przestepnych)*365
               + obj.dniodpoczroku[czy_przestepny][dt.get_m()];
  int odjemna_sekundy = dt.get_min() * 60 + dt.get_sek();
  int odjemna =  iledni * 24;
  czy_przestepny = dt2.get_r()%4 == 0 ? 1 : 0;
  ile_przestepnych = dt2.get_r()/4 - dt2.get_r()/100 + dt2.get_r()/400;
  iledni = ile_przestepnych*366 + (dt2.get_r()-ile_przestepnych)*365
               + obj.dniodpoczroku[czy_przestepny][dt2.get_m()];
  int odjemnik_sekundy = dt2.get_min() * 60 + dt2.get_sek();
  int odjemnik = iledni * 24;
  return (odjemna - odjemnik) * 3600 + odjemna_sekundy - odjemnik_sekundy;
}
