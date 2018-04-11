import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class DodajListy extends Pojazd implements ActionListener
{
  String w;
  String m;
  String p;
  String c;

  DodajListy(String wla,String mar,String pre, String co)
  {
    w = wla;
    m = mar;
    p = pre;
    c = co;
  }
}
