#include <iostream>
#include <vector>

#include "common.h"

struct position {
    int r;
    int l;
};

int mark(bool **can_use, int r, int l, int tr, int tl);

void max_word_matrix(char **m, int r, int l) {
    position* char_poses = new position[256];
    for (int i = 0; i < 256; i++) {
        char_poses[i].r = -1;
        char_poses[i].l = -1;
    }

    bool **can_use = new bool*[r];
    for (int i = 0; i < r; i++) {
        can_use[i] = new bool[l];
        for (int j = 0; j < l; j++) {
            can_use[i][j] = true;
        }
    }

    // asumming all chars are unique
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < l; j++) {
            char c = m[i][j];
            char_poses[c].r = i;
            char_poses[c].l = j;
        }
    }

    std::vector<int> res;
    res.reserve(256);

    for (int i = 0; i < 256; i++) {
        int tmp_r = char_poses[i].r;
        int tmp_l = char_poses[i].l;
        
        if (tmp_r != -1 && tmp_l != -1 && can_use[tmp_r][tmp_l]) {
            res.push_back(i);
            mark(can_use, r, l, tmp_r, tmp_l);
        }
    }
            
    print(res.begin(), res.end());
}

int mark(bool **can_use, int r, int l, int tr, int tl) {
    // the lower left corner of (tr, tl).
    for (int i = tr + 1; i < r; i++) {
        for (int j = 0; j < tl; j++) {
            can_use[i][j] = false;
        }
    }

    // the upper right corner of (tr, tl).
    for (int i = 0; i < tr; i++) {
        for (int j = tl + 1; j < l; j++) {
            can_use[i][j] = false;
        }
    }
}

void test() {
    char ** data = new char*[10];
    char c = 0;
    for (int i = 0; i < 10; i++) {
        data[i] = new char[10];
        for (int j = 0; j < 10; j++) {
            data[i][j] = c++;
        }
    }

    max_word_matrix(data, 10, 10);
}

int main() {
    test();
}
