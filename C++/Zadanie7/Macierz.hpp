#include <iostream>
#include <ostream>


using namespace std;

class Macierz
{
  private:
    int wiersze;
    int kolumny;
    double **macierz;

  public:
    Macierz(int n);
    Macierz(int m, int n);
    Macierz(const Macierz &mac) = default;
    Macierz(Macierz &&mac) = default;
    ~Macierz();

    friend istream & operator >> (istream &we, Macierz &mac);
    friend ostream & operator << (ostream &wy, const Macierz &mac);

    Macierz & operator = (const Macierz &tb);
    Macierz & operator = (Macierz &&tb);

    Macierz operator * (int skalar);
    Macierz operator + (const Macierz &m2);
    Macierz operator - (const Macierz &m2);

    Macierz & operator *= (int skalar);
    Macierz & operator += (const Macierz &mac);
    Macierz & operator -= (const Macierz &mac);

    Macierz operator * (const Macierz &m);
    Macierz & operator *= (const Macierz &m);
};
