#include <ostream>

class Wektor
{
  public:
    const double dx=0.0;
    const double dy=0.0;
    Wektor() = default;
    Wektor(const Wektor &wektor);
    Wektor(const double dx,const double dy);
    Wektor& operator = (const &Wektor) = delete;
};

std::ostream& operator<<(std::ostream &str, const Wektor&A);
Wektor skladanieWektorow(const Wektor &wkt1, const Wektor &wkt2);
