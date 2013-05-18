#include <algorithm>
#include <iostream>
#include <iterator>

bool is_sorted(int a[], int s) {
    for(int i = 0; i < s - 2; i++) {
        if(a[i] > a[i+1]) {
            return false;
        }
    }
    return true;
}

void merge_backend(int a[], int b[], int sa, int sb) {
    if(sa <= 0 || sb <= 0 || sa < sb) { 
        return;
    }

    // a contas (sa - sb) number of integers
    int idx_a = sa - sb - 1;
    int idx_b = sb - 1;

    for(int i = sa - 1; i >= 0; i--) {
        if(idx_a < 0) {
            for(int j = i; j >= 0; j--) {
                a[j] = b[j];
            }
            break;
        }

        if(idx_b < 0) {
            break;
        }

        if(a[idx_a] > b[idx_b]) {
            a[i] = a[idx_a];
            idx_a--;
        } else {
            a[i] = b[idx_b];
            idx_b--;
        }
    }
}

void test(int sa, int sb) {
    int *a = (int*)malloc(sizeof(int) * (sa + sb));
    int *b = (int*)malloc(sizeof(int) * sb);

    for(int i = 0; i < sa; i++) {
        a[i] = rand();
    }
    for(int i = 0; i < sb; i++) {
        b[i] = rand();
    }

    //std::copy(a, a + sa, std::ostream_iterator<int>(std::cout, " "));
    //std::cout<<std::endl<<std::endl;

    //std::copy(b, b + sb, std::ostream_iterator<int>(std::cout, " "));
    //std::cout<<std::endl;

    //std::copy(b, b + sb, std::ostream_iterator<int>(std::cout, " "));
    //std::cout<<std::endl;

    std::sort(a, a + sa);
    std::sort(b, b + sb);
    merge_backend(a, b, sa + sb, sb);

    //std::copy(a, a + sa + sb, std::ostream_iterator<int>(std::cout, " "));
    //std::cout<<std::endl;

    if(!is_sorted(a, sa + sb)) {
        std::cout<<"fuck wrong, input array size: "<<sa<<" "<<sb<<std::endl;
    } else {
        std::cout<<"passed, input array size: "<<sa<<" "<<sb<<std::endl;
    }
    free(a);
    free(b);
}

void testall() {
    test(0, 0);
    test(100, 0);
    test(0, 100);
    test(100, 100);
    test(100, 10000);
}

int main(int argc, char *argv[]) {
    //int sa = atoi(argv[1]);
    //int sb = atoi(argv[2]);

    //test(sa, sb);
    testall();
}
