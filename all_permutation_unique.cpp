#include "common.h"

void permute(string& nums, int pos, vector<string>& res);

vector<string> permute(const string& nums) {
    string chars = nums;
    vector<string> res;
    permute(chars, 0, res);
    return res;
}

void permute(string& nums, int pos, vector<string>& res) {
    if (pos >= nums.size()) {
        res.push_back(nums);
        return;
    }
    
    permute(nums, pos+1, res);
    for (int i = pos+1; i < nums.size(); ++i) {
        swap(nums[pos], nums[i]);
        permute(nums, pos+1, res);
        swap(nums[pos], nums[i]);
    }
}

void test() {
    string s = "abcd";
    vector<string> res = permute(s);
    cout<<"number of permutaion:"<<res.size()<<endl;
    print(res.begin(), res.end());
}

int main() {
    test();
}
