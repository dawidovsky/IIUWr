// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Stala.java
// 2018-03-29

// ob³uga sta³ych
public class Stala implements Wyrazenie
{
  int val; // wartoœæ sta³ej

  // konstruktor sta³ej
  public Stala(int x)
  {
     val = x;
  }

  // obliczanie sta³ej - zwracanie jej wartoœci
  public int Oblicz()
  {
    return val;
  }

  // £adne wypisanie sta³ej
  public String toString()
  {
    return " " + val + " ";
  }
}
