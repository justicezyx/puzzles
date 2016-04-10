#include "common/common.h"

void helper(vector<int>& nums, int pos, vector<vector<int>>& res) {
    cout<<"pos:"<<pos<<endl;

    if (pos >= nums.size()) {
        res.push_back(nums);
        return;
    }
    
    helper(nums, pos+1, res);
    for (int i = pos+1; i < nums.size(); ++i) {
        swap(nums[pos], nums[i]);
        helper(nums, pos+1, res);
        swap(nums[pos], nums[i]);
    }
}

vector<vector<int>> permute(const vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> tmp = nums;
    helper(tmp, 0, res);
    return res;
}

void test() {
    cout<<"test begin"<<endl;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);

    cout<<"argument finished"<<endl;
    vector<vector<int>> res = permute(nums);
    cout<<"permuteation finished"<<endl;
    for (int i = 0; i < res.size(); ++i) {
        print(res[i].begin(), res[i].end());
    }
}

int main() {
    test();
}
