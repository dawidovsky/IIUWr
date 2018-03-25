// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna kolekcja
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
    lista.Dodaj(1);
    lista.Dodaj(6);
    lista.Dodaj(3);
    lista.Dodaj(0);
    lista.Wypisz();
    System.out.print("Pobieram i usuwam: " + lista.Pobierz() + "\n");
    lista.Wypisz();
  }

  public class Lista<T extends Comparable>
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
          while(pierwszy.next != null)
          {
            if(pierwszy.next.wartosc.compareTo(a) > 0)
              break;
            pierwszy = pierwszy.next;
          }
          Lista<T> nowy = new Lista<T>();
          nowy.wartosc = a;
          nowy.next = pierwszy.next;
          pierwszy.next = nowy;
        }
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
