#include "common.h"

pair<int,int> partion(int* array, int begin, int end, int v) {
    int low = begin;
    int high = end - 1;
    int i = begin;
    while (i <= high && low <= high) {
        if (array[i] < v) {
            if (i == low) {
                ++i;
            } else {
                swap(array[i], array[low]);
            }
            ++low;
        } else if (array[i] > v) {
            swap(array[i], array[high]);
            --high;
        } else {
            ++i;
        }
    }
    return make_pair(low, high);
}

int quick_selection(int* array, int len, int k) {
    int begin = 0;
    int end = len;
    while (true) {
        pair<int,int> tmp = partion(array, begin, end, array[k]);
        if (k >= tmp.first && k <= tmp.second) {
            return array[k];
        } else {
            if (tmp.first > k) {
                end = tmp.first;
            } else {
                begin = tmp.second;
            }
        }
    }
}

void test() {
    int array[] = {1, 5, 2, 1, 4, 4, 5, 8, 9};
    pair<int,int> res = partion(array, 0, sizeof(array) / sizeof(int), 4);
    cout<<res.first<<" "<<res.second<<endl;
    print(array, array + sizeof(array) / sizeof(int));
    cout<<quick_selection(array, sizeof(array) / sizeof(int), 7);
    print(array, array + sizeof(array) / sizeof(int));
}

int main() {
    test();
}
