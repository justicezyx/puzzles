class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        std::map<std::string, std::list<std::string>> h;
        for (int i = 0; i < strs.size(); ++i) {
            std::string str = strs[i];
            std::sort(str.begin(), str.end());
            h[str].push_back(strs[i]);
        }
        
        std::vector<std::string> res;
        for (const auto& pair : h) {
            if (pair.second.size() > 1) {
                res.insert(res.end(), pair.second.begin(), pair.second.end());
            }
        }
        return res;
    }
};
