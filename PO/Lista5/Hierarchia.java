// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna hierarchia klas
// Hierarchia
// Hierarchia.java
// 2018-03-29

public class Hierarchia
{
  public static void main(String[] args)
  {
    Hierarchia start = new Hierarchia();
    start.start();
  }

  public void start()
  {
    Kwadrat kwa = new Kwadrat(4);
    Kwadrat kwaw2 = new Kwadrat(6);
    if(kwa.compareTo(kwaw2) > 0) System.out.print("pierwszy");
    else System.out.print("drugi");
  }

  public class Kwadrat implements Comparable<Kwadrat>
  {
    double dlugosc_boku;
    double pole;
    double obwod;

    public Kwadrat(double a)
    {
      dlugosc_boku = a;
      pole = a * a;
      obwod = 4 * a;
    }

    @Override
    public int compareTo(Kwadrat o)
    {
      if(this.pole == o.pole)
        return 0;
      if(this.pole > o.pole)
        return 1;
      return -1;
    }
  }

  public class Prostokat implements Comparable<Prostokat>
  {
    double dlugosc;
    double szerokosc;
    double pole;
    double obwod;

    public Prostokat(double a, double b)
    {
      dlugosc = a;
      szerokosc = b;
      pole = a * b;
      obwod = 2 * a + 2 * b;
    }

    @Override
    public int compareTo(Prostokat o)
    {
      if(this.pole == o.pole)
        return 0;
      if(this.pole > o.pole)
        return 1;
      return -1;
    }
  }

  public class Trojkat implements Comparable<Trojkat>
  {
    double podstawa;
    double wysokosc;
    double pole;

    public Trojkat(double a, double h)
    {
      podstawa = a;
      wysokosc = h;
      pole = a * h;
    }

    @Override
    public int compareTo(Trojkat o)
    {
      if(this.pole == o.pole)
        return 0;
      if(this.pole > o.pole)
        return 1;
      return -1;
    }
  }

  public class Kolo implements Comparable<Kolo>
  {
    double promien;
    double obwod;
    double pole;

    public Kolo(double r)
    {
      promien = r;
      obwod = 2 * r * 3.14159265359;
      pole = r * r * 3.14159265359;
    }

    @Override
    public int compareTo(Kolo o)
    {
      if(this.pole == o.pole)
        return 0;
      if(this.pole > o.pole)
        return 1;
      return -1;
    }
  }
}
