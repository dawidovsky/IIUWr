//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z2, Stworzenie s³ownika
//S³ownik.exe
//S³ownik.cs
//2018-03-15

using System;

namespace S³ownik
{
  class test
  {
    static void Main()
    {
      S³ownik<int, string> s³ownik = new S³ownik<int, string>();
      int stan = 1;
      Console.WriteLine("Wybierz co chcesz zrobiæ:");
      Console.WriteLine("1.Dodaj element");
      Console.WriteLine("2.Usuñ element");
      Console.WriteLine("3.Wypisz elementy s³ownika");
      Console.WriteLine("4.Szukaj elementu");
      Console.WriteLine("5.Wyjœcie");
      while(stan == 1)
      {
        string wybór = Console.ReadLine();
        switch (wybór)
        {
          case "1":
          {
            Console.WriteLine("Podaj klucz(miejsce/numer w s³owniku) elementu");
            int miejsce = Int32.Parse(Console.ReadLine());
            Console.WriteLine("Podaj wartoœæ elementu:");
            string napis = Console.ReadLine();
            s³ownik.Dodaj(miejsce, napis);
            break;
          }
          case "2":
          {
            Console.WriteLine("Podaj numer elementu do usuniêcia");
            int miejsce = Int32.Parse(Console.ReadLine());
            s³ownik.Usuñ(miejsce);
            break;
          }
          case "3":
          {
            s³ownik.Wypisz();
            break;
          }
          case "4":
          {
            Console.WriteLine("Podaj klucz(numer) elementu:");
            int miejsce = Int32.Parse(Console.ReadLine());
            s³ownik.Szukaj(miejsce);
            break;
          }
          case "5":
          {
            stan = 0;
            break;
          }
          default:
          {
            System.Console.WriteLine("B³êdny wybór");
            break;
          }
        }
      }
    }
  }
}
