// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L7, z1, Program okienkowy - Pojazdy
// Pojazd
// Samochody.java
// 2018-04-12

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class Samochody extends Pojazd implements Serializable
{
  String wlasciciel;
  String marka;
  int max_predkosc;

  public Samochody(String w, String m, int p)
  {
    wlasciciel = w;
    marka = m;
    max_predkosc = p;
  }

  @Override
  public String toString()
  {
    String str = marka + " nalezacy do " + wlasciciel;
    str = str + " osiaga " + max_predkosc;
    return str;
  }
}
