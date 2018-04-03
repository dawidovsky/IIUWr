// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna hierarchia klas
// Figury
// Kolo.java
// 2018-03-29

// klasa przechowuj�ca ko�a
public class Kolo extends Figury
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
