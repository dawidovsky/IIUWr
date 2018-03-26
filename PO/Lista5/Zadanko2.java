// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Zadanie2.java
// 2018-03-29

import java.util.*;

public class Zadanko2
{

  public static void main(String[] args)
  {
    Zadanko2 start = new Zadanko2();
    start.start();

  }

  public void start()
  {

    Wyrazenie x = new Stala(20);
    Wyrazenie y = new Stala(10);

    Operator plus = new Operator()
    {
      int oblicz(int x, int y)
      {
        return x + y;
      }
    };

    Operator minus = new Operator()
    {
      int oblicz(int x, int y)
      {
        return x - y;
      }
    };

    Operator mnoz = new Operator()
    {
      int oblicz(int x, int y)
      {
        return x * y;
      }
    };

    Operator dziel = new Operator()
    {
      int oblicz(int x, int y)
      {
        return x / y;
      }
    };

    Wyrazenie xplusy = new Dzialanie(x, plus, y);
    System.out.println(xplusy.oblicz()); // 30
  }

  public interface Wyrazenie
   {
    public int oblicz();
  }

  public interface Operator
  {
    public int oblicz(int x, int y);
  }

  public class Dzialanie implements Wyrazenie
  {
    private Wyrazenie lewe;
    private Wyrazenie prawe;
    private Operator operator;

    public Dzialanie(Wyrazenie lewe, Operator operator, Wyrazenie prawe)
    {
      this.lewe = lewe;
      this.prawe = prawe;
      this.operator = operator;
    }

      public int oblicz()
      {
        return operator.oblicz(lewe.oblicz(), prawe.oblicz());
      }
  }

  public class Stala implements Wyrazenie
  {
    private int wartosc;

    public Stala(int wartosc)
    {
      this.wartosc = wartosc;
    }

    public int oblicz()
    {
      return wartosc;
    }
  }

  // public class Zmienna implements Wyrazenie
  // {
  //     private String nazwa;
  //     private Hashtable<String, Integer> kontekst;
  //
  //     public Zmienna(String nazwa, Hashtable<String, Integer> kontekst) {
  //         this.nazwa = nazwa;
  //         this.kontekst = kontekst;
  //     }
  //
  //     public int oblicz() {
  //         return kontekst.get(nazwa);
  //     }
  // }

}
