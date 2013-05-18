#include "common.h"

/**
 * Question:
 * Find the n-th prime number starting from 0.
 * 0 is deemed a prime.
 */

// http://math.stackexchange.com/questions/1257/is-there-a-known-mathematical-equation-to-find-the-nth-prime
//
// http://mathworld.wolfram.com/PrimeCountingFunction.html
// http://mathworld.wolfram.com/RiemannPrimeCountingFunction.html
//
// The idea is to guess a starting point and count the primes <= the number
// and starting from that number and find the range that contains the desired number and sieve from that point.
//
// Find the n-th prime number staring from 0.
// The index starts from '0'.
int nth_prime(int n) {
    if (n <= 3) {
        return n;
    }

    

