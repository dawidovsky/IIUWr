//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z2, Stworzenie s這wnika
//S這wnik.exe
//S這wnik.cs
//2018-03-15

using System;

namespace S這wnik
{
  class test
  {
    static void Main()
    {
      S這wnik<int, string> s這wnik = new S這wnik<int, string>();
      int stan = 1;
      Console.WriteLine("Wybierz co chcesz zrobi�:");
      Console.WriteLine("1.Dodaj element");
      Console.WriteLine("2.Usu� element");
      Console.WriteLine("3.Wypisz elementy s這wnika");
      Console.WriteLine("4.Szukaj elementu");
      Console.WriteLine("5.Wyj�cie");
      while(stan == 1)
      {
        string wyb鏎 = Console.ReadLine();
        switch (wyb鏎)
        {
          case "1":
          {
            Console.WriteLine("Podaj klucz(miejsce/numer w s這wniku) elementu");
            int miejsce = Int32.Parse(Console.ReadLine());
            Console.WriteLine("Podaj warto�� elementu:");
            string napis = Console.ReadLine();
            s這wnik.Dodaj(miejsce, napis);
            break;
          }
          case "2":
          {
            Console.WriteLine("Podaj numer elementu do usuni璚ia");
            int miejsce = Int32.Parse(Console.ReadLine());
            s這wnik.Usu�(miejsce);
            break;
          }
          case "3":
          {
            s這wnik.Wypisz();
            break;
          }
          case "4":
          {
            Console.WriteLine("Podaj klucz(numer) elementu:");
            int miejsce = Int32.Parse(Console.ReadLine());
            s這wnik.Szukaj(miejsce);
            break;
          }
          case "5":
          {
            stan = 0;
            break;
          }
          default:
          {
            System.Console.WriteLine("B喚dny wyb鏎");
            break;
          }
        }
      }
    }
  }
}
