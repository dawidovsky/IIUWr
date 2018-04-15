#include "Macierz.hpp"

Macierz::Macierz(int n)
{
  kolumny = n;
  wiersze = n;
  macierz = new double *[n];
  for(int i = 0 ; i < n ; i++)
  {
    macierz[i] = new double [n];
    for(int j = 0; j < n ; j++)
    {
      if(i == j)
        macierz[i][j] = 1;
      else
        macierz[i][j] = 0;
    }
  }
}

Macierz::Macierz(int m, int n)
{
  wiersze = m;
  kolumny = n;
  macierz = new double *[m];
  for(int i = 0 ; i < n ; i++)
  {
    macierz[i] = new double [n];
    for(int j = 0; j < n ; j++)
        macierz[i][j] = 0;
  }
}

ostream& operator << (ostream& wy, const Macierz& mac)
{
  for(int i = 0 ; i < mac.wiersze ; i++ )
  {
    for(int j = 0 ; j < mac.kolumny ; j++)
      wy << mac.macierz[i][j] << " ";
    wy << endl;
  }
  return wy;
}

istream & operator >> (istream &we , Macierz &mac)
{
  for(int i = 0 ; i < mac.wiersze ; i++)
    for(int j = 0; j < mac.kolumny ; j++)
      we >> mac.macierz[i][j];
  return we;
}

Macierz& Macierz::operator = (const Macierz &mac)
{
    wiersze = mac.wiersze;
    kolumny = mac.kolumny;
    macierz = mac.macierz;
    return *this;
}

Macierz& Macierz::operator = (Macierz &&mac)
{
    wiersze = mac.wiersze;
    kolumny = mac.kolumny;
    macierz = mac.macierz;
    mac.wiersze = 0;
    mac.kolumny = 0;
    mac.macierz = nullptr;
    return *this;
}

Macierz Macierz::operator * (int skalar)
{
  Macierz wynik(this->wiersze,this->kolumny);
  for(int i = 0 ; i < this->wiersze ; i++)
    for(int j = 0; j < this->kolumny ; j++)
      wynik.macierz[i][j] = this->macierz[i][j] * skalar;
  return wynik;
}

Macierz Macierz::operator + (const Macierz &m2)
{
  if(this->wiersze != m2.wiersze || this->kolumny != m2.kolumny)
    throw "rozmiary_nie_pasuja";
  Macierz wynik(m2.wiersze,m2.kolumny);
  for(int i = 0 ; i < m2.wiersze ; i++)
    for(int j = 0; j < m2.kolumny ; j++)
      wynik.macierz[i][j] = this->macierz[i][j] + m2.macierz[i][j];
  return wynik;
}

Macierz Macierz::operator - (const Macierz &m2)
{
  if(this->wiersze != m2.wiersze || this->kolumny != m2.kolumny)
    throw "rozmiary_nie_pasuja";
  Macierz wynik(m2.wiersze,m2.kolumny);
  for(int i = 0 ; i < m2.wiersze ; i++)
    for(int j = 0; j < m2.kolumny ; j++)
      wynik.macierz[i][j] = this->macierz[i][j] - m2.macierz[i][j];
  return wynik;
}

Macierz & Macierz::operator *= (int skalar)
{
  for(int i = 0 ; i < this->wiersze ; i++)
    for(int j = 0; j < this->kolumny ; j++)
      this->macierz[i][j] = this->macierz[i][j] * skalar;
  return *this;
}

Macierz & Macierz::operator += (const Macierz &mac)
{
  for(int i = 0 ; i < this->wiersze ; i++)
    for(int j = 0; j < this->kolumny ; j++)
      this->macierz[i][j] = this->macierz[i][j] + mac.macierz[i][j];
  return *this;
}

Macierz & Macierz::operator -= (const Macierz &mac)
{
  for(int i = 0 ; i < this->wiersze ; i++)
    for(int j = 0; j < this->kolumny ; j++)
      this->macierz[i][j] = this->macierz[i][j] - mac.macierz[i][j];
  return *this;
}

Macierz Macierz::operator * (const Macierz &m)
{
  if(this->wiersze != m.kolumny)
    throw "rozmiary_nie_pasuja";
  Macierz wynik(m.wiersze,m.kolumny);
  for(int i = 0; i < this->wiersze; i++)
    for(int j = 0; j < m.kolumny; j++)
      for(int k = 0; k < this->kolumny; k++)
      {
        wynik.macierz[i][j] += this->macierz[i][k] * m.macierz[k][j];
      }
  return wynik;
}

Macierz & Macierz::operator *= (const Macierz &m)
{
  if(this->wiersze != m.kolumny)
    throw "rozmiary_nie_pasuja";
  Macierz wynik(*this);
  for(int i = 0; i < this->wiersze; i++)
    for(int j = 0; j < m.kolumny; j++)
      for(int k = 0; k < this->kolumny; k++)
      {
        this->macierz[i][j] += wynik.macierz[i][k] * m.macierz[k][j];
      }
  return *this;
}

Macierz::~Macierz()
{
  for(int i = 0 ; i < wiersze ; i++)
    delete [] macierz[i];
  delete [] macierz;
}
