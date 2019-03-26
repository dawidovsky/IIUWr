#include <iostream>
#include <cmath>

// template <int T>
// struct Fib{
//     enum { value = (int)((pow((1 + sqrt(5))/2, T) - pow((1 - sqrt(5))/2, T))/sqrt(5))};
// };

constexpr int Fib(unsigned int T){
    return (int)((pow((1 + sqrt(5))/2, T) - pow((1 - sqrt(5))/2, T))/sqrt(5));
};

template <int T>
struct Luc{
    enum { value = ( Fib(T-1) + Fib(T+1) )};
    // enum { value = ( Fib<T-1>::value + Fib<T+1>::value )};
};

template <>
struct Luc<0>{
    enum { value = 2};
};

int main(){
    std::cout << Luc<0>::value << " " << Luc<1>::value << " " << Luc<2>::value << " " << Luc<3>::value << " " << Luc<4>::value << " " << Luc<5>::value << " " << Luc<6>::value;
}
// 2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, 199, 322, 521, 843, 1364,