//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z2, Stworzenie s�ownika
//S�ownik.exe
//S�ownik.cs
//2018-03-15

using System;

namespace S�ownik
{
  class test
  {
    static void Main()
    {
      S�ownik<int, string> s�ownik = new S�ownik<int, string>();
      int stan = 1;
      Console.WriteLine("Wybierz co chcesz zrobi�:");
      Console.WriteLine("1.Dodaj element");
      Console.WriteLine("2.Usu� element");
      Console.WriteLine("3.Wypisz elementy s�ownika");
      Console.WriteLine("4.Szukaj elementu");
      Console.WriteLine("5.Wyj�cie");
      while(stan == 1)
      {
        string wyb�r = Console.ReadLine();
        switch (wyb�r)
        {
          case "1":
          {
            Console.WriteLine("Podaj klucz(miejsce/numer w s�owniku) elementu");
            int miejsce = Int32.Parse(Console.ReadLine());
            Console.WriteLine("Podaj warto�� elementu:");
            string napis = Console.ReadLine();
            s�ownik.Dodaj(miejsce, napis);
            break;
          }
          case "2":
          {
            Console.WriteLine("Podaj numer elementu do usuni�cia");
            int miejsce = Int32.Parse(Console.ReadLine());
            s�ownik.Usu�(miejsce);
            break;
          }
          case "3":
          {
            s�ownik.Wypisz();
            break;
          }
          case "4":
          {
            Console.WriteLine("Podaj klucz(numer) elementu:");
            int miejsce = Int32.Parse(Console.ReadLine());
            s�ownik.Szukaj(miejsce);
            break;
          }
          case "5":
          {
            stan = 0;
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
