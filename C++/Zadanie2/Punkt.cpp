#include "Punkt.hpp"

Punkt::Punkt(const double x,const double y) : x(x), y(y) {}
Punkt::Punkt(const Punkt &pkt,const Wektor &wkt): x(pkt.x + wkt.dx), y(pkt.y + wkt.dy) {}
Punkt::Punkt(const Punkt &punkt) : x(punkt.x), y(punkt.y) {}

std::ostream& operator<<(std::ostream& str, const Punkt& A)
{
	return str << "(" << A.x <<","<<A.y<<")";
}
