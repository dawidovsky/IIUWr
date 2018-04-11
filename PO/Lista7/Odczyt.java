
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("unchecked")

class Odczyt extends Pojazd implements ActionListener
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
    {
      System.out.println(obj);
      System.out.println("Odczytuje");
    }
  }
}
