#include "common.h"

/**
 * Given an integer, find the factors that are all primes.
 */
std::vector<int> prime_factor(int n) {
    std::vector<int> res;
    while (n % 2 == 0) {
        res.push_back(2);
        n /= 2;
    }

    for (int i = 3; i <= n; i+=2) {
        while (n % i == 0) {
            res.push_back(i);
            n /= i;
        }
    }

    if (n != 1) {
        res.push_back(n);
    }
    return res;    
}

void test(int n) {
    std::vector<int> res = prime_factor(n);
    print(res.begin(), res.end());
}

int main(int argc, char* argv[]) {
    test(atoi(argv[1]));
}
