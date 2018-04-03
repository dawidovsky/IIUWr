// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z1, Por�wnywalna hierarchia klas
// Figury
// Figury.java
// 2018-03-29

import java.util.Scanner;

public class Zadanie5
{

	public static void main(String[] args)
	{
		int r = 0, liczba;
		Scanner s = new Scanner(System.in);

		System.out.println("Podaj rozmiar tablicy");
		r = s.nextInt();
		int[] tab = new int[r];

		System.out.println("Podaj elementy tablicy (po znaku konca linii)");
		for(int i=0;i<r;i++)
		{
			liczba = s.nextInt();
			tab[i] = liczba;
		}
    MergeSort sort = new MergeSort(tab);
		sort.start();

		try
		{
			sort.join();
		}
    catch(Exception e)
		{
			System.out.print("Blad");
		}

		System.out.print("\n");
    for(int i = 0; i < r; i++) System.out.println(tab[i]);
	}
}
