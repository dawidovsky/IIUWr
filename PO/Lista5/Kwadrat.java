// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna hierarchia klas
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
    return "bok: " + dlugosc_boku + " pole: " + pole() +" obwod: " + obwod();
  }
}
