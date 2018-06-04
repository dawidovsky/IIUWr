#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace strumienie
{
  inline ostream& comma (ostream& os)
  {
      return os << ", ";
  }

  inline ostream& colon (ostream& os)
  {
      return os << ": ";
  }

  istream &clearline(istream &in)
  {
      while(in && in.get() != '\n')
      {
      }
      return in;
  }

  class ignore
  {
  public:
    int i;
    friend istream& operator >> (istream& in, const ignore& ig)
    {
      int x = ig.i;
      while(x > 0 && in && in.get() != '\n')
      {
        x--;
      }
      return in;
    }
    ignore(int x)
    {
      i = x;
    }
  };

  class index
  {
    int x, y;
    friend ostream& operator << (ostream &os, const index &licz)
    {
      os << "[";
      os.width(licz.y);
      os << licz.x << "]";
      return os;
    }
  public:
    index (int x1, int y1)
    {
      x = x1;
      y = y1;
    }
  };
}

void print(vector<string> v1, vector<string> v2)
{
  int i = 0;
  cout << "Dodalismy" << strumienie::colon << endl;
  while( i != v1.size())
  {
    int j = 0;
    while(v1[i] != v2[j])
      j++;
    cout << strumienie::index(j+1,1) << v1[i] << strumienie::comma << endl;
    i++;
  }
}

int main()
{
  string c;
  vector<string> v1,v2;
  cout << "Vector Test" << endl;
  int t;
  cin >> t;
  for(int i=1 ; i <= t ; i++)
  {
    cin >> c;
    v1.push_back(c);
  }
  // while(!cin.eof())
  // {
  //   if(cin.peek() == EOF)
  //   {
  //     cout << "PustyPlik" << endl;
  //     break;
  //   }
  //   getline(cin, c);
  //   v1.push_back(c);
  // }
  v2 = v1;
  sort(v1.begin(), v1.end());
  print(v1,v2);
}
