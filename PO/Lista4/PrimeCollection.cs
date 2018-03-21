//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L4, z2, Stworzenie kolekcji liczb pierwszych
//PrimeCollection.exe
//PrimeCollection.cs
//2018-03-22

using System;
using System.Collections;

public class Primes : IEnumerator
  {
    private int iter;
    public int max;

    //sprawdzamy czy liczba jest pierwsza
    private bool IsPrime(int n)
    {
      if (n < 2) return false;
      for (int i = 2; i < n - 1; i++)
      {
        if (n % i == 0) return false;
      }
      return true;
    }

    //konstruktor
    public Primes()
    {
      iter = 1;
      max = int.MaxValue;
    }

    public Primes(int limit)
    {
      iter = 1;
      max = limit;
    }

    //nastêpny element kolekcji, a¿ do maksymalnej wartoœci inta
    public bool MoveNext()
    {
      iter++;
      while (!IsPrime(iter)) iter++;
      return iter < max;
    }

    //ustawia iter na 1, czyli resetuje kolekcjê
    public void Reset()
    {
      iter = 1;
    }

    //pobiera aktulany element kolekcji
    public object Current
    {
      get
      {
        return iter;
      }
    }
}

class PrimeCollection : IEnumerable
{
  private int limit = int.MaxValue;

  public IEnumerator GetEnumerator()
  {
    return new Primes(limit);
  }

  public PrimeCollection(int limiter)
  {
    limit = limiter;
  }
}

class MainClass
{
  public static void Main()
  {
    int limit=0;
    Primes obj = new Primes();
    bool stan = true;
    while(stan)
    {
      obj.Reset();
      Console.WriteLine("Podaj maksymalna wartosc liczby pierwszej");
      Console.WriteLine("Zero jesli chcesz opuscic program");
      try
      {
        limit = Int32.Parse(Console.ReadLine());
      }
      catch(OverflowException)
      {
        Console.WriteLine("Liczba za duza");
      }
      catch(FormatException)
      {
        Console.WriteLine("Podaj jakies dane");
      }
      if(limit == 0)
      {
        stan = false;
        continue;
      }
      PrimeCollection pc = new PrimeCollection(limit);
      Console.WriteLine("");
      foreach (int p in pc)
        Console.WriteLine(p);
    }
  }
}
