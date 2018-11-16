#include <iostream>
#include <vector>
#include <string> 
#include <list>
#include <set>
#include <algorithm>
#include <limits>

class Print{
    private:
        int k;
        int i;
    public:
        Print(int x, int& iter): k(x), i(iter) {}
        void operator() (double value) {
            if(i%k == 0)
                std::cout << value << " ";
            i++;
        }
        void operator() (std::string value) {
            if(i%k == 0)
                std::cout << value << " ";
            i++;
        }
        void operator() (int value) {
            if(i%k == 0)
                std::cout << value << " ";
            i++;
        }
};

int main(){
    std::vector<double> v1 = {1.2 , 0.7, 0.1, 12.3, 31.1, 5.3, 9.4, 8.1, 1.8, 1.0};
    std::list<std::string> l1 = {"asd", "zxc", "a", "qwe", "qaz", "cxz", "s", "x", "123", "/<>"};
    std::set<int> s1 = {1, 2, 0, 4, -2, 42, 12, 8, 321, -123};

    // Wypisanie wartosci z zakresu
    int a = 2, b = 6;
    std::for_each(&v1[a], &v1[b], [](double num){ std::cout << num << " "; }); std::cout << "\n";
    std::for_each(std::next(l1.begin(), a), std::next(l1.begin(), b), [](std::string str){ std::cout << str << " "; }); std::cout << "\n";
    std::for_each(std::next(s1.begin(), a), std::next(s1.begin(), b), [](int num){ std::cout << num << " "; });std::cout << "\n\n";

    // Wypisanie co k-tej wartosci od p-tej pozycji
    int k = 2, p = 3, iter = 0;
    std::for_each(std::next(v1.begin(), p), v1.end(), Print(k, iter)); std::cout << "\n"; iter = 0;
    std::for_each(std::next(l1.begin(), p), l1.end(), Print(k, iter)); std::cout << "\n"; iter = 0;
    std::for_each(std::next(s1.begin(), p), s1.end(), Print(k, iter)); std::cout << "\n\n"; iter = 0;

    // Suma/Konkatenacja
    double sum = 0;
    std::string str;
    std::for_each(v1.begin(), v1.end(), [&](double num){ sum += num; }); std::cout << sum << "\n"; sum = 0;
    std::for_each(l1.begin(), l1.end(), [&](std::string s){ str += s; }); std::cout << str << "\n";
    std::for_each(s1.begin(), s1.end(), [&](int num){ sum += num; }); std::cout << sum << "\n\n";

    // Dodawanie zadanej wartosci
    double val = 12.3;
    str = "value";
    std::for_each(v1.begin(), v1.end(), [=](double& num){ num += val; });
    std::for_each(l1.begin(), l1.end(), [=](std::string& s){ s += str; }); 
    // std::for_each(s1.begin(), s1.end(), [=](int num){ num += val; }); // problem -- wartosci seta sie nie zmienia 

    // Srednia arytmetyczna
    double res = 0.0;
    std::for_each(v1.begin(), v1.end(), [&](double num){ res *= iter; res += num; res /= ++iter; }); std::cout << res << "\n"; iter = 0; 
    std::for_each(s1.begin(), s1.end(), [&](int num){ res *= iter; res += num; res /= ++iter; });  std::cout << res << "\n\n";

    // Min / Max
    double min = std::numeric_limits<int>::max();
    double max = std::numeric_limits<int>::min();
    int iter1 = 0, iter2 = 0;
    iter = 0;
    std::for_each(v1.begin(), v1.end(), [&](double num) {
        if(num > max){ max = num; iter2 = iter; }
        if(num < min){ min = num; iter1 = iter; }
        iter++;
     }); std:: cout << "min: " << v1[iter1] << " max: " << v1[iter2] << "\n";

    min = std::numeric_limits<int>::max();
    max = std::numeric_limits<int>::min();

    iter = iter1 = iter2 = 0;
    std::for_each(s1.begin(), s1.end(), [&](int num) {
        if(num > max){ max = num; iter2 = iter; }
        if(num < min){ min = num; iter1 = iter; }
        iter++;
    }); std:: cout << "min: " << *std::next(s1.begin(), iter1) << " max: " << *std::next(s1.begin(), iter2) << "\n";

    std::string mins = std::numeric_limits<std::string>::max();
    std::string maxs = std::numeric_limits<std::string>::min();

    iter = iter1 = iter2 = 0;
    std::for_each(l1.begin(), l1.end(), [&](std::string str) {
        if(str > maxs){ maxs = str; iter2 = iter; }
        if(str < mins){ mins = str; iter1 = iter; }
        iter++;
    }); std:: cout << "min: " << *std::next(l1.begin(), iter1) << " max: " << *std::next(l1.begin(), iter2) << "\n\n";

    // znajdowanie pierwszej liczby parzystej z set'a
    std::cout << *std::find_if(s1.begin(), s1.end(), [](int num){ return num%2 == 0; }) << "\n";

    // znajdowanie pierwszej liczby całkowitej w vectorze
    std::cout << *std::find_if(v1.begin(), v1.end(), [](double num){ return num == (int)num; }) << "\n\n"; 

    // podnoszenie elemntów vectora do kwadratu za pomoca transform
    std::for_each(v1.begin(), v1.end(), [](double num){ std::cout << num << " "; }); std::cout << "\n";
    std::transform(v1.begin(), v1.end(), v1.begin(), [](double num){ return num*num; });
    std::for_each(v1.begin(), v1.end(), [](double num){ std::cout << num << " "; }); 
}