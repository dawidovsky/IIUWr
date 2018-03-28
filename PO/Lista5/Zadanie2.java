// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Zadanie2.java
// 2018-03-29

import java.util.Hashtable;

public class Zadanie2
{

  public static void main(String[] args)
  {
    Hashtable<String, Integer> Args = new Hashtable<String, Integer>();
    try
    {
      Args.put("x",2);
      Wyrazenie zmienna = new Dodaj(new Stala(2), new Zmienna("x", Args));
      System.out.println(zmienna.toString() + " = " + zmienna.Oblicz());

      Args.put("y",8);
      Wyrazenie zag = new Pomnoz(new Stala(4), new Stala(5));
      zag = new Dodaj(new Zmienna("y",Args), zag);
      System.out.println(zag.toString() + " = " + zag.Oblicz());

      Wyrazenie odj = new Odejmij(new Stala(2), new Stala(4));
      System.out.println(odj.toString() + " = " + odj.Oblicz());

      Wyrazenie dzi = new Podziel(new Stala(8), new Stala(4));
      System.out.println(dzi.toString() + " = " + dzi.Oblicz());

      Wyrazenie zero = new Podziel(new Stala(4), new Stala(0));
      System.out.println(zero.toString() + " = " + zero.Oblicz());
    }
    catch(ArithmeticException err)
    {
      System.out.print("Bledne wyrazenie" );
    }
  }
}
