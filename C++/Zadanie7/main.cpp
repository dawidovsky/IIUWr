#include "Macierz.hpp"

int main()
{
  Macierz mdia(5);
  cout << "Macierz diagonalna:\n";
  cout << mdia;
  Macierz mzer(3,6);
  cout << "Macierz wypelniona zerami (3,6)\n";
  cout << mzer;
  Macierz mkop(mdia);
  cout << "Macierz kopiowana\n";
  cout << mkop;
  cout << "Macierz diagonalna pomnozona przez 5 \n";
  mdia = mdia * 5;
  Macierz m5(mdia);
  cout << mdia;
  cout << "Dodanie dwoch poprzednich macierzy \n";
  mkop = mdia + mdia;
  cout << mkop;
  cout << "Odejmowanie dwoch poprzednich macierzy \n";
  mdia = mkop - mdia;
  cout << mdia;
  cout << "Mnozenie *= skalarem\n";
  m5 *= 5;
  cout << m5;
  cout << "Odejmowanie -=\n";
  m5 -= mdia;
  cout << m5;
  cout << "Dodawanie +=\n";
  m5 += mkop;
  cout << m5;
  cout << "Mnozenie macierzy \n";
  mzer = m5 * mdia;
  cout << mzer;
  cout << "Mnozenie *= macierzy\n";
  cout << mzer << endl;
  mzer *= mdia;
  cout << mdia << endl;
  cout << mzer;
}
