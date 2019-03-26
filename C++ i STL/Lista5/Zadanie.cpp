#include <random>
#include <iostream>
#include <cmath>
#include <fstream>

int main() {
    std::ofstream file1("uniform.csv"), file2("binomial.csv"), file3("poisson.csv"), file4("normal.csv");
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> d(1, 10);
    std::binomial_distribution<> d2(10, 0.5);
    std::poisson_distribution<> d3(3);
    std::normal_distribution<> d4{10,4};
    for(int i=0; i<1000; i++){
        file1 << std::floor(d(gen)) << ';';
        file2 << d2(gen) << ';';
        file3 << d3(gen) << ';';
        file4 << std::floor(d4(gen)) << ';';
    }
    file1.close();
    file2.close();
    file3.close();
    file4.close();
}