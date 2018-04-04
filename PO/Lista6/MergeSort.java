// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L6, z5, MergeSort poprzez w¹tki
// Zadanie5
// Zadanie5.java
// 2018-04-05

// implementacja mergesort'a poprzez w¹tki
class MergeSort extends Thread
{

  public int[] array;

  // konstruktor
  public MergeSort(int[] a)
  {
    array = a;
  }

  // sortowanie
  public void mergeSort(int[] array)
  {
    if (array.length > 1)
    {
      // tablicê dzielimy na dwie mniejsze tablice i wykonujemy na nich
      // sortowanie wywo³uj¹c je jako kolejny w¹tek
      int[] left = leftHalf(array);
      int[] right = rightHalf(array);

      MergeSort sort1 = new MergeSort(left);
      MergeSort sort2 = new MergeSort(right);

      sort1.start();
      sort2.start();

      try
  		{
  			sort1.join();
        sort2.join();
  		}
      catch(Exception e)
  		{
  			System.out.print("Blad");
  		}

      merge(array, left, right);
    }
  }

  // przepisywanie pierwszej po³owy tablicy i zapisywanie jej
  // do tablicy pomocniczej
  public int[] leftHalf(int[] array)
  {
    int size1 = array.length / 2;
    int[] left = new int[size1];
    for (int i = 0; i < size1; i++)
    {
      left[i] = array[i];
    }
    return left;
  }

  // przepisywanie drugiej po³owy tablicy i zapisywanie jej
  // do tablicy pomocniczej
  public int[] rightHalf(int[] array)
  {
    int size1 = array.length / 2;
    int size2 = array.length - size1;
    int[] right = new int[size2];
    for (int i = 0; i < size2; i++)
    {
      right[i] = array[i + size1];
    }
    return right;
  }

  // ³¹czenie dwóch tablic
  public void merge(int[] result, int[] left, int[] right)
  {
    int i1 = 0;
    int i2 = 0;

    for (int i = 0; i < result.length; i++)
    {
      if (i2 >= right.length || (i1 < left.length && left[i1] <= right[i2]))
      {
         result[i] = left[i1];
        i1++;
      }
      else
      {
         result[i] = right[i2];
         i2++;
      }
    }
  }

  // uruchomienie w¹tku
  public void run()
  {
    mergeSort(array);
  }
}
