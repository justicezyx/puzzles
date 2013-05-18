#include "common.h"

int longestConsecutive(const std::vector<int>& num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    std::map<int,std::pair<int,int> > h;
    typedef std::map<int,std::pair<int,int> >::iterator iter;
    int max = 0;
    for (int i = 0; i < num.size(); ++i) {
        std::cout<<"num: "<<num[i]<<std::endl;
        if (h.find(num[i]) != h.end()) {
            continue;
        }
        int left = 0;
        int right = 0;
        iter nl = h.find(num[i] - 1);
        if (nl != h.end()) {
            left = std::max(left, 1 + nl->second.first);
            std::cout<<"prev: "<<num[i] - 1<<" left:"<<nl->second.first<<" right: "<<nl->second.second<<std::endl;
        }
        
        nl = h.find(num[i] + 1);
        if (nl != h.end()) {
            right = std::max(right, 1 + nl->second.second);
            std::cout<<"next: "<<num[i] + 1<<" left:"<<nl->second.first<<" right: "<<nl->second.second<<std::endl;
        }
        h[num[i]] = std::make_pair(0, 0);
        h[num[i] - left] = std::make_pair(0, std::max(h[num[i] - left].second, left + right));
        h[num[i] + right] = std::make_pair(std::max(h[num[i] + right].first, left + right), 0);
        max =std::max(max, left + right + 1);
        std::cout<<" -left:"<<num[i] - left<<" right:"<<left + right<<" +right:"<<num[i] + right<<" left: "<<left + right<<std::endl;
    }
    return max;
}

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::unordered_map<int,std::pair<int,int>> h;
        typedef std::unordered_map<int,std::pair<int,int>>::iterator iter;
        int max = 0;
        for (int i = 0; i < num.size(); ++i) {
            if (h.find(num[i]) != h.end()) {
                continue;
            }
            h[num[i]];
            int left = 0;
            int right = 0;
            iter nl = h.find(num[i] - 1);
            if (nl != h.end()) {
                left = std::max(left, 1 + nl->second.first);
            }
            nl = h.find(num[i] + 1);
            if (nl != h.end()) {
                right = std::max(right, 1 + nl->second.second);
            }
            h[num[i]-left].second = std::max(h[num[i]-left].second, left+right);
            h[num[i]+right].first = std::max(h[num[i]+right].first, left+right);
            max =std::max(max, left + right + 1);
        }
        return max;
    }
};

void test() {
    int A[] = {1,3,5,-1,5,-1,-6,2,3,-4,9,-1,1,9,-1,7,5,0,8,-7,9,-2,-1,7};
    std::vector<int> input(A, A + sizeof(A) / sizeof(int));
    print(input.begin(), input.end());
    std::cout<<std::endl;

    std::cout<<longestConsecutive(input)<<std::endl;
}

int main() {
    test();
}
