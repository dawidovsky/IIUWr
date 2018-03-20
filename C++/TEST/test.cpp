#include <iostream>
#include <ostream>
#include <string>

using namespace std;

bool getbit(uint64_t * tab, int bitindex) {
  int byte = bitindex / 8;
  int bit = bitindex % 8;
  return (tab[byte] & (1<<bit));
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
  uint64_t tab[rozmiar] = {255};
  cout << getbit(tab,3);
}
