#include <iostream>
#include <ostream>
#include <algorithm>
#include <exception>

using namespace std;
namespace obliczenia
{
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

      friend istream & operator >> (istream &we, Macierz &mac)
      {
        for(int i = 0 ; i < mac.wiersze ; i++)
          for(int j = 0; j < mac.kolumny ; j++)
            we >> mac.macierz[i][j];
        return we;
      };
      friend ostream & operator << (ostream &wy, const Macierz &mac)
      {
        for(int i = 0 ; i < mac.wiersze ; i++ )
        {
          for(int j = 0 ; j < mac.kolumny ; j++)
            wy << mac.macierz[i][j] << " ";
          wy << endl;
        }
        return wy;
      };

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
      SkalarNieZero() = default;
      SkalarNieZero(const char* t);
      SkalarNieZero(const SkalarNieZero &c) = default;
      SkalarNieZero & operator = (const SkalarNieZero &tb) = default;
      virtual const char* what();
      virtual ~SkalarNieZero() = default;
  };

  class RozmiaryNiePasuja : public exception
  {
    private:
      string tresc;
    public:
      RozmiaryNiePasuja() = default;
      RozmiaryNiePasuja(const char* t);
      RozmiaryNiePasuja(const RozmiaryNiePasuja &c) = default;
      RozmiaryNiePasuja & operator = (const RozmiaryNiePasuja &tb) = default;
      virtual const char* what();
      virtual ~RozmiaryNiePasuja() = default;
  };

  class Brak : public exception
  {
    private:
      string tresc;
    public:
      Brak() = default;
      Brak(const char* t);
      Brak(const Brak &c) = default;
      Brak & operator = (const Brak &tb) = default;
      virtual const char* what();
      virtual ~Brak() = default;
  };

}
