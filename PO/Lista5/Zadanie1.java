// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna kolekcja
// Zadanie1
// Zadanie1.java
// 2018-03-29

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
    lista.Dodaj(5);
    lista.Dodaj(6);
    lista.Wypisz();
    System.out.print("Pobieram i usuwam: " + lista.Pobierz() + "\n");
    lista.Wypisz();
  }

  public class Lista<T>
  {
    private Lista<T> pierwszy;
    private Lista<T> next;
    private T wartosc;

    public void Dodaj(T a)
    {
      if(pierwszy == null)
      {
        pierwszy = new Lista<T>();
        next = new Lista<T>();
        pierwszy.wartosc = a;
      }
      else
      {
        // if(pierwszy.wartosc > a)
        // {
        //   Lista<T> nowy = new Lista<T>();
        //   nowy.wartosc = pierwszy.wartosc;
        //   pierwszy.wartosc = a;
        //   pierwszy.next = nowy;
        //   nowy.next = null;
        // }
        // else
        // {
          while(pierwszy.next != null /*|| pierwszy.next.wartosc > a*/)
            pierwszy = pierwszy.next;
          Lista<T> nowy = new Lista<T>();
          nowy.wartosc = a;
          nowy.next = pierwszy.next;
          pierwszy.next = nowy;
        // }
      }
    }

    public T Pobierz()
    {
      T war = pierwszy.wartosc;
      pierwszy.wartosc = pierwszy.next.wartosc;
      pierwszy = pierwszy.next;
      return war;
    }

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
