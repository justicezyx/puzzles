#include "common/common.h"

// Question: 
// Given an pizza being separated into n pieces, each piece has a weight;
// these n numbers are input as an array.
// Now, starting with you, each of the 2 players pick one and the opponent
// pick 2 immediately on the left and right of the picked one.
// How to maximize the weight picked by you?

// Given an input array of n pieces. 
// find the sequence that skips exact 1 element and has the maximum sum,
// while at the same time has a length of ceil(n / 3).
// the below is a brute force approach.
std::pair<int,int> brute_force(const std::vector<int>& input) {
    // assume all input are positive; there is no negative sized pizza after all.
    int max = 0;
    int maxi = -1;
    int l = (input.size() + 2) / 3;
    for (int i = 0; i < input.size(); i++) {
        int sum = 0;
        for (int j = 0; j < l; j++) {
            sum += input[(i + 2 * j) % input.size()];
        }

        if (sum > max) {
            max = sum;
            maxi = i;
        }
    }
    return std::make_pair(max, maxi);
}

static int MOD_MAX = 10;
int rand_mod() {
    return rand() % MOD_MAX;
}

void test() {
    srand(time(0));
    std::vector<int> input = puzzles::rnd_fill(9, rand_mod); 
    puzzles::print(input.begin(), input.end());
    std::pair<int,int> res = brute_force(input);
    std::cout<<res.first<<" "<<res.second<<std::endl;
}

int main() {
    test();
}
    
