#include <iostream>
#include <ctime>
#include <ostream>
#include <cstdlib>

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
    double get_d() const {return dzien;};   // gettery
    double get_m() const {return miesiac;};
    double get_r() const {return rok;};

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
