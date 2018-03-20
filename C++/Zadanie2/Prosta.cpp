#include "Prosta.hpp"

std::ostream& operator<<(std::ostream& str, const Prosta&A)
{
  return str << A.get_a() << "x + " << A.get_b() << "y + " << A.get_c() << " = 0";
}

Prosta::Prosta()
{
  this->a = 1;
  this->b = 1;
  this->c = 1;
}

void Prosta::normalize()
{
  double len = sqrt(this->a * this->a + this->b * this->b);
  this->a /= len;
  this->b /= len;
  this->c /= len;
}

Prosta::Prosta(const Punkt& A,const Punkt& B)
{
  if (A.x == B.x && A.y == B.y)
    throw invalid_argument("Nie mozna jednoznacznie utworzyc prostej\n");
	this->a = (B.y - A.y);
	this->b = (A.x - B.x);
	this->c = (A.y*B.x - A.x*B.y);
//  normalize();
}

Prosta::Prosta(const Wektor &wkt)
{
  if (wkt.dx == 0 && wkt.dy == 0)
      throw invalid_argument("Nie mozna utworzyc prostej gdy mamy wektor zerowy!\n");
  this->a = wkt.dx;
  this->b = wkt.dy;
  this->c = -1*(wkt.dx*wkt.dx + wkt.dy*wkt.dy);
  //normalize();
}

Prosta::Prosta(const double ws_a , const double ws_b, const double ws_c)
{
  if(ws_a == ws_b && ws_a == 0)
      throw invalid_argument("Nie mozna utworzyc prostej gdy A i B rowne zeru!\n");
  this->a = ws_a;
  this->b = ws_b;
  this->c = ws_c;
  //normalize();
}

Prosta::Prosta(const Prosta &prs,const Wektor &wkt)
{
  this->a = prs.get_a();
  this->b = prs.get_b();
  this->c = prs.get_c() - (wkt.dy - prs.get_a() * wkt.dx);
  //normalize();
}

string Prosta::czyWektorProstopadly(const Wektor &wkt)
{
  if(a * (wkt.dy / b) == wkt.dx && b * (wkt.dy / b) == wkt.dy)
    return "TAK";
  return "NIE";
}

string Prosta::czyWektorRownolegly(const Wektor &wkt)
{
  if(a == (wkt.dy / wkt.dx))
    return "TAK";
  return "NIE";

}

string Prosta::czyPunktProsta(const Punkt &pkt)
{
  if(a * pkt.x + b * pkt.y + c == 0)
    return "TAK";
  return "NIE";
}

string czyProstopadle(const Prosta &prs1, const Prosta &prs2)
{
  if(prs1.get_a() * prs2.get_a() == -1)
    return "TAK";
  return "NIE";
}

string czyRownolegle(const Prosta &prs1, const Prosta &prs2)
{
  if(prs1.get_a() == prs2.get_a())
    return "TAK";
  return "NIE";
}

Punkt punktPrzeciecia(const Prosta &prs1, const Prosta &prs2)
{
  double wynik = prs1.get_a()* prs2.get_b() - prs2.get_a() * prs1.get_b();
  if(wynik == 0) throw invalid_argument("Nie mozna obliczyc punktu przeciecia prostych rownoleglych!\n");
  double x = (-prs1.get_c() * prs2.get_b() - (-prs2.get_c())*prs1.get_b())/wynik;
  double y = (prs1.get_a()*(-prs2.get_c())-prs2.get_a()*(-prs1.get_c()))/wynik;
  return Punkt(x,y);
}
