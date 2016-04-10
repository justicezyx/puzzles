#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstring>

clock_t quick_selection(int* begin, int* end, int k) {
    clock_t begin_time = clock();
    std::nth_element(begin, begin + k - 1, end);
    clock_t used_time = clock() - begin_time;
    std::sort(begin, begin + k);
    for(int i = 0; i < k; i++) {
        std::cout<<begin[i]<<" ";
    }
    std::cout<<std::endl;
    return used_time;
}

clock_t heap_selection(int* begin, int* end, int k) {
    clock_t begin_time = clock();
    int *heap = new int[k];
    memcpy(heap, begin, k * sizeof(int));
    std::make_heap(heap, heap + k);
    for(int* i = begin + k; i != end; ++i) {
        if(*i < heap[0]) {
            std::pop_heap(heap, heap + k);
            heap[k-1] = *i;
            std::push_heap(heap, heap + k);
        }
    }
    clock_t used_time = clock() - begin_time;
    std::sort(heap, heap + k);
    for(int i = 0; i < k; i++) {
        std::cout<<heap[i]<<" ";
    }
    std::cout<<std::endl;
    return used_time;
}

int main(int argc, char *argv[] ) {
    int size = 100000000; // 100milion
    if(argc > 1) {
        size = atoi(argv[1]);
    }
    int *input1 = new int[size];
    int *input2 = new int[size];
    srand(time(0));
    for(int i = 0; i < size; i++) {
        int t = rand();
        input1[i] = t;
        input2[i] = t;
    }

    clock_t qst = quick_selection(input1, input1 + size, 100);
    clock_t hst = heap_selection(input2, input2 + size, 100);

    std::cout<<"quick selection: "<<qst<<" heap selection: "<<hst<<std::endl;
}
