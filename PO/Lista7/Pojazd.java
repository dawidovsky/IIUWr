// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L7, z1, Program okienkowy - Pojazdy
// Pojazd
// Pojazd.java
// 2018-04-12

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("unchecked")

public class Pojazd
{

  public static void main(String[] args)
  {
    List<Pojazd> pojazd = new ArrayList<Pojazd>();

    pojazd.add(new Samochody("Marek","Opel",210));
    pojazd.add(new Samochody("Kacper","Dacia",250));
    pojazd.add(new Tramwaje(60,1231,70));
    pojazd.add(new Tramwaje(80,1511,80));

    try
    {
      FileOutputStream fos= new FileOutputStream("pojazdy.bin");
      ObjectOutputStream oos= new ObjectOutputStream(fos);
      oos.writeObject(pojazd);
      oos.flush();
      oos.close();
    }
    catch(IOException ioe)
    {
         ioe.printStackTrace();
    }
    odczyt();
  }

  public static void odczyt() {

      FileInputStream fis = null;
      ObjectInputStream ois = null;

      List<Pojazd> poj = null;

      try
      {
        fis = new FileInputStream("pojazdy.bin");
        ois = new ObjectInputStream(fis);
        poj = (List<Pojazd>) ois.readObject();
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
      for(Pojazd obj : poj)
        System.out.println(obj);
  }
}
