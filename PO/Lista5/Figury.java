  // Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna hierarchia klas
// Figury
// Figury.java
// 2018-03-29

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.io.IOException;
import java.util.Scanner;

// klasa zawieraj�ca menu i obs�ug� figur
public abstract class Figury implements Comparable<Figury>
{
  public static void main(String[] args)
  {
      List<Figury> figury = new ArrayList<Figury>();
      Scanner s = new Scanner(System.in);
      int wybor=5,stan=1;
      while(stan != 0)
      {
        System.out.print("Wybierz, co chcesz zrobic:\n");
        System.out.print("1.Dodaj kwadrat\n");
        System.out.print("2.Dodaj prostokat\n");
        System.out.print("3.Dodaj kolo\n");
        System.out.print("4.Dodaj trojkat\n");
        System.out.print("5.Wypisz figury posortowane po polach\n");
        System.out.print("6.Wyjscie\n");
        wybor = s.nextInt();
        switch(wybor)
        {
          case 1: double dlugosc_boku = 0;
          System.out.print("Podaj dlugosc boku\n");
          dlugosc_boku = s.nextInt();
          figury.add(new Kwadrat(dlugosc_boku));
          break;

          case 2: double dlugosc = 0, szerokosc = 0;
          System.out.print("Podaj dlugosc\n");
          dlugosc = s.nextInt();
          System.out.print("Podaj szerokosc\n");
          szerokosc = s.nextInt();
          figury.add(new Prostokat(dlugosc,szerokosc));
          break;

          case 3: double promien = 0;
          System.out.print("Podaj promien kola\n");
          promien = s.nextInt();
          figury.add(new Kolo(promien));
          break;

          case 4: double podstawa = 0, wysokosc = 0, bok1 = 0, bok2 = 0;
          System.out.print("Podaj podstawe\n");
          podstawa = s.nextInt();
          System.out.print("Podaj wysokosc\n");
          wysokosc = s.nextInt();
          System.out.print("Podaj drugi bok\n");
          bok1 = s.nextInt();
          System.out.print("Podaj trzeci bok\n");
          bok2 = s.nextInt();
          figury.add(new Trojkat(podstawa,wysokosc,bok1,bok2));
          break;

          case 5:
          Collections.sort(figury);
          System.out.println("\nFigury posortowane: ");
          for(Figury figura : figury)
          {
            System.out.println(figura);
          }
          System.out.println("\n");
          break;

          case 6: stan = 0;
          break;

          default:
          System.out.println("Bledne dane");
          break;
        }
      }
  }

  // wyliczanie pola ( nadpisywane w konkretnych klasach )
  public abstract double pole();

  // wyliczanie obwodu ( nadpisywane w konkretnych klasach )
	public abstract double obwod();

  // por�wnywanie figur
  @Override
	public int compareTo(Figury o) {
		return (int) Math.signum(pole() - o.pole());
	}

}
