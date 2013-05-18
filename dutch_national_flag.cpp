#include "common.h"

template<typename RandomAccessIterator>
void dutch_national_flag_sort(RandomAccessIterator begin, RandomAccessIterator end) {
    RandomAccessIterator lower = begin;
    RandomAccessIterator upper = end - 1;

    // upper is the next position for writing the largest element
    // the element in the position still needs exmination
    for(RandomAccessIterator itor = begin; itor <= upper; ) {
        if(*itor < 0) {
            if (itor - begin == lower - begin) {
                // same.
                ++itor;
            } else {
                std::swap(*itor, *lower);
            }
            ++lower;
        } else if(*itor > 0) {
            std::swap(*itor, *upper);
            --upper;
        } else {
            ++itor;
        }
    }
}

template<typename RandomAccessIterator>
bool negative_positive_partition_check(RandomAccessIterator begin, RandomAccessIterator end) {
    int current = -1;
    for(RandomAccessIterator i = begin; i != end; ++i) {
        switch(current) {
            case -1:
                if(*i == 0) {
                    current = 0;
                } 
                if(*i > 0) {
                    current = 1;
                }
                break;
            case 0:
                if(*i < 0) {
                    return false;
                }

                if(*i > 0) {
                    current = 1;
                }
                break;
            case 1:
                if(*i <= 0) {
                    return false;
                }
                break;
        }
    }
    return true;
}

void test() {
    std::vector<int> v = rnd_fill(100, rnd);
    v.resize(0);
    v.push_back(0);
    v.push_back(0);
    v.push_back(1);
    dutch_national_flag_sort(v.begin(), v.end());
    print(v.begin(), v.end());
    if(!negative_positive_partition_check(v.begin(), v.end())) {
        std::cout<<"Test failed"<<std::endl;
    } else {
        std::cout<<"Test passed"<<std::endl;
    }
}
void sortColors(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int zero_pos = 0;
    int two_pos = n - 1;
    
    for (int i = 0; i < n && i <= two_pos && zero_pos < two_pos; ) {
        if (A[i] == 0) {
            swap(A[i], A[zero_pos]);
            if (i == zero_pos) { ++i; }
            ++zero_pos;
        } else if (A[i] == 1) {
            ++i;
        } else if (A[i] == 2) {
            swap(A[i], A[two_pos]);
            --two_pos;
        }
    }
}

int main() {
    test();
}
