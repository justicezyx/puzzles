#include "common/common.h"

int sqrt(int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int guess = x / 10;
    guess = std::max(10, guess);
    
    int next = guess / 2 + x / guess / 2;
    while (guess > next) {
        std::cout<<"guess:"<<guess<<"next:"<<next<<std::endl;
        guess = next;
        next = guess / 2 + x / guess / 2;
    }
    return guess;
}

int main() {
    std::cout<<sqrt(1)<<std::endl;
}
