// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L7, z1, Program okienkowy - Pojazdy
// main
// Zapis.java
// 2018-04-12

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

// Zapis do pliku
class Zapis extends Pojazd implements ActionListener
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
      System.out.println("Zapisuje");
    }
    catch(IOException ioe)
    {
         ioe.printStackTrace();
    }
  }
}
