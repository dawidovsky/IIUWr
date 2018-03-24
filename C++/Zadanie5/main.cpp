#include "Data.hpp"

using namespace std;

int main()
{
  cout << "******* Klasa Data *******" << endl;
  Data dzien_pierwszy(15,10,1582);
  cout << dzien_pierwszy << " - data z konkretnymi danymi" <<  endl;
  Data zla_data(29,2,2001);
  cout << " - data z blednymi danymi (29.02.2001)" << endl;
  Data data;
  cout << data << " - data bez parametrow" <<  endl;
  Data data_kopiowana(dzien_pierwszy);
  cout << data_kopiowana << " - data kopiowana" <<  endl;
  Data dzien(31,12,2000);
  cout << dzien << " - ostatni dzien w roku" <<  endl;
  dzien++;
  cout << dzien << " - inkrementowana poprzednia data" <<  endl;
  dzien--;
  cout << dzien << " - dekrementowana poprzednia data" <<  endl;
  Data dzien_odej1(20,10,2002);
  Data dzien_odej2(20,10,2001);
  cout << dzien_odej1 - dzien_odej2;
  cout << " - odejmowanie dat oddalonych o rok" <<  endl;
  cout << dzien_odej2 << " - data od ktorej dodaje/odejmuje" << endl;
  dzien_odej2 += 730;
  cout << dzien_odej2 << " - dodaje 730(2_lata) do daty" <<  endl;
  dzien_odej2 += 366;
  cout << dzien_odej2 << " - dodaje 366 do daty(przestepny rok)" <<  endl;
  dzien_odej2 -= 1096;
  cout << dzien_odej2 << " - odejmuje 1096(3 lata jeden rok przestepny)" <<  endl << endl;

  cout << "******* Klasa DataGodz *******" << endl;
  DataGodz data_bezargumentowa;
  cout << data_bezargumentowa << " - data bez argumentow" << endl;
  DataGodz data_moja(20,10,2003,15,24,59);
  cout << data_moja << " - data z konkretnymi danymi" <<  endl;
  DataGodz ostatnia_sekunda(31,12,2001,23,59,59);
  cout << ostatnia_sekunda << " - ostatnia sekunda w roku" << endl;
  ostatnia_sekunda++;
  cout << ostatnia_sekunda << " - inkrementowana poprzednia data" <<  endl;
  ostatnia_sekunda--;
  cout << ostatnia_sekunda << " - dekrementowana poprzednia data" <<  endl;
  DataGodz data_odej1(20,10,2002,20,20,20);
  DataGodz data_odej2(20,10,2001,20,20,20);
  int wynik = data_odej1 - data_odej2;
  cout << wynik;
  cout << " - odejmowanie dat oddalonych o rok(31536000 - ilosc sekund w roku)" <<  endl;
  cout << "Czy " << data_odej1 << " jest wczesniej niz " << data_odej2 << " ?";
  bool odp = data_odej1 < data_odej2;
  cout << "Odpowiedz(bool): " << odp << endl;
  cout << "Czy " << data_odej2 << " jest wczesniej niz " << data_odej1 << " ?";
  odp = data_odej2 < data_odej1;
  cout << "Odpowiedz(bool): " << odp << endl;
  cout << "Czy " << data_odej1 << " i " << data_odej2 << " sa rowne?";
  odp = data_odej1 == data_odej2;
  cout << "Odpowiedz(bool): " << odp << endl;
  cout << "Czy " << DataGodz(1,1,2000,1,1,1) << " i " << DataGodz(1,1,2000,1,1,1) << " sa rowne?";
  odp = DataGodz(1,1,2000,1,1,1) == DataGodz(1,1,2000,1,1,1);
  cout << "Odpowiedz(bool): " << odp << endl << endl;

  cout << "******* Klasa Wydarzenie *******" << endl;
  vector<Wydarzenie> wydarzenia;
  Wydarzenie ins;
  Wydarzenie wyd1(DataGodz(1,1,2000,0,0,0),"Rozpoczecie nowego milenium");
  wydarzenia.push_back(wyd1);
  Wydarzenie wyd2(DataGodz(1,9,1939,0,0,0),"Rozpoczecie II wojny swiatowej");
  wydarzenia.push_back(wyd2);
  Wydarzenie wyd3(DataGodz(15,4,1912,0,0,0),"Zatoniecie Titanica");
  wydarzenia.push_back(wyd3);
  Wydarzenie wyd4(DataGodz(26,4,1986,0,0,0),"Wybuch elektrowni w Czarnobylu");
  wydarzenia.push_back(wyd4);
  Wydarzenie wyd5(DataGodz(20,7,1969,0,0,0),"Ladowanie na Ksiezycu");
  wydarzenia.push_back(wyd5);
  wydarzenia = ins.sortowanie(wydarzenia);
  for(int i=0; i<wydarzenia.size();i++)
  {
    cout << "Dnia: " << wydarzenia[i].data << " wydarzylo sie: " << wydarzenia[i].opis << endl;
  }
}
