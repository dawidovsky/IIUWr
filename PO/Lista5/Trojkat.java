// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna hierarchia klas
// Figury
// Trojkat.java
// 2018-03-29

public class Trojkat extends Figury
{
  double podstawa;
  double bok1;
  double bok2;
  double wysokosc;

  public Trojkat(double a, double b , double c, double h)
  {
    podstawa = a;
    bok1 = b;
    bok2 = c;
    wysokosc = h;
  }

  @Override
  public double pole()
  {
    return podstawa * wysokosc / 2;
  }

  @Override
  public double obwod()
  {
    return podstawa + bok1 + bok2;
  }

  @Override
  public String toString()
  {
    String str = "Trojkat: podstawa: " + podstawa + " wysokosc: " + wysokosc;
    str = str +" pole: " + pole();
    return  str;
  }
}
