#include <iostream>
#include <ostream>
#include <stdexcept>
#include <cmath>
#include "Punkt.hpp"

using namespace std;

class Prosta
{
  private:
    double a;
    double b;
    double c;
  public:
    double get_a() const {return a;};
    double get_b() const {return b;};
    double get_c() const {return c;};

    Prosta();
    Prosta(const Punkt& A, const Punkt& B);
    Prosta(const Wektor& wkt);
    Prosta(const double ws_a , const double ws_b, const double ws_c);
    Prosta(const Prosta &prs, const Wektor &wkt);

    Prosta(const Prosta&) = delete;

    string czyWektorProstopadly(const Wektor& wkt);
    string czyWektorRownolegly(const Wektor& wkt);
    string czyPunktProsta(const Punkt &pkt);

    void normalize();
};

std::ostream& operator<<(std::ostream& str, const Prosta&A);

string czyProstopadle(const Prosta& prs1, const Prosta &prs2);
string czyRownolegle(const Prosta &prs1, const Prosta &prs2);
Punkt punktPrzeciecia(const Prosta& prs1, const Prosta& prs2);
