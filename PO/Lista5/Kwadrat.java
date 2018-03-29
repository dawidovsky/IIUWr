// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna hierarchia klas
// Figury
// Kwadrat.java
// 2018-03-29

public class Kwadrat extends Figury
{
  double dlugosc_boku;

  public Kwadrat(double a)
  {
    dlugosc_boku = a;
  }

  @Override
  public double pole()
  {
    return dlugosc_boku * dlugosc_boku;
  }

  @Override
  public double obwod()
  {
    return 4 * dlugosc_boku;
  }

  @Override
  public String toString()
  {
    String str = "Kwadrat: dlugosc boku: " + dlugosc_boku ;
    str = str +" obwod: " + obwod() + " pole: " + pole();
    return str;
  }
}
