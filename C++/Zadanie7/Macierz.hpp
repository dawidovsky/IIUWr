#include <iostream>
#include <ostream>
#include <algorithm>
#include <exception>

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
    Macierz(const Macierz &mac);
    Macierz(Macierz &&mac);
    ~Macierz();

    friend istream & operator >> (istream &we, Macierz &mac);
    friend ostream & operator << (ostream &wy, const Macierz &mac);

    Macierz & operator = (const Macierz &tb);
    Macierz & operator = (Macierz &&tb);

    Macierz operator * (double skalar);
    Macierz operator + (const Macierz &m2);
    Macierz operator - (const Macierz &m2);

    Macierz & operator *= (double skalar);
    Macierz & operator += (const Macierz &mac);
    Macierz & operator -= (const Macierz &mac);

    Macierz operator * (const Macierz &m);
    Macierz & operator *= (const Macierz &m);

    void zamienW(int x, int y);
    void zamienK(int x, int y);
    void mnozW(int x, int skalar);
    void mnozK(int x, int skalar);
    void dodajW(int x, int y);
    void dodajK(int x, int y);
    Macierz usunWK(int x, int y);
    Macierz usunW(int x);
    Macierz usunK(int y);
    Macierz transpozycja();
};

class SkalarNieZero : public exception
{
  private:
    string tresc;
  public:
    SkalarNieZero();
    SkalarNieZero(const SkalarNieZero &c) = default;
    SkalarNieZero & operator = (const SkalarNieZero &tb) = default;
    virtual const string what();
    virtual ~SkalarNieZero() = default;
};

class RozmiaryNiePasuja : public exception
{
private:
  string tresc;
public:
  RozmiaryNiePasuja();
  RozmiaryNiePasuja(const RozmiaryNiePasuja &c) = default;
  RozmiaryNiePasuja & operator = (const RozmiaryNiePasuja &tb) = default;
  string what();
  virtual ~RozmiaryNiePasuja() = default;
};
