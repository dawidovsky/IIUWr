#include <iostream>
#include <ctime>
#include <ostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// pierwszy dzien 15 października 1582 roku

class Data
{
  private:
    bool czyPoprawna(const Data &dt);  // poprawnosc daty
    int ileDniOdZera(const Data &dt); // ile dni uplynelo od 01.01.00
    friend ostream & operator << (ostream &wy, const Data &dt);

  protected:
    int dzien;  // chronione pola z danymi
    int miesiac;
    int rok;

    static bool czyPrzestepny(const Data &dt);  // sprawdzanie czy przestepny

  public:
    int get_d() const {return dzien;};   // gettery
    int get_m() const {return miesiac;};
    int get_r() const {return rok;};

    Data();                               // konstruktor bezargumentowy
    Data(int dz, int ms, int rk);         // konstruktor z danymi
    Data(const Data &dt) = default;       // konstruktor kopiujacy

    Data & operator = (const Data &dt) = default; // przypisanie kopiujace

    //przeciazenia operatorow
    virtual int operator - (const Data &dt);   // -
    Data operator ++ (int);                    // ++
    Data operator -- (int);                    // --
    Data & operator += (int dni);              // +=
    Data & operator -= (int dni);              // -=

    static int dniwmiesiacach[2][13];
    static int dniodpoczroku[2][13];

};

class DataGodz : public Data
{
  private:
    friend ostream & operator << (ostream &wy, const DataGodz &dt);

  protected:
    int sekundy;    // chronione pola z danymi
    int minuty;
    int godziny;

  public:
    int get_sek() const {return sekundy;};   // gettery
    int get_min() const {return minuty;};
    int get_godz() const {return godziny;};

    DataGodz();                             // konstruktor bezargumentowy
    DataGodz(int dz, int mie, int rok, int godz, int min, int sek);  // konstruktor z danymi
    DataGodz(const DataGodz &dt) = default; // konstruktor kopiujacy

    DataGodz & operator = (const DataGodz &dt) = default; // przypisanie kopiujace

    // przeciazenia operatorow
    DataGodz operator ++ (int);                     // ++
    DataGodz operator -- (int);                     // --
    DataGodz & operator += (int czas);              // +=
    DataGodz & operator -= (int czas);              // -=
    bool operator < (const DataGodz &dt);     // <
    bool operator == (const DataGodz &dt);    // ==
};

int operator - (const DataGodz &dt, const DataGodz &dt2); // globalny operator -

class Wydarzenie
{
  public:
    DataGodz data; // dane
    string opis;

    Wydarzenie() = default;
    Wydarzenie(const DataGodz &dt, string napis); // konstruktor z danymi

    bool operator < (const Wydarzenie &dt); // operator < 

    vector<Wydarzenie> sortowanie(vector<Wydarzenie> wyd); // sortowanie
};
