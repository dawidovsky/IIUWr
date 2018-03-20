/*Programowanie Obiektowe - Dawid Paluszak Pracownia 108 | 08.03.2018r
Lista 2 Zadanie 1
Uruchamiamy program i  obsługujemy go poprzez zaimplementowane menu
Język C# - kompilator csc 4.7.2556.0*/

class IntStream
{
  private int i=-1;
  private bool endofstream = false;
      virtual public int next()
      {
        if(i == 2147483647)
          endofstream = true;
        if(endofstream == true)
          return -1;
        i++;

        return i;
      }
      public bool eos()
      {
        return endofstream;
      }
      static void Main()
      {
        int stan = 1;
        System.Console.WriteLine("Wybierz co chcesz zrobic:");
        System.Console.WriteLine("1.Kolejna liczba naturalna");
        System.Console.WriteLine("2.Wlacz/Wylacz strumien");
        System.Console.WriteLine("3.Sprawdz stan strumienia");
        System.Console.WriteLine("4.Reset");
        System.Console.WriteLine("5.Liczba losowa");
        System.Console.WriteLine("6.Kolejne liczby pierwsze");
        System.Console.WriteLine("7.Ciagi znakow o dlugosci liczb pierwszych");
        System.Console.WriteLine("8.Wyjscie");
        IntStream instance = new IntStream();
        PrimeStream prime = new PrimeStream();  
        PrimeStream primeForStrings = new PrimeStream();
        while(stan == 1)
        {
          string wybor = System.Console.ReadLine();
          switch (wybor)
          {
            case "1":
            {
              int liczba = instance.next();
              if(liczba == -1)
                System.Console.WriteLine("Strumien zamkniety");
              else
                System.Console.WriteLine("Liczba naturalna: " + liczba);
              break;
            }
            case "2":
            {
              bool eos = instance.endofstream;
              if(eos == true)
                instance.endofstream = false;
              else
                instance.endofstream = true;
                break;
            }
            case "3":
            {
              System.Console.WriteLine("Stan strumienia : " + instance.eos());
              break;
            }
            case "4":
            {
              instance = new IntStream();
              System.Console.WriteLine("Ustawienia zresetowane");
              break;
            }
            case "5":
            {
              RandomStream random = new RandomStream();
              if(instance.endofstream == false)
                System.Console.WriteLine("Liczba losowa:" + random.next());
              else
                System.Console.WriteLine("Strumien zamkniety");
              break;
            }
            case "6":
            {
              int wynik = prime.next();
              if(wynik == -1)
              {
                instance.endofstream = true;
                System.Console.WriteLine("Strumien zamkniety");
              }
              else
                System.Console.WriteLine("Kolejna Liczba Pierwsza " + wynik);
              break;
            }
            case "7":
            {
              RandomWordStream ciag = new RandomWordStream();
              string rnd_string = ciag.next();
              System.Console.WriteLine("Losowy ciag znakow: " + rnd_string);
              break;
            }
            case "8":
            {
              stan = 0;
              break;
            }
            default:
            {
              System.Console.WriteLine("Bledny wybor");
              break;
            }
          }
        }
      }
}

class PrimeStream : IntStream
{
  private int ps = 2;
  override public int next()
  {
    bool czyPierwsza = false;
    while(czyPierwsza == false)
    {
      bool czyZnalazlo = false;
      for(int i = 2; i <= System.Math.Sqrt(ps); i++)
      {
        if(ps%i == 0)
        {
          czyZnalazlo = true;
          break;
        }
      }
      if(czyZnalazlo == true)
        ps++;
      else
        czyPierwsza = true;
    }
    int ps_poprz = ps;
    ps++;
    if(ps_poprz == 2147483647)
      return -1;
    return ps_poprz;
  }
}

class RandomStream : IntStream
{
  override public int next()
  {
    System.Random rnd = new System.Random();
    return rnd.Next();
  }
}

class RandomWordStream
{
  private static PrimeStream len = new PrimeStream();
  private int length = len.next() ;
  private RandomStream random = new RandomStream();
  private string str = null;

  public string next()
  {
    int ran = random.next();
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++)
    {
      str += chars[ran%52];
      ran /= 10;
      if(ran < 10) ran = random.next();
    }

    return str;
  }
}
