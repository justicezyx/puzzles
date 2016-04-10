class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> set;
        sort(num.begin(), num.end());
        int *array = new int[num.size()];
        combinationSum(num, target, 0, array, 0, set);
        delete array;
        return set;
    }
    
    void combinationSum(vector<int> &num, int target, int index, int *array,
        int count, vector<vector<int>> &set) {

        if (target < 0)
            return;
        if (target == 0) {
            vector<int> a;
            for (int i=0; i<count; i++)
                a.push_back(array[i]);
            set.push_back(a);
            return;
        }
        if (index >= num.size())
            return;
        int t = num[index];
        int j = index+1;
        while (j<num.size() && num[j] == t) j++;
        combinationSum(num, target, j, array, count, set);
        for (int k=index; k<j; k++) {
            t = num[index] * (k-index+1);
            if (t>target)
                return;
            array[count++] = num[k];
            combinationSum(num, target-t, j, array, count, set);
        }
    }
};
