#include "Macierz.hpp"

int main()
{
  Macierz mdia(5);
  cout << mdia << endl << endl;
  mdia *= 10;
  cout << mdia << endl << endl;
  Macierz nowa = mdia.usunWK(1,2);
  cout << nowa << endl << endl;
}
