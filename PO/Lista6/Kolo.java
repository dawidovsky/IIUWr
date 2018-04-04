// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L6, z1, Kolekcja 'Serializable'
// Figury
// Kolo.java
// 2018-04-05

import java.io.*;

// klasa przechowuj¹ca ko³o
public class Kolo extends Figury implements Serializable
{

  double promien;

  public Kolo(double r)
  {
    promien = r;
  }

  @Override
  public double pole()
  {
    return promien * promien * 3.14159265359;
  }

  @Override
  public double obwod()
  {
    return 2 * promien * 3.14159265359;
  }

  @Override
  public String toString()
  {
    String str = "Kolo: promien: " + promien ;
    str = str +" obwod: " + obwod() + " pole: " + pole();
    return str;
  }
}
