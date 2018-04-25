#include "wymierne.hpp"

using namespace obliczenia;

int main()
{
  try
  {
    Wymierna w1(1,2);
    Wymierna w2(3,4);
    cout << "1/2 + 3/4 = ";
    Wymierna w3 = w1 + w2;
    cout << w3 << endl;
    Wymierna w4(1,3);
    cout << "1/3 = " << w4 << endl;
    w3 = w1 - w2;
    cout << "1/2 - 3/4 = " << w3 << endl;
    w3 = w1 * w2;
    cout << "1/2 * 3/4 = " << w3 << endl;
    w3 = w1 / w2;
    cout << "1/2 / 3/4 = " << w3 << endl;
    Wymierna w5(1,0);
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
