#include "common.h"

#include <cstring>

// the buffer's should be k.
int read_k(char* buf, int k) {
    static int count = 0;
    std::cout<<count<<std::endl;
    if (count < 2) {
        count++;
        return k;
    }
    if (count == 2) {
        count++;
        return 1;
    }
    if (count > 2) {
        count++;
        return 0;
    }
}

int read_n(char* buf, int n) {
    int count = n / k;
    int res = 0;
    for (int i = 0; i < count; ++i, buf += k) {
        int read_count = read_k(buf, k);
        res += read_count;
        if (read_count == 0) { return res; }
    }
    char* tmp_buf = new char[k];
    int read_count = read_k(tmp_buf, k);   
    int copy_count = std::min(read_count, n - res);
    memcpy(buf, tmp_buf, copy_count);
    std::cout<<"copy count:"<<read_count<<std::endl;
    return res + copy_count;
}

int main() {
    char* buf = new char[9];
    std::cout<<read_n(buf, 20)<<std::endl;
}
