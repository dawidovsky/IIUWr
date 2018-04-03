// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Stala.java
// 2018-03-29

// ob�uga sta�ych
public class Stala implements Wyrazenie
{
  
  int val; // warto�� sta�ej

  // konstruktor sta�ej
  public Stala(int x)
  {
     val = x;
  }

  // obliczanie sta�ej - zwracanie jej warto�ci
  public int Oblicz()
  {
    return val;
  }

  // �adne wypisanie sta�ej
  public String toString()
  {
    return " " + val + " ";
  }
}
