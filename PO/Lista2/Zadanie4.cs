/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 08.03.2018r
Lista 2 Zadanie 4
Uruchamiamy program i  obsługujemy go poprzez zaimplementowane menu
Język C# - kompilator csc 4.7.2556.0*/

using System;
using System.Collections.Generic;

class ListaLeniwa
{
  List<int> list = new List<int>();
  Random rnd = new Random();
  virtual public int element(int elem)
  {
    if(list.Count > elem-1)
    {
        return list[elem-1];
    }
    else
    {
      for(int i=0; i<elem; i++)
      {
        if(list.Count <= i)
        {
          int liczba = rnd.Next(0,10000);
          list.Add(liczba);
        }
      }
      return list[elem-1];
    }
  }
  public int size()
  {
    return list.Count;
  }
  static void Main()
  {
    int stan = 1;
    System.Console.WriteLine("Wybierz co chcesz zrobic:");
    System.Console.WriteLine("1.Wypisz element z listy");
    System.Console.WriteLine("2.Wyswietl wielkosc listy");
    System.Console.WriteLine("3.Wypisz element z listy liczb pierwszych");
    System.Console.WriteLine("4.Wyjscie");
    ListaLeniwa lista = new ListaLeniwa();
    Pierwsze listaprime = new Pierwsze();
    while(stan == 1)
    {
      string wybor = System.Console.ReadLine();
      switch (wybor)
      {
        case "1":
        {
          System.Console.WriteLine("Wpisz indeks elementu");
          int indeks = Int32.Parse(System.Console.ReadLine());
          System.Console.WriteLine("Element o indeksie " + indeks + " zawiera "
           + lista.element(indeks));
          break;
        }
        case "2":
        {
            System.Console.WriteLine("Wielkosc listy wynosi " + lista.size());
            break;
        }
        case "3":
        {
          System.Console.WriteLine("Wpisz indeks elementu");
          int indeks = Int32.Parse(System.Console.ReadLine());
          System.Console.WriteLine("Element o indeksie " + indeks + " zawiera "
           + listaprime.element(indeks));
          break;
        }
        case "4":
        {
          stan = 0;
          break;
        }
        default:
        {
          System.Console.WriteLine("Bledny wybor");
          break;
        }
      }
    }
  }
}

class Pierwsze : ListaLeniwa
{
  List<int> primelist = new List<int>();
  private int prime = 2;
  override public int element(int elem)
  {
    if(primelist.Count > elem-1)
    {
        return primelist[elem-1];
    }
    int iter = elem;
    while(iter != 0)
    {
      bool czyZnalazlo = false;
      for(int i = 2; i <= System.Math.Sqrt(prime); i++)
      {
        if(prime%i == 0)
        {
          czyZnalazlo = true;
          break;
        }
      }
      if(czyZnalazlo == true)
        prime++;
      else
        {
          primelist.Add(prime);
          prime++;
          iter--;
        }
    }
    return primelist[elem-1];
  }
}
