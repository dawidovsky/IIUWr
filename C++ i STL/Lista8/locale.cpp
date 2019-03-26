#include <iostream>
#include <locale>
#include <random>
#include <iomanip>
#include <ctime>    

int main(){
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(-1000000000, 1000000000);

    double n = distr(eng);
    std::time_t t = std::time(NULL);
	cout << "something";

    // std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << n << '\n';
    std::cout << std::put_money(100) << "\n";
    std::cout << std::put_time(std::localtime(&t), "%c") << "\n\n";  

    // std::cout.imbue(std::locale("pl-PL"));
    std::cout << std::fixed << n << '\n';
    std::cout << std::put_money(100) << "\n";
    std::cout << std::put_time(std::localtime(&t), "%c") << "\n";  
} 