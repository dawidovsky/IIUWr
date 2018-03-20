//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L3, z1, Stworzenie Listy
//Lista.exe
//Lista_klasa.cs
//2018-03-15


using System;

namespace Lista
{
//Klasa z polami do Listy
  public class Elem<T>
  {
      public T warto��;
      public Elem<T> kolejny;
      public Elem<T> poprzedni;

      public Elem()
      {
          kolejny = null;
          poprzedni = null;
          warto�� = default(T);
      }
  }


  public class Lista<T>
    where T : IComparable<T>
  {

      public Elem<T> pierwszy;
      public Elem<T> ostatni;

      public Lista()
      {
          pierwszy = null;
          ostatni = null;
      }

    // Dodaje element na pocz�tek listy
      public void DodajPocz�tek(T x)
      {
          if (pierwszy == null)
          {
              pierwszy = new Elem<T>();
              ostatni = new Elem<T>();
              pierwszy.warto�� = x;
              ostatni = pierwszy;
          }
          else
          {
              Elem<T> nowy = new Elem<T>();
              nowy.warto�� = x;
              nowy.kolejny = pierwszy;
              nowy.poprzedni = null;
              pierwszy.poprzedni = nowy;
              if(pierwszy.warto��.CompareTo(ostatni.warto��) == 0)
              {
                ostatni = nowy.kolejny;
              }
              pierwszy = nowy;
          }
      }

    //Dodaje element na koniec listy
      public void DodajKoniec(T x)
      {
          if (ostatni == null)
          {
              pierwszy = new Elem<T>();
              ostatni = new Elem<T>();
              pierwszy.warto�� = x;
              ostatni = pierwszy;
          }
          else
          {
              Elem<T> nowy = new Elem<T>();
              nowy.warto�� = x;
              nowy.kolejny = null;
              ostatni.kolejny = nowy;
              nowy.poprzedni = ostatni;
              ostatni = nowy;
          }

      }

    // Usuwana element z pocz�tku listy
      public T Usu�Pocz�tek()
      {
          if (pierwszy == null)
          {
              Console.WriteLine("Nie mo�na usun�� elementu z listy pustej!");
              return default(T);
          }
          else
          {
              T temp = ostatni.warto��;
              if(pierwszy == ostatni)
              {
                 ostatni = null;
                 pierwszy = null;
                 return temp;
              }
              pierwszy = pierwszy.kolejny;
              if(pierwszy != null)
                 pierwszy.poprzedni = null;
              return temp;
          }
      }

    // Usuwa elementy z ko�ca listy
      public T Usu�Koniec()
      {
          if (ostatni == null)
          {
              Console.WriteLine("Nie mo�na usun�� elementu z listy pustej!");
              return default(T);
          }
          else
          {
            T temp = ostatni.warto��;
            if(pierwszy == ostatni)
              {
                 ostatni = null;
                 pierwszy = null;
                 return temp;
              }
            ostatni = ostatni.poprzedni;
            if(ostatni != null)
              ostatni.kolejny = null;
            return temp;
          }
      }

    // Sprawdzanie czy lista jest pusta
      public bool Pusta()
      {
          if (pierwszy == null)
              return true;
          else
              return false;
      }

    // Wypisywanie ca�ej listy
      public void Wypisz()
      {
          if(pierwszy == null)
          {
              Console.WriteLine("Lista jest pusta!");
              return;

          }
          Elem<T> temp = pierwszy;
          Console.WriteLine("Lista zawiera:");
          while (temp != null)
          {
              Console.WriteLine(temp.warto��);
              temp = temp.kolejny;
          }
      }

      // Wypisuje element na jaki wskazuje "pierwszy"
      public void WP()
      {
         if(pierwszy != null)
         Console.WriteLine("Pierwszy element to: " + pierwszy.warto��);
      }

      // Wypisuje element na jaki wskazuje "ostatni"
      public void WO()
      {
         if(ostatni != null)
         Console.WriteLine("Ostatni element to: " + ostatni.warto��);
      }
  }
}
