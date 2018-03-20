#include "stos.hpp"

int main()
{
  int poj;
  cout << "Podaj pojemnosc stosu" << endl;
  cin >> poj;
  Stos instance = Stos(poj);
  cout << "Wybierz co chcesz zrobic:" << endl;
  cout << "1.Wyswietl pojemnosc stosu" << endl;
  cout << "2.Wyswietl ile jest elementow na stosie" << endl;
  cout << "3.Wstaw element na stos" << endl;
  cout << "4.Usun element ze szczytu stosu" << endl;
  cout << "5.Wypisz zawartosc stosu" << endl;
  cout << "6.Wyjscie" << endl;
  bool stan = 1;
  string elem;
  int wybor;
  while(stan)
  {
    cin >> wybor;
    switch (wybor) {
      case 1:
      {
          cout << "Pojemnosc stosu wynosi : " << instance.get_poj() << endl;
          break;
      }
      case 2:
      {
          cout << "Ilosc elementow na stosie : " << instance.rozmiar() << endl;
          break;
      }
      case 3:
      {
          int ile = instance.get_ile();
          int poj = instance.get_poj();
          cout << "Jaki element wstawic?" << endl;
          cin >> elem;
          if(ile == poj)
          {
            cout << "Maksymalny rozmiar stosu osiagniety!" << endl;
            break;
          }
          instance.wloz(elem);
          cout << "Wkladam element " <<  elem <<
          " na miejsce " << instance.rozmiar() << endl;
          break;
      }
      case 4:
      {
        if(!instance.get_ile())
        {
          cout << "Na stosie nic nie ma! " << endl;
          break;
        }
        cout << "Sciagam element " << instance.sciagnij() <<
        " ze stosu" << endl;
        break;
      }
      case 5:
      {
        if(!instance.get_ile())
        {
          cout << "Na stosie nic nie ma! " << endl;
          break;
        }
        cout << "Na stosie mamy:" << endl;
        for(int i=instance.rozmiar()-1 ; i>=0 ; i--)
        {
          cout << instance.stos[i] << endl;
        }
        break;
      }
      case 6:
      {
        stan = 0;
        delete [] instance.stos;
        break;
      }
      default:
      {
        cout << "Bledny wybor" << endl;
      }
    }
  }
}
