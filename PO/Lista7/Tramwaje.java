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
  int ilosc_miejsc;
  int numer_id;
  int max_predkosc;

  public Tramwaje(int i, int n, int p)
  {
    ilosc_miejsc = i;
    numer_id = n;
    max_predkosc = p;
  }

  @Override
  public String toString()
  {
    String str = "Tramwaj " + numer_id + " o ilosci miejsc " + ilosc_miejsc;
    str = str + " osiaga maksymalnie " + max_predkosc;
    return str;
  }
}
