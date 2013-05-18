class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::map<std::string, std::list<std::string>> h;
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            std::sort(str.begin(), str.end());
            h[str].push_back(strs[i]);
        }
        
        std::vector<std::string> res;
        for (std::map<std::string, std::list<std::string>>::iterator itor = h.begin();
             itor != h.end();
             ++itor) {
            
            if (itor->second.size() > 1) {
                res.insert(res.end(), itor->second.begin(), itor->second.end());
            }
        }
        return res;
    }
};
