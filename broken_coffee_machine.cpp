/**
 * There is a coffee machine has 3 buttons for small, medium, and large.
 * For some reason, it is broken. Instead of output exactly a certain amount,
 * each button produces volume in a range [lower, upper].
 * 
 * Now given a cup of a volume of N, check if the coffee machine could guarantee
 * that the cup will be filled with at least M volume and without overflow.
 * 
 * Example
 * small [100, 200]
 * medium [200, 300]
 * large [400, 500]
 * 
 * M = 200, N = 400
 * return true, press small twice guarantees that the cup will have at least 200
 * but no overflow is possible.
 */

#include "common.h"

typedef pair<int, int> range_t;

bool solve(const vector<range_t>& vols, int idx, range_t partial, const range_t& cup);
bool broken_coffee_machine_fill(const vector<range_t>& vols, const range_t& cup);

void test() {
    range_t a(100, 200);
    range_t b(200, 400);
    vector<range_t> vols;
    vols.push_back(a);
    vols.push_back(b);
    
    range_t cup(400, 500);

    if (broken_coffee_machine_fill(vols, cup)) {
        cout<<"Can fill"<<endl;
    }
}

int main() {
    test();
}

bool broken_coffee_machine_fill(const vector<range_t>& vols, const range_t& cup) {
    range_t partial(0, 0);
    return solve(vols, 0, partial, cup);
}

bool solve(const vector<range_t>& vols, int idx, range_t partial, const range_t& cup) {
    if (partial.first >= cup.first && partial.second <= cup.second) {
        return true;
    }
    
    if (partial.second > cup.second) {
        return false;
    }
    
    if (idx >= vols.size()) {
        return false;
    }

    if (solve(vols, idx+1, partial, cup)) {
        return true;
    }

    do {
        partial.first += vols[idx].first;
        partial.second += vols[idx].second;
        if (solve(vols, idx+1, partial, cup)) {
            return true;
        }
    } while (partial.second <= cup.second);
    return false;
}


