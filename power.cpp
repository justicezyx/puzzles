#include "common.h"


double pow(double x, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    std::cout<<"Begin"<<std::endl;
    if (n == 0) {
        return 1;
    }
    
    if (n < 0) {
        if (n == std::numeric_limits<int>::min()) {
            double t = pow(x, std::numeric_limits<int>::max());
            return 1 / t / x;
        }
        return 1 / pow(x, -n);
    }
    
    double res = 1;
    int r = x;
    while (n) {
        std::cout<<"n:"<<n<<std::endl;
        if (n % 2) {
            res *= r;
        }
        r *= r;
        n >>= 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::cout<<pow(1, -2147483648)<<std::endl;
}
