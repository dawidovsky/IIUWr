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

// klasa dziedziczona przez klase Samochody i Tramwaje
public abstract class Pojazd implements Serializable
{
  String predkosc;
}
