// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L7, z1, Program okienkowy - Pojazdy
// main
// main.java
// 2018-04-12

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("unchecked")

public class main
{
  List<Pojazd> pojazd = new ArrayList<Pojazd>();
  public static void main(String[] args)
  {
    main start = new main();
    start.start();
  }
  public void start()
  {
    JFrame frame = new JFrame("Edycja pojazdy");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(6, 2);
    kontener.setLayout(layout);

    JLabel imie = new JLabel("Imie(samochod)/Numer_ID(tramwaj)");
    kontener.add(imie);
    JTextField podaj_imie = new JTextField(40);
    kontener.add(podaj_imie);

    JLabel marka = new JLabel("Marka(samochod)/Ilosc_miejsc(tramwaj)");
    kontener.add(marka);
    JTextField podaj_marke = new JTextField(40);
    kontener.add(podaj_marke);

    JLabel predkosc = new JLabel("Max Predkosc");
    kontener.add(predkosc);
    JTextField max = new JTextField(40);
    kontener.add(max);

    JLabel typ = new JLabel("Typ Pojazdu(S - samochod, T - tramwaj)");
    kontener.add(typ);
    JTextField jaki = new JTextField(10);
    kontener.add(jaki);

    JButton b = new JButton("Dodaj");
    b.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
        String w = podaj_imie.getText();
        String m = podaj_marke.getText();
        String p = max.getText();
        String c = jaki.getText();
        if(c.equals("S"))
        {
          pojazd.add(new Samochody(w,m,p));
          System.out.print("Dodaje samochod ");
          System.out.println(m);
          System.out.print("Wlascicielem jego jest ");
          System.out.println(w);
          System.out.print("Maksymalnie osiaga ");
          System.out.print(p);
          System.out.print(" km/h");
        }

        if(c.equals("T"))
        {
          pojazd.add(new Tramwaje(w,m,p));
          System.out.print("Dodaje tramwaj ");
          System.out.println(w);
          System.out.print("Posiada on ");
          System.out.print(m);
          System.out.print(" miejsc \nMaksymalnie osiaga ");
          System.out.print(p);
          System.out.print(" km/h");
        }
      }
    });
    kontener.add(b);

    JButton b2 = new JButton("Odczyt");
    b2.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
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
    });
    kontener.add(b2);

    JButton b3 = new JButton("Zapisz");
    b3.addActionListener(new ActionListener()
    {
      public void actionPerformed(ActionEvent e)
      {
        try
        {
          FileOutputStream fos= new FileOutputStream("pojazdy.bin");
          ObjectOutputStream oos= new ObjectOutputStream(fos);
          oos.writeObject(pojazd);
          oos.flush();
          oos.close();
          System.out.println("\nZapisuje");
        }
        catch(IOException ioe)
        {
             ioe.printStackTrace();
        }
      }
    }
    );
    kontener.add(b3);

    frame.pack();
    frame.setVisible(true);
  }
}
