#include "Wektor.hpp"
#include <ostream>
class Punkt
{
  public:
   const double x=0.0;
   const double y=0.0;
   Punkt() = default;
   Punkt(const Punkt &punkt);
   Punkt(const double x, const double y);
   Punkt(const Punkt& pkt, const Wektor& wkt);
   Punkt& operator = (const Punkt&) = delete;
};

std::ostream& operator<<(std::ostream& str, const Punkt& A);
