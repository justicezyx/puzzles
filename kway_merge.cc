#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <vector>

bool is_sorted(int a[], int s) {
    for(int i = 0; i < s - 2; i++) {
        if(a[i] > a[i+1]) {
            return false;
        }
    }
    return true;
}

void kway_merge_log(int *input[ ], int size[ ], int k, int output[ ]);
void kway_merge_heap(int *input[ ], int size[ ], int k, int output[ ]);

void kway_merge(int *input[ ], int size[ ], int k, int output[ ]) {
    // "input" is a list of arrays
    // there are "k" arrays in "input"
    // their sizes are in array "size" of the same size "k"
    // merged output is in array "output"
    int *merge_index = new int[k]();    // the indexes to the values to be merged in each input array
    //int *merge_index = new int[k];
    //for(int i = 0; i < k; i++) {
        //printf("%d ", merge_index[i]);
    //}
    //printf("\n");

    int oi = 0; // output index

    while(true) {
        bool completed = true;
        int min;
        int min_index;
        for(int i = 0; i < k; i++) {
            if(merge_index[i] < size[i]) {
                min = input[i][merge_index[i]];
                min_index = i;
                completed = false;
                break;
            }
        }

        if(completed) {
            break;
        }

        int begin = min_index + 1;
        for(int i = begin; i < k; i++) {
            if(merge_index[i] < size[i] &&
                    input[i][merge_index[i]] < min) {
                min = input[i][merge_index[i]];
                min_index = i;
            }
        }

        output[oi++] = min;
        merge_index[min_index]++;
    }
}

void test(int size[ ], int k) {
    // generate the input and output arrays
    int** input = new int*[k];
    int total_size = 0;
    for(int i = 0; i < k; i++) {
        total_size += size[i];
        input[i] = new int[size[i]];
        for(int j = 0; j < size[i]; j++) {
            input[i][j] = rand() % 1000;
        }
        std::sort(input[i], input[i] + size[i]);
    }
    int *output = new int[total_size];

    //kway_merge(input, size, k, output);
    //kway_merge_log(input, size, k, output);
    kway_merge_heap(input, size, k, output);

    // print out the output
    for(int i = 0; i < total_size; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    // check validity
    if(!is_sorted(output, total_size)) {
        printf("fuck wrong\n");
    } else {
        printf("passed, input array size: ");
        for(int i = 0; i < k; i++) {
            printf("%d ", size[i]);
        }
        printf("\n");
    }
    
    kway_merge(input, size, k, output);
    //kway_merge_log(input, size, k, output);

    // print out the output
    for(int i = 0; i < total_size; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    // free the allocated memory
    for(int i = 0; i < k; i++) {
        delete[] input[i];
    }
    delete[] input;
    delete[] output;
}

int main() {
    int size[] = {10, 10, 10, 100};
    int k = sizeof(size) / sizeof(int);
    test(size, k);
}

void kway_merge_log(int *input[ ], int size[ ], int k, int output[ ]) {
    typedef std::multimap<int, std::pair<int, int> > map_t;
    typedef map_t::iterator iter_t;

    map_t merge_value_index;
    int oi = 0;
    
    for(int i = 0; i < k; i++) {
        if(size[i] <= 0) { continue; }

        int val = input[i][0];
        int array_idx = i;
        int idx = 0;

        merge_value_index.insert(std::make_pair(val, std::make_pair(array_idx, idx) ) );
    }

    while(!merge_value_index.empty()) {
        iter_t min = merge_value_index.begin();
        int val = min->first;
        int array_idx = min->second.first;
        int idx = min->second.second;
        printf("%d %d %d\n", val, array_idx, idx);
        
        merge_value_index.erase(min);

        if(idx + 1 < size[array_idx]) {
            // next element is valid
            merge_value_index.insert(std::make_pair( input[array_idx][idx+1], std::make_pair(array_idx, idx+1) ) );
        }

        output[oi++] = val;
    }
}


typedef std::pair<int, std::pair<int, int> > pair_t;
struct comp {
    bool operator()(const pair_t& lhs, const pair_t& rhs) const {
        return lhs.first >= rhs.first;
    }
};

void kway_merge_heap(int *input[ ], int size[ ], int k, int output[ ]) {
    typedef std::pair<int, std::pair<int, int> > pair_t;
    std::vector<pair_t> merge_candidate;
    merge_candidate.reserve(k);

    for(int i = 0; i < k; i++) {
        merge_candidate.push_back(std::make_pair(input[i][0], std::make_pair(i, 0)));
    }
    
    make_heap(merge_candidate.begin(), merge_candidate.end(), comp());
    
    int oi = 0;
    while(!merge_candidate.empty()) {
        pop_heap(merge_candidate.begin(), merge_candidate.end(), comp());

        pair_t min = merge_candidate.back();

        merge_candidate.pop_back();
        int val = min.first;
        int array_idx = min.second.first;
        int idx = min.second.second;
        output[oi++] = val;
        
        if(idx + 1 < size[array_idx]) {
            min = std::make_pair(input[array_idx][idx+1], std::make_pair(array_idx, idx+1));
            merge_candidate.push_back(min);
            push_heap(merge_candidate.begin(), merge_candidate.end(), comp());
        }
    }
}
