// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L7, z1, Program okienkowy - Pojazdy
// Pojazd
// Tramwaje.java
// 2018-04-12

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class Tramwaje extends Pojazd implements Serializable
{
  String numer_id;
  String ilosc_miejsc;
  
  public Tramwaje(String i, String n, String pr)
  {
    numer_id = i;
    ilosc_miejsc = n;
    predkosc = pr;
  }

  @Override
  public String toString()
  {
    String str = "Tramwaj " + numer_id + " o ilosci miejsc "
    + ilosc_miejsc + " osiaga maksymalnie " + predkosc + " km/h";
    return str;
  }
}
