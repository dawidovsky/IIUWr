using System;
using System.Collections;

public class Primes : IEnumerator
  {
    private int iter;

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
    }

    //nastêpny element kolekcji, a¿ do maksymalnej wartoœci inta
    public bool MoveNext()
    {
      iter++;
      while (!IsPrime(iter)) iter++;
      return iter < int.MaxValue;
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
  public IEnumerator GetEnumerator()
  {
    return new Primes();
  }
}

class MainClass
{
  public static void Main()
  {
    PrimeCollection pc = new PrimeCollection();
    foreach (int p in pc)
      Console.WriteLine(p);
  }
}
