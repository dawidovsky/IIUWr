//Dawid Paluszak
//Pracownia PO, czwartek, s. 108
//L4, z1, Stworzenie kolekcji z dw�ch poprzednich zada�
//MyCollection.exe
//MyCollection.cs
//2018-03-22

using System;
using System.Collections;

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

    // Usuwa elementy z ko