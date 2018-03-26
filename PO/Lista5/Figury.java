// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Porównywalna hierarchia klas
// Figury
// Figury.java
// 2018-03-29

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public abstract class Figury implements Comparable<Figury>
{

  public static void main(String[] args)
  {
      List<Figury> figury = new ArrayList<Figury>();
      figury.add(new Kwadrat(4));
      figury.add(new Kwadrat(6));
      figury.add(new Kwadrat(2));
      Collections.sort(figury);

      System.out.println("\nPosortowane: ");
      for(Figury figura : figury)
      {
        System.out.println(figura);
      }
      //System.out.print("drugi");
  }

  public abstract double pole();

	public abstract double obwod();

  @Override
	public int compareTo(Figury o) {
		return (int) Math.signum(pole() - o.pole());
	}

}
