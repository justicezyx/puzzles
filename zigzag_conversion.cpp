class Solution {
public:
    string convert(string s, int nRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = s.length();
        if(len < 3 || nRows == 1) return s;
    
        vector<vector<char> > matrix(nRows);
    
        bool down = true;
        for(int i = 0, row = 0; i < len;) {
    
            if(down) {
                if(row < nRows) matrix[row++].push_back(s[i++]);
                else {
                    down = !down;
                    row -= 2;
                }
            }
            else {
                if(row >= 0) matrix[row--].push_back(s[i++]);
                else {
                    down = !down;
                    row += 2;
                }
            }
        }
    
        string r = "";
        vector<vector<char> >::iterator it = matrix.begin();
        for(; it != matrix.end(); ++it) {
            vector<char>::iterator it2 = (*it).begin();
            for(; it2 != (*it).end(); ++it2) {
                r += *it2;
            }
        }
    
        return r;
    }
};
