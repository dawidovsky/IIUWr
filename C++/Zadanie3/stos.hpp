#include <iostream>
#include <initializer_list>

using namespace std;

class Stos
{
  private:
    int pojemnosc;
    int ile=0;

  public:
    double get_ile() const {return ile;};
    double get_poj() const {return pojemnosc;};
    void set_ile(int n) {ile = n;};

    string *stos = new string[pojemnosc];

    ~Stos();

    Stos();
    Stos(const int &poj);
    Stos(const Stos &stos);
    Stos(const Stos && elem);
    Stos(initializer_list<string> list);

    Stos & operator =(const Stos && elem);
    Stos & operator =(const Stos &);

    void wloz(const string &str);
    string sciagnij();
    string sprawdz();
    int rozmiar();

};
