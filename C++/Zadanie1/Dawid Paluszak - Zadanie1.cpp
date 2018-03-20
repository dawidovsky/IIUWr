#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

using namespace std;

bool isPrime(int64_t x) {
    if (x % 2 == 0)
        return false;
    int64_t max = floor(sqrt(x));
    for (int64_t i = 3; i < max; i+=2)
        if (x % i == 0)
            return false;
    return true;
}

int64_t stringToInt64(string znaki)
{
  int64_t liczba;
  bool czyBlad = false;
	try
      {
        for(int i=1;i<znaki.length();i++)
          if(znaki[i] < 47 || znaki[i] > 57)
            czyBlad = true;
        if(czyBlad)
          throw invalid_argument("");
        liczba = stoll(znaki,NULL,10);
			}
	catch (invalid_argument) {
        cerr << "Ten argument nie jest liczba: " << znaki <<  endl;
        return 0;
      }
  catch (out_of_range) {
        cerr << "Ten argument jest zbyt duza liczba: " << znaki << endl;
        return 0;
      }
  return liczba;
}

vector<int64_t> dodajLiczbyPierwsze(vector<int64_t> tab,int64_t liczba)
{
  if(liczba == -1){tab.push_back(-1);return tab;}
  if(liczba == 0){tab.push_back(0);return tab;}
  if(liczba == -9223372036854775807){tab.push_back(-1);tab.push_back(2);liczba/=-2;}
	if(liczba<0)
  {
		liczba*=-1;
		tab.push_back(-1);
	}

  if (isPrime(liczba) )
   {
      tab.push_back(liczba);
      return tab;
   }

  int64_t dzielnik = 2;
	while(liczba > 1)
	{
			if(liczba%dzielnik == 0)
			{
				tab.push_back(dzielnik);
				liczba/=dzielnik;
        if (isPrime(liczba) && liczba != 1)
            {
                tab.push_back(liczba);
                return tab;
            }
			}
			else
				dzielnik++;
	}
	return tab;
}

void print  (int64_t i) {
  cout << " * " << i;
}

int main(int argc, char * argv[])
{
	if(argc < 2)
		  cout << "Uzytkownik powinien podac rowniez argumenty wywolania programu z zakresu int64_t";
	vector<int64_t> tab;
	for(int i=1; i<argc ; i++)
	{
    string znaki = argv[i];
		int64_t liczba = stringToInt64(znaki);
    if((znaki != "0" && liczba != 0) || (znaki == "0" && liczba == 0))
    {
      tab = dodajLiczbyPierwsze(tab,liczba);
  		cout << liczba << " = " << tab[0];
  		for_each(tab.begin() + 1, tab.end() , print);
  		cout << endl;
  		tab.clear();
    }
	}
}
