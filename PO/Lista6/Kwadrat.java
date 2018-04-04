// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L6, z1, Kolekcja 'Serializable'
// Figury
// Kwadrat.java
// 2018-04-05

import java.io.*;

// klasa przechowuj¹ca kwadraty
public class Kwadrat extends Figury implements Serializable
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
