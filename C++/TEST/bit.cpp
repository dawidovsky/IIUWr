#include <iostream>

using namespace std;

bool getbit(uint64_t * tab, int bitindex) {
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  return (tab[byte] & (1<<bit));
}

uint64_t &getwsk(uint64_t *tab,int i)
{
  int byte = i / 8;
  return tab[byte];
}

void setbit(uint64_t * tab, int bitindex, bool val)
{
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  if(val == 1)
    tab[byte] |= 1 << bit;
  if(val == 0)
    tab[byte] &= ~(1 << bit);
}


int main()
{
  int rozmiar = 6;
  uint64_t tab[rozmiar] = {0,0,0,0,0};
  int bitindex = 12;
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  int iter = 0;
  for( int i = 0 ; i < 32 ; i++ )
  {
    cout << getbit(tab, i);
    iter++;
    if(iter%8 == 0)
      cout << " ";
  }
  cout << endl;
  int i = 5;
  bit = i%8;
  uint64_t &wsk = getwsk(tab,i);

  cout << "wartosc getbit: " << getbit(tab,5) << endl;
  cout << wsk << endl;
  wsk = 1<<bit;
  cout << wsk << endl;
  wsk = 0;
  cout << "wartosc getbit: " << getbit(tab,5) << endl;
  for( int i = 0 ; i < 32 ; i++ )
  {
    cout << getbit(tab, i);
    iter++;
    if(iter%8 == 0)
      cout << " ";
  }
}
