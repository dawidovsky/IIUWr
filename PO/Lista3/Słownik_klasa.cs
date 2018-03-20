//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z2, Stworzenie s³ownika
//S³ownik.exe
//S³ownik_klasa.cs
//2018-03-15

using System;

namespace S³ownik
{
  public class S³ownik<K,V>
    where K : IComparable<K>
  {
    public S³ownik<K,V> elem;
    public K klucz;
    public V wartoœæ;

  //Dodaje wartoœæ do s³ownika o zadanym kluczu
    public void Dodaj(K klucz, V war)
    {
        if (this.elem != null)
        {
          if(klucz.CompareTo(this.elem.klucz) == 0)
            {
              Console.WriteLine("Element o takim indeksie juz istnieje!");
              return;
            }
          this.elem.Dodaj(klucz, war);
        }
        else
        {
            this.elem = new S³ownik<K,V>();
            this.elem.klucz = klucz;
            this.elem.wartoœæ = war;
            Console.WriteLine("Dodano " + war + " na miejsce " + klucz);
        }
    }

  //Wypisuje elementy s³ownika
    public void Wypisz()
    {
        if (this.elem != null)
        {
            Console.WriteLine(this.elem.klucz + " " + this.elem.wartoœæ);
            this.elem.Wypisz();
        }
    }

  // Usuwa element ze s³ownika o zadanym kluczu
    public void Usuñ(K klucz)
    {
      if(this.elem != null)
      {
        if (klucz.CompareTo(this.elem.klucz) == 0)
        {
          Console.WriteLine("Element usuwany: " + this.elem.wartoœæ);
          this.elem = this.elem.elem;
        }
        else
          this.elem.Usuñ(klucz);
      }
      else
        Console.WriteLine("Nie ma elementu o indeksie: " + klucz);
    }

  // Szuka elementu o zadanym kluczu
    public void Szukaj(K klucz)
    {
        if(klucz.CompareTo(this.klucz) != 0 && this.elem != null)
            this.elem.Szukaj(klucz);
        else
        {
          if(klucz.CompareTo(this.klucz) == 0)
            Console.WriteLine("Element o numerze " + klucz + " to "+
            this.wartoœæ);
          else
            {
              Console.WriteLine("Nie ma takiego elementu!");
            }
        }
    }
  }
}
