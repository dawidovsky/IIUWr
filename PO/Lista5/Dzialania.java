// Dawid Paluszak
// Pracownia PO, czwartek, s. 108
// L5, z2, Drzewo AST
// Zadanie2
// Dzialania.java
// 2018-03-29

class Dodaj implements Wyrazenie
{
  Wyrazenie a;
  Wyrazenie b;

  // konstruktor dodawania
  public Dodaj (Wyrazenie a, Wyrazenie b)
  {
    this.a = a;
    this.b = b;
  }

  // obliczanie dodawania
  // wyliczamy wartoœci wyra¿eñ a i b i sumujemy wyniki
  public int Oblicz()
  {
    return a.Oblicz() + b.Oblicz();
  }

  // £adne wypisanie dodawania
  public String toString()
  {
    return "(" + a + " + " + b + ")";
  }
}

class Odejmij implements Wyrazenie
{
  Wyrazenie a;
  Wyrazenie b;

  // konstruktor odejmownania
  public Odejmij (Wyrazenie a, Wyrazenie b)
  {
    this.a = a;
    this.b = b;
  }

  // obliczanie odejmowania
  // wyliczamy wartoœci wyra¿eñ a i b i odejmujemy wyniki
  public int Oblicz()
  {
    return a.Oblicz() - b.Oblicz();
  }

  // £adne wypisanie odejmowania
  public String toString()
  {
    return "(" + a + " - " + b + ")";
  }
}

class Pomnoz implements Wyrazenie
{
  Wyrazenie a;
  Wyrazenie b;

  public Pomnoz (Wyrazenie a, Wyrazenie b)
  {
    this.a = a;
    this.b = b;
  }

  // obliczanie mno¿enia
  // wyliczamy wartoœci wyra¿eñ a i b i mno¿ymy wyniki
  public int Oblicz()
  {
    return a.Oblicz() * b.Oblicz();
  }

  // £adne wypisanie mno¿enia
  public String toString()
  {
    return "(" + a + " * " + b + ")";
  }
}

class Podziel implements Wyrazenie
{
  Wyrazenie a;
  Wyrazenie b;

  public Podziel (Wyrazenie a, Wyrazenie b)
  {
    this.a = a;
    this.b = b;
  }

  // obliczanie odejmowania
  // wyliczamy wartoœci wyra¿eñ a i b i dzielimy wyniki
  public int Oblicz()
  {
      return a.Oblicz() / b.Oblicz();
  }

  // £adne wypisanie dzielenia
  public String toString()
  {
    return "(" + a + " / " + b + ")";
  }
}
