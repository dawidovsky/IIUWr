#include "Wektor.hpp"

Wektor::Wektor(const double dx, const double dy) : dx(dx), dy(dy){}
Wektor::Wektor(const Wektor &wektor) : dx(wektor.dx), dy(wektor.dy){}

Wektor skladanieWektorow(const Wektor &wkt1,const Wektor &wkt2)
{
  return Wektor(wkt1.dx + wkt2.dx, wkt1.dy + wkt2.dy);
}

std::ostream& operator<<(std::ostream &str , const Wektor&A)
{
  return str << "[" << A.dx << "," << A.dy << "]" ;
}
