// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Stala.java
// 2018-03-29

public class Stala implements Wyrazenie
{
  int val; // warto쒏 sta쿮j

  // konstruktor sta쿮j
  public Stala(int x)
  {
     val = x;
  }

  // obliczanie sta쿮j - zwracanie jej warto쐁i
  public int Oblicz()
  {
    return val;
  }

  // 즑dne wypisanie sta쿮j
  public String toString()
  {
    return " " + val + " ";
  }
}
