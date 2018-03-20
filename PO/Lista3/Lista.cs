//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z1, Stworzenie Listy
//Lista.exe
//Lista.cs
//2018-03-15

using System;

namespace Lista
{
  class menu
  {
    static void Main()
    {
      Lista<int> lista = new Lista<int>();
      string opcja = "1";
      while(opcja != "7")
      {
        Console.WriteLine("");
        Console.WriteLine("Wybierz co chcesz zrobi�:");
        Console.WriteLine("1.Dodaj element na pocz�tek");
        Console.WriteLine("2.Usu� element z pocz�tku");
        Console.WriteLine("3.Dodaj element na koniec");
        Console.WriteLine("4.Usu� element z ko�ca");
        Console.WriteLine("5.Sprawd� czy lista jest pusta");
        Console.WriteLine("6.Wypisz elementy listy");
        Console.WriteLine("7.Wyj�cie");
        opcja = Console.ReadLine();
        switch (opcja)
        {
          case "1":
          {
            Console.WriteLine("Podaj liczbe wstawian� na pocz�tek listy");
            int liczba = Int32.Parse(Console.ReadLine());
            lista.DodajPocz�tek(liczba);
            break;
          }
          case "2":
          {
            int usuni�ta = lista.Usu�Pocz�tek();
            if(usuni�ta != 0)
              Console.WriteLine("Usuni�to " + usuni�ta + " z listy");
            break;
          }
          case "3":
          {
            Console.WriteLine("Podaj liczbe wstawian� na koniec listy");
            int liczba = Int32.Parse(Console.ReadLine());
            lista.DodajKoniec(liczba);
            break;
          }
          case "4":
          {
            int usuni�ta = lista.Usu�Koniec();
            if(usuni�ta != 0)
              Console.WriteLine("Usuni�to " + usuni�ta + " z listy");
            break;
          }
          case "5":
          {
            if(lista.Pusta())
              Console.WriteLine("Lista jest pusta");
            else
              Console.WriteLine("Lista zawiera jakie� elementy");
              break;
          }
          case "6":
          {
            lista.Wypisz();
            Console.WriteLine("");
            lista.WP();
            lista.WO();
            break;
          }
          case "7":
          {
            break;
          }
          default:
          {
            System.Console.WriteLine("B��dny wyb�r");
            break;
          }
        }
      }
    }
  }
}
