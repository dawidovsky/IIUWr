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
  // pola
  String wlasciciel;
  String marka;

  // konstruktor
  public Samochody(String wl, String ma, String pr)
  {
    wlasciciel = wl;
    marka = ma;
    predkosc = pr;
  }

  @Override
  public String toString()
  {
    String str = marka + " nalezacy do " + wlasciciel + " osiaga " + predkosc
    + " km/h";
    return str;
  }
}
