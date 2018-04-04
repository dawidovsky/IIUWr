// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L6, z1, Kolekcja 'Serializable'
// Figury
// Figury.java
// 2018-04-05

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.io.*;
import java.util.Scanner;

@SuppressWarnings("unchecked")

// klasa tworz¹ca kolekcjê figur
// zapisuj¹ca wynik do pliku
// i odczytuj¹ca ten wynik z pliku
public abstract class Figury implements Comparable<Figury>
{
  public static void main(String[] args)
  {
    List<Figury> figury = new ArrayList<Figury>();

    figury.add(new Kwadrat(5));
    figury.add(new Kwadrat(3));
    figury.add(new Prostokat(2,4));
    figury.add(new Kolo(5));
    Collections.sort(figury);

    // zapisywanie do pliku
    try
    {
      FileOutputStream fos= new FileOutputStream("figury.txt");
      ObjectOutputStream oos= new ObjectOutputStream(fos);
      oos.writeObject(figury);
      oos.flush();
      oos.close();
    }
    catch(IOException ioe)
    {
         ioe.printStackTrace();
    }
    odczyt();
  }


  // wyliczanie pola ( nadpisywane w konkretnych klasach )
  public abstract double pole();

  // wyliczanie obwodu ( nadpisywane w konkretnych klasach )
	public abstract double obwod();

  // porównywanie figur
  @Override
	public int compareTo(Figury o)
  {
		return (int) Math.signum(pole() - o.pole());
	}

  // metoda odczytuj¹ca z pliku
  public static void odczyt() {

      FileInputStream fis = null;
      ObjectInputStream ois = null;

      List<Figury> fig = null;

      try
      {
        fis = new FileInputStream("figury.txt");
        ois = new ObjectInputStream(fis);
        fig = (List<Figury>) ois.readObject();
      }
      catch (FileNotFoundException err)
      {
        err.printStackTrace();
      }
      catch (IOException err)
      {
        err.printStackTrace();
      }
      catch (ClassNotFoundException err)
      {
        err.printStackTrace();
      }

      // wypisywanie tego co zostanie odczytane z pliku
      for(Figury obj : fig)
        System.out.println(obj);
  }

}
