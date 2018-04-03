// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna hierarchia klas
// Figury
// Prostokat.java
// 2018-03-29

// klasa przechowuj�ca prostok�ty
public class Prostokat extends Figury
{
  
  double dlugosc;
  double szerokosc;
  double pole;
  double obwod;

  public Prostokat(double a, double b)
  {
    dlugosc = a;
    szerokosc = b;
  }

  @Override
  public double pole()
  {
    return dlugosc * szerokosc;
  }

  @Override
  public double obwod()
  {
    return 2 * dlugosc + 2 * szerokosc;
  }

  @Override
  public String toString()
  {
    String str = "Prostokat: dlugosc: " + dlugosc + " szerokosc: " + szerokosc;
    str = str +" obwod: " + obwod() + " pole: " + pole();
    return str;
  }
}
