#include "wymierne.hpp"

using namespace obliczenia;

int main()
{
  try
  {
    Wymierna w1(1,2);
    Wymierna w2(3,4);
    cout << "1/2 + 3/4 = ";
    cout << w1 + w2 << endl;
    cout << "1/2 - 3/4 = ";
    cout << w1 - w2 << endl;
    cout << "1/2 * 3/4 = ";
    cout << w1 * w2 << endl;
    cout << "1/2 / 3/4 = ";
    cout << w1 / w2 << endl;
    cout << "1/2 ze zmienionym znakiem: " << -w1 << endl;
    cout << "-1/2 odwrotna: " << !w1 << endl;
    Wymierna zero(1,0);
  }

  catch(NieDzielPrzezZero &er)
  {
    cerr << er.what();
  }

  catch(PrzekroczonoZakres &er)
  {
    cerr << er.what();
  }
}
