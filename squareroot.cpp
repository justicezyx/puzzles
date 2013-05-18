#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <iostream>

int squareroot(int n) {
    if(n < 0) {
        return -1;
    }

    if(n == 0) {
        return 0;
    }

    int low = 10;
    int high = n / low;
    if(low > high) {
        std::swap(low, high);
    }

    int i = 0;

    while(high - low > 1) {
        ++i;
        int mid = (low + high) / 2;
        int tmp = n / mid;
        
        //printf("mid %d high %d low %d\n", tmp, high, low);
        if(mid > tmp) {
            high = mid;
            low = tmp;
        } else {
            high = tmp;
            low = mid;
        }
    }
    //printf("iterator: %d\n", i);
    return low;
}

void test() {
    int int_max = std::numeric_limits<int>::max();
    for(int i = 0; i <= int_max; i++) {
        int l = squareroot(i);
        int r = sqrt(i);
        if(l != r) {
            printf("failed: %d\n", i);
        }
    }
    printf("passed\n");
}

void test(int (*func)(int)) {
    int int_max = std::numeric_limits<int>::max();
    for(int i = 0; i <= int_max; i++) {
        int l = sqrt(i);
        int r = func(i);
        if(l != r) {
            printf("failed: %d sqrt: %d err: %d\n", i, l, r);
        } else {
            // printf("succeeded: %d sqrt: %d err: %d\n", i, l, r);
        }
    }
    printf("passed\n");
}

// incorrect version for input 24, will switch between 5, 4
int babylonian(int n) {
    // babylonian method
    // see methods_of_computing_square_roots on wiki
    int init = 10;
    int next = (init + n/init)/2;

    while(abs(init - next) >= 1) {
        printf("init:%d next:%d\n", init, next);
        std::swap(init, next);
        next = (init + n/init)/2;
        printf("init:%d next:%d\n", init, next);
    }

    return std::min(init, next);
}

// never start the estimation from a wrong angle
// if the initial estimation is certainly smaller than sqrt(n)
// then approaching by increasing, and stops when the next estimation is less
// then or equals to the current 
// if the initial estimation if certainly larger than sqrt(n)
// then approaching by decreasing. This is preferred, since it avoids the overflow problem.
int babylonian_correct(int n) {
    // babylonian method
    // see methods_of_computing_square_roots on wiki
    std::cout<<"Input: "<<n<<std::endl;
    if (n <= 1) { 
        return n;
    }

    int init = n / 2 + 1;
    int next = (init + n / init) / 2;
    /*
    if (init > next) {
        std::swap(init, next);
    }
    */
    printf("init:%d next:%d\n", init, next);

    while (next < init) {
        init = next;
        next = (init + n / init) / 2;
        printf("init:%d next:%d\n", init, next);
    }

    return init;
    /**
     * Seems that if start from an estimation that is larger than the answer,
     * any estimation will not be larger than this; until we reach an estimation that
     * is less than or equal to the answer.
     *
     * however, if start from an estimation that is smaller than the answer,
     * the estimation can sweep back to a larger one. So we should always start from the
     * larger estimation.
     */
}


int binary_isqrt(int n) {
    // std::cout<<"Input: "<<n<<std::endl;

    if (n <= 1) { return n; }

    int low = 1;
    int high = n;

    while (high - low > 1) {
        int mid = low / 2 + high / 2;
        
        if (mid < n / mid) {
            low = mid;
        } else {
            high = mid;
        }
        // std::cout<<low<<" "<<high<<std::endl;
    }

    if (high > n / high) {
        return low;
    } else {
        return high;
    }
}

int isqrt(int num) {
    if (0 == num) { return 0; }  // Avoid zero divide
    int n = (num / 2) + 1;       // Initial estimate, never low
    int n1 = (n + (num / n)) / 2;
    while (n1 < n) {
        n = n1;
        n1 = (n + (num / n)) / 2;
    } // end while
    return n;
} // end Isqrt()

int main(int argc, char *argv[]) {
    //int n = atoi(argv[1]);
    //printf("%d %d\n", squareroot(n), (int)sqrt(n));
    //test();
    // std::cout<<(1<<15)<<std::endl;
    // std::cout<<babylonian_correct(atoi(argv[1]))<<std::endl;
    std::cout<<binary_isqrt(atoi(argv[1]))<<std::endl;
    std::cout<<"Test binary search: "<<std::endl;
    std::cout<<time(0)<<std::endl;
    test(binary_isqrt);
    std::cout<<time(0)<<std::endl;
    
    std::cout<<"Test babylonian: "<<std::endl;
    std::cout<<time(0)<<std::endl;
    test(babylonian_correct);
    std::cout<<time(0)<<std::endl;
}
