// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Zmienna.java
// 2018-03-29

import java.util.Hashtable;

// ob�uga zmiennych
public class Zmienna implements Wyrazenie
{
  
  String s;
  Hashtable<String, Integer> Args;

  // konstruktor zmiennej
  public Zmienna(String s, Hashtable<String, Integer> l)
  {
    this.s = s; this.Args = l;
  }

  // obliczanie warto�ci zmiennej
  // wypisuje warto�� przypisan� do stringa s
  public int Oblicz()
  {
    return Args.get(s);
  }

  // �adne wypisanie zmiennej
  public String toString()
  {
    return " " + s + " ";
  }
}
