#include "common.h"
using namespace std;

struct cover_direction {
    bool left_dia;
    bool right_dia;
    bool vertical;
    cover_direction() {
        left_dia = false;
        right_dia = false;
        vertical = false;
    }
    
    bool can_place() {
        return !left_dia && !right_dia && !vertical;
    }
};

vector<cover_direction> place(vector<cover_direction> cur, int pos) {
    cur[pos].left_dia = true;
    cur[pos].right_dia = true;
    cur[pos].vertical = true;
    
    vector<cover_direction> next(cur.size());
    for (int i = 0; i < cur.size(); ++i) {
        if (cur[i].can_place()) {
            continue;
        }
        if (cur[i].left_dia) {
            if (i - 1 >= 0) {
                next[i-1].left_dia = true;
            }
        }
        if (cur[i].right_dia) {
            if (i + 1 < next.size()) {
                next[i+1].right_dia = true;
            }
        }
        if (cur[i].vertical) {
            next[i].vertical = true;
        }
    }
    return next;
}

ostream& operator<<(ostream& os, const cover_direction& dir) {
    os<<"left_dia:"<<dir.left_dia;
    os<<" right_dia:"<<dir.right_dia;
    os<<" vertical:"<<dir.vertical<<endl;
    return os;
}

int main() {
    vector<cover_direction> cur(2);
    print(cur.begin(), cur.end());
    vector<cover_direction> next = place(cur, 0);
    print(next.begin(), next.end());
}
