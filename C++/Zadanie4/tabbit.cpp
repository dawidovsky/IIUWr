#include "tabbit.hpp"
//metody z tab_bit::ref
bool tab_bit::ref::Get_bit(uint64_t * tab, int bitindex)
{
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  return (tab[byte] & (1<<bit));
}

void tab_bit::ref::Set_bit(uint64_t * tab, int bitindex, bool val)
{
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  if(val == 1)
    tab[byte] |= 1 << bit;
  if(val == 0)
    tab[byte] &= ~(1 << bit);
}

uint64_t &tab_bit::ref::Get_wsk(uint64_t *tab,int i)
{
  int byte = i / 8;
  int bit = i%8;
  uint64_t &wsk = tab[byte];
  wsk = wsk << bit;
  return wsk;
}

//metody pomocnicze
bool tab_bit::czytaj(int i) const
{
  tab_bit::ref obj;
  return obj.Get_bit(tab,i);
}

void tab_bit::pisz(int i, bool b)
{
  tab_bit::ref obj;
  obj.Set_bit(tab,i,b);
}

//konstruktory z tab_bit
tab_bit::tab_bit(int rozmiar)
{
  dl = rozmiar;
  int roz_tab = ceil(dl/8)+1;
  tab = new slowo[roz_tab];
  for(int i=0;i<roz_tab;i++)
    tab[i] = 0;
}

tab_bit::tab_bit(slowo rozmiar)
{
  dl = sizeof(slowo)*sizeof(rozmiar);
  int roz_tab = ceil(dl/8)+1;
  tab = new slowo[roz_tab];
  for(int i=0;i<roz_tab;i++)
    tab[i] = 0;
}

tab_bit::tab_bit(const tab_bit &obj)
{
    dl = obj.dl;
    if(tab) delete[] tab;
    tab = new slowo[dl+1];
    for(int i=0; i<dl+1; ++i) tab[i]=obj.tab[i];
}

tab_bit::tab_bit(tab_bit &&obj)
{
    dl=obj.dl;
    tab=obj.tab;
    obj.dl=0;
    obj.tab=nullptr;
}

tab_bit::tab_bit(initializer_list<bool> list)
{
    dl=list.size();
    tab = new slowo[dl+1];
    int i = 0;
    for(auto x : list)
    {
      pisz(i,x);
      i++;
    }
}

//destruktor
tab_bit::~tab_bit()
{
  if(tab)
  {
    delete [] tab;
    tab = nullptr;
  }
}

//wejście/wyjście
ostream& operator<<(ostream& wy, const tab_bit& tb)
{
  int iter = 0;
  for( int i = 0 ; i < tb.dl ; i++ )
  {
    wy << tb.czytaj(i);
    iter++;
    if(iter%8 == 0)
      wy << " ";
  }
  return wy;
}

istream& operator >>(istream& we, tab_bit &tb)
{
  cout << "Podaj rozmiar tablicy" << endl;
  we >> tb.dl;
  tab_bit obj(tb.dl);
}

//operator indeksowania
bool tab_bit::operator[](int i) const
{
   return czytaj(i);
}

uint64_t& tab_bit::operator[](int i)
{
   tab_bit::ref obj;
   uint64_t &wsk = obj.Get_wsk(tab,i);
   return wsk;
}

//operatory kopiowania i przypisania
tab_bit& tab_bit::operator=(const tab_bit &obj)
{
    dl = obj.dl;
    if(tab) delete[] tab;
    tab = new slowo[dl+1];
    for(int i=0; i<dl+1; ++i) tab[i]=obj.tab[i];
    return *this;
}

tab_bit& tab_bit::operator=(tab_bit &&obj)
{
    dl=obj.dl;
    tab=obj.tab;
    obj.dl=0;
    obj.tab=nullptr;
    return *this;
}

//operatory bitowe
tab_bit operator | (const tab_bit &u, const tab_bit &v)
{
  int max_index = (u.dl>v.dl?u.dl:v.dl);
  int min_index = (u.dl>v.dl?v.dl:u.dl);
  tab_bit obj(max_index);
  for(int i=0;i<min_index;i++)
  {
    if(u[i] == 1 || v[i] == 1) obj.pisz(i,1);
    else obj.pisz(i,0);
  }
  for(int i=min_index;i<max_index;i++)
  {
    if(max_index == u.dl)
    {
      if(u[i] == 1)obj.pisz(i,1);
      else obj.pisz(i,0);
    }
    else
    {
      if(v[i] == 1)obj.pisz(i,1);
      else obj.pisz(i,0);
    }

  }
  return obj;
}

tab_bit operator & (const tab_bit &u, const tab_bit &v)
{
  int max_index = (u.dl>v.dl?u.dl:v.dl);
  tab_bit obj(max_index);
  for(int i=0;i<(u.dl>v.dl?v.dl:u.dl);i++)
  {
    if(u[i] == 1 && v[i] == 1) obj.pisz(i,1);
    else obj.pisz(i,0);
  }
  return obj;
}

tab_bit operator ^ (const tab_bit &u, const tab_bit &v)
{
  int max_index = (u.dl>v.dl?u.dl:v.dl);
  int min_index = (u.dl>v.dl?v.dl:u.dl);
  tab_bit obj(max_index);
  for(int i=0;i<min_index;i++)
  {
    if(u[i] != v[i]) obj.pisz(i,1);
    else obj.pisz(i,0);
  }
  for(int i=min_index;i<max_index;i++)
  {
    if(max_index == u.dl)
    {
      if(u[i] == 1)obj.pisz(i,1);
      else obj.pisz(i,0);
    }
    else
    {
      if(v[i] == 1)obj.pisz(i,1);
      else obj.pisz(i,0);
    }

  }
  return obj;
}

tab_bit& tab_bit::operator |= (const tab_bit &v)
{
  int min_index = (dl>v.dl?v.dl:dl);
  for(int i=0;i<min_index;i++)
  {
    if(czytaj(i) ==1 || v[i] == 1) pisz(i,1);
    else pisz(i,0);
  }
  if(min_index == dl)
  {
    for(int i=min_index;i<v.dl;i++)
    {
      if(v[i] == 1) pisz(i,1);
      else pisz(i,0);
    }
  }
  else
  {
    for(int i=min_index;i<dl;i++)
    {
      if(czytaj(i) == 1) pisz(i,1);
      else pisz(i,0);
    }
  }
  return *this;
}

tab_bit& tab_bit::operator &= (const tab_bit &v)
{
  for(int i=0;i<(dl>v.dl?v.dl:dl);i++)
  {
    if(czytaj(i) == 1 && v[i] == 1) pisz(i,1);
    else pisz(i,0);
  }
  return *this;
}

tab_bit& tab_bit::operator ^= (const tab_bit &v)
{
  int min_index = (dl>v.dl?v.dl:dl);
  for(int i=0;i<min_index;i++)
  {
    if(czytaj(i) != v[i]) pisz(i,1);
    else pisz(i,0);
  }
  if(min_index == dl)
  {
    for(int i=min_index;i<v.dl;i++)
    {
      if(v[i] != 0) pisz(i,1);
      else pisz(i,0);
    }
  }
  else
  {
    for(int i=min_index;i<dl;i++)
    {
      if(czytaj(i) != 0) pisz(i,1);
      else pisz(i,0);
    }
  }
  return *this;
}

tab_bit tab_bit::operator !()
{
  for(int i=0;i<dl;i++)
  {
    if(!czytaj(i)) pisz(i,1);
    else pisz(i,0);
  }
  return *this;
}
