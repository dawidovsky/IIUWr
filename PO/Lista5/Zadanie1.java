// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna kolekcja
// Zadanie1
// Zadanie1.java
// 2018-03-29

import java.util.Collections;
import java.util.Scanner;

// Main
public class Zadanie1
{
  public static void main(String[] args)
  {
    Zadanie1 start = new Zadanie1();
    start.start();
  }

  public void start()
  {
    Lista<Integer> lista = new Lista<Integer>();
    Scanner s = new Scanner(System.in);
    int wybor=5, stan=1, liczba = 0;
    while(stan != 0)
    {
      System.out.print("\nWybierz, co chcesz zrobic:\n");
      System.out.print("1.Dodaj liczbe do listy\n");
      System.out.print("2.Wyjmij element z listy\n");
      System.out.print("3.Wypisz liste\n");
      System.out.print("4.Wyjscie\n\n");
      wybor = s.nextInt();

      switch(wybor)
      {
        case 1: System.out.print("Podaj liczbe\n");
        liczba = s.nextInt();
        lista.Dodaj(liczba);
        break;

        case 2:
        try
        {
          liczba = lista.Pobierz();
        }
        catch(NullPointerException err)
        {
          System.out.print("Lista Pusta\n");
          break;
        }

        System.out.print("Wyjeto element " + liczba + "\n");
        break;

        case 3: lista.Wypisz();
        break;

        case 4: stan = 0;
        break;

        default:
        System.out.println("Bledne dane");
        break;
      }
    }
  }

  public class Lista<T extends Comparable>
  {
    private Lista<T> pierwszy;
    private Lista<T> next;
    private T wartosc;

    // Dodawanie elementu do listy w odpowiednie miejsce
    public void Dodaj(T a)
    {
      if(pierwszy == null)
      {
        pierwszy = new Lista<T>();
        pierwszy.wartosc = a;
        pierwszy.next = null;
      }
      else
      {
        if(pierwszy.wartosc.compareTo(a) > 0)
        {
          Lista<T> nowy = new Lista<T>();
          nowy.wartosc = pierwszy.wartosc;
          pierwszy.wartosc = a;
          nowy.next = pierwszy.next;
          pierwszy.next = nowy;
        }
        else
        {
          Lista<T> wsk = pierwszy;
          while(wsk.next != null)
          {
            if(wsk.next.wartosc.compareTo(a) > 0)
              break;
            wsk = wsk.next;
          }
          Lista<T> nowy = new Lista<T>();
          nowy.wartosc = a;
          nowy.next = wsk.next;
          wsk.next = nowy;
        }
      }
    }

    // Pobieranie peirwszego elementu i usuwanie go
    public T Pobierz()
    {
      T war = pierwszy.wartosc;
      if(pierwszy.next != null)
      {
        pierwszy = pierwszy.next;
      }
      else
        pierwszy = null;
      return war;
    }

    // Wypisaywanie zawartoœci listy
    public void Wypisz()
    {
      if(pierwszy == null)
      {
          System.out.print("Lista jest pusta!");
          return;

      }
      Lista<T> temp = pierwszy;
      System.out.print("Lista zawiera:\n");
      while (temp != null)
      {
          System.out.print(temp.wartosc + "\n");
          temp = temp.next;
      }
    }
  }
}
