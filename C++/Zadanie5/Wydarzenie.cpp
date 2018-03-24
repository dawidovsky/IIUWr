#include "Data.hpp"
#include <algorithm>

Wydarzenie::Wydarzenie(const DataGodz &dt, string napis)
{
  data = dt;
  opis = napis;
}

bool Wydarzenie::operator < (const Wydarzenie &dt)
{
  if(this->data < dt.data) return true;
  return false;
}

vector<Wydarzenie> Wydarzenie::sortowanie(vector<Wydarzenie> wyd)
{
  for(int j = 0; j < wyd.size() - 1; j++)
    for(int i = 0; i < wyd.size() - 1; i++)
      if(wyd[i+1] < wyd[i]) swap(wyd[i+1], wyd[i]);
  return wyd;
}
