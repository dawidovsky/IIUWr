#include "tabbit.hpp"

int main()
{
  tab_bit t(45);         // tablica 46-bitowa (zainicjalizowana zerami)
  tab_bit v(t);          // tablica 46-bitowa (skopiowana z t)
  tab_bit u(45ull);      // tablica 64-bitowa (sizeof(uint64_t)*8)
  tab_bit w({1, 0, 1, 1, 0, 0, 0, 1});
  v[0] = 1;              // ustawienie bitu 0-go bitu na 1
  // t[45] = true;         // ustawienie bitu 45-go bitu na 1
  bool b = w[2];         // odczytanie bitu 1-go
  // u[63] = 1;
  // u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
  cout << "b: w[2]: " << b << endl;
  cout << "u[45]: " << u[45] << " u[46]: " << u[46] << " u[63]: " << u[63] <<endl;
  cout << "t: " << t << endl;
  cout << "v: " << v << endl;
  cout << "u: " << u << endl;
  cout << "w: " << w << endl;
  v |= w;
  cout << "v |= w : " << v << endl;
  v &= w;
  cout << "v &= w : " << v << endl;
  v ^= w;
  cout << "v ^= w : " << v << endl;
  cout << "!t: " << !t << endl;
  v = t&w;
  cout << "v = t&w : " << v << endl;
  v = t|w;
  cout << "v = t|w : " << v << endl;
  v = t^w;
  cout << "v = t^w : " << v << endl;
}
