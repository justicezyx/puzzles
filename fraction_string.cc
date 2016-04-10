#include "common/common.h"

std::string fraction_lessone(int n, int d);
std::string fraction(int n, int d) {
    assert(d != 0);

    std::string res;
    if (n >= d) {
        std::ostringstream oss;
        oss<<(n / d);
        res += oss.str();
        res.push_back('.');
    } else {
        res += "0.";
    }

    res += fraction_lessone(n % d, d);
    return res;
}
    
struct vector_asmap {
    std::vector<int> pos;
    vector_asmap(int m) : pos(m + 1, -1) { }
    bool contains(int c) {
        return pos[c] != -1;
    }

    int& operator[](int c) {
        return pos[c];
    }
};

std::string fraction_lessone(int n, int d) {
    assert(n < d);
    assert(d != 0);

    int r = n;
    vector_asmap reminder_pos_map(d + 1);
    std::vector<char> t;
    int pos = 0;

    while (r != 0 && !reminder_pos_map.contains(r)) {
        std::cout<<"reminder: "<<r<<" pos: "<<pos<<std::endl;
        char q = (10 * r / d) + '0';
        t.push_back(q);
        reminder_pos_map[r] = pos;

        // next reminder.
        r = (10 * r) % d;
        ++pos;
    }
    
    if (r == 0) {
        // no reminder left.
        return std::string(t.begin(), t.end());
    } else {
        int rep_pos = reminder_pos_map[r];
        std::vector<char>::iterator i = t.begin();
        std::advance(i, rep_pos);
        std::string res(t.begin(), i);
        res.push_back('[');
        res += std::string(i, t.end());
        res.push_back(']');
        return res;
    }
}

void test() {
    std::string res = fraction(2, 3);
    std::cout<<res<<std::endl;
}

int main(int argc, char* argv[]) {
    std::cout<<fraction(atoi(argv[1]), atoi(argv[2]))<<std::endl;
}

