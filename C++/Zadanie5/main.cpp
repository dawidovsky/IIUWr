#include "Data.hpp"

using namespace std;

int main()
{
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
  cout << dzien_odej2 << " - odejmuje 1096(3 lata jeden rok przestepny)" <<  endl;
}
