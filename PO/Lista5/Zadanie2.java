// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Dzia³ania arytmetyczne
// Zadanie2.class
// Zadanie2.java
// 2018-03-29

import java.io.IOException;

// Main
public class Zadanie2
{
  public static void main(String[] args)
  {
    Zadanie2 start = new Zadanie2();
    start.start();

  }

  public void start()
  {

    Wyrazenie nowy = new Wyrazenie();
    int wybor=1;
    while(wybor != 0)
    {
      System.out.print("Wybierz, co chcesz zrobic\n");
      System.out.print("1.Dodaj\n");
      System.out.print("2.Odejmij\n");
      System.out.print("3.Pomnoz\n");
      System.out.print("4.Podziel\n");
      System.out.print("0.Wyjscie\n");
      try
      {
        wybor = System.in.read();
      }
      catch(IOException ex)
      {
        System.out.println (ex.toString());
        System.out.print("Podaj liczbe!\n");
      }
      switch(wybor)
      {
        case 0: break;
        case 1: nowy = new Dodaj( new Lisc(4), new Lisc(2));
                System.out.print(nowy.wynik + "\n");
                break;
        case 2: nowy = new Odejmij( new Lisc(4), new Lisc(2));
                System.out.print(nowy.wynik + "\n");
                break;
        case 3: nowy = new Pomnoz( new Lisc(4), new Lisc(2));
                System.out.print(nowy.wynik + "\n");
                break;
        case 4: nowy = new Podziel( new Lisc(4), new Lisc(2));
                System.out.print(nowy.wynik + "\n");
                break;
        default: System.out.print("Bledne dane\n");
                 break;
      }
      System.out.print("\n");
    }




  }

  // Klasa Wyrazenie - przechowuje ci¹gi do obliczenia
  public class Wyrazenie
  {

    public int wynik;
    public int stala;

  }

  public class Dodaj extends Wyrazenie
  {
    public Dodaj(Lisc a, Lisc b)
    {
      wynik = a.stala + b.stala;
    }
  }

  public class Odejmij extends Wyrazenie
  {
    public Odejmij(Lisc a, Lisc b)
    {
      wynik = a.stala - b.stala;
    }
  }

  public class Pomnoz extends Wyrazenie
  {
    public Pomnoz(Lisc a, Lisc b)
    {
      wynik = a.stala * b.stala;
    }

  }

  public class Podziel extends Wyrazenie
  {
    public Podziel(Lisc a, Lisc b)
    {
      wynik = a.stala / b.stala;
    }
  }


  // Klasa Lisc - przechowuje sta³e i zmienne
  public class Lisc extends Wyrazenie
  {

    public Lisc(int st)
    {
      stala = st;
    }
    public Lisc(char zm)
    {
      stala = zm;
    }
  }
}
