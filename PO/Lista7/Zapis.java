import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;


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
