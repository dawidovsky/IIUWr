#include <iostream>
#include <ostream>
#include <cmath>
#include <initializer_list>

using namespace std;

class tab_bit
{
  private:
    typedef uint64_t slowo; // komorka w tablicy
    class ref
    {
      public:
        bool Get_bit(uint64_t * tab, int bitindex);
        void Set_bit(uint64_t * tab, int bitindex, bool val);
        uint64_t &Get_wsk(uint64_t *tab,int i);
    }; // klasa pomocnicza do adresowania bitów

    friend istream & operator >> (istream &we, tab_bit &tb);
    friend ostream & operator << (ostream &wy, const tab_bit &tb);

  protected:
    slowo *tab; // tablica bitów
    int dl; // liczba bitów

  public:
    explicit tab_bit (int rozm); // wyzerowana tablica bitow [0...rozm]
    explicit tab_bit (slowo tb); // tablica bitów [0...rozmiarSlowa]
    explicit tab_bit (initializer_list<bool> list);

    tab_bit (const tab_bit &tb); // konstruktor kopiujący
    tab_bit (tab_bit &&tb); // konstruktor przenoszący
    tab_bit & operator = (const tab_bit &tb); // przypisanie kopiujące
    tab_bit & operator = (tab_bit &&tb); // przypisanie przenoszące

    ~tab_bit (); // destruktor

  private:
    bool czytaj (int i) const; // metoda pomocnicza do odczytu bitu
    void pisz (int i, bool b); // metoda pomocnicza do zapisu bitu

  public:
    bool operator[] (int i) const; // indeksowanie dla stałych tablic bitowych
    uint64_t& operator[] (int i); // indeksowanie dla zwykłych tablic bitowych
    friend tab_bit operator | (const tab_bit &u, const tab_bit &v);
    friend tab_bit operator & (const tab_bit &u, const tab_bit &v);
    friend tab_bit operator ^ (const tab_bit &u, const tab_bit &v);
    tab_bit& operator |= (const tab_bit &v);
    tab_bit& operator &= (const tab_bit &v);
    tab_bit& operator ^= (const tab_bit &v);
    tab_bit operator ! ();
    // operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
};
