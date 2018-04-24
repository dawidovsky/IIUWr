#include <iostream>
#include <climits>

using namespace std;

namespace obliczenia
{
  class Wymierna
  {
    private:
      int licz;
      int mian;

    public:
      int get_l() const {return licz;};
      int get_m() const {return mian;};
      void set_l(int x) {licz = x;};
      void set_m(int x) {mian = x;};
      Wymierna(int, int);
      Wymierna(int);
      Wymierna(const Wymierna &) = default;
      Wymierna & operator = (const Wymierna &) = default;
      friend ostream & operator << (ostream & wy, const Wymierna & x)
      {
        return wy << (double) x.get_l() / x.get_m();
      };

      Skroc();
      int Skroc(int64_t, int64_t);
      NWD(int, int);
      NWW(int, int);

      Wymierna & operator + (const Wymierna &);
      Wymierna & operator - (const Wymierna &);
      Wymierna & operator * (const Wymierna &);
      Wymierna & operator / (const Wymierna &);

      Wymierna operator ! ();
      Wymierna operator - ();

      operator double();
      explicit operator int();
  };
}

class Bledy : public exception
{
  protected:
    string tresc;
  public:
    Bledy() = default;
};

class NieDzielPrzezZero : public Bledy
{
  public:
    NieDzielPrzezZero() = default;
    NieDzielPrzezZero(const char* t);
    NieDzielPrzezZero(const NieDzielPrzezZero &c) = default;
    NieDzielPrzezZero & operator = (const NieDzielPrzezZero &tb) = default;
    virtual const char* what();
    virtual ~NieDzielPrzezZero() = default;
};

class PrzekroczonoZakres : public Bledy
{
  public:
    PrzekroczonoZakres() = default;
    PrzekroczonoZakres(const char* t);
    PrzekroczonoZakres(const PrzekroczonoZakres &c) = default;
    PrzekroczonoZakres & operator = (const PrzekroczonoZakres &tb) = default;
    virtual const char* what();
    virtual ~PrzekroczonoZakres() = default;
};
