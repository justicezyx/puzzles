#include "common.h"

struct comp {
    bool operator()(const int& a, const int& b) const {
        return a > b;
    }
};

// given an array, starting with all 1's and ending with all 0's.
// find the index of the first appearance of 0
int first_zero(const vector<int>& nums) {
    int b = 0;
    int e = nums.size();
    while (b < e) {
        int mid = b + (e - b) / 2;
        int tmp = nums[mid];
        cout<<"mid element:"<<tmp<<endl;
        if (tmp == 1) {
            b = mid + 1;
        } else {
            e = mid;
        }
    }
    return b;
}

void test() {
    vector<int> nums {0, 0, 0, };
    cout<<first_zero(nums)<<endl;
    comp cmp;
    cout<<distance(nums.begin(), upper_bound(nums.begin(), nums.end(), 1, comp()))<<endl;
}

int main() {
    test();
}
        
