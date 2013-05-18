class Solution {
public:
    string minWindow(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        map<char, int> char_count;
        for (int i = 0; i < T.size(); ++i) {
            ++char_count[T[i]];
        }
        
        map<char, int> tmp;
        int min_win_len = S.size() + 1;
        int min_win_beg = -1;
        int min_win_end = S.size() + 1;
        for (int i = 0, j = 0, c = 0; i < S.size() && j < S.size();) {
            while (j < S.size() && c < T.size()) {
                ++tmp[S[j]];
                if (char_count[S[j]] != 0 && tmp[S[j]] <= char_count[S[j]]) {
                    ++c;
                }
                ++j;    // always advance end
            }
            if (c == T.size() && j - i < min_win_len) {
                // got a window
                min_win_len = j - i;
                min_win_beg = i;
                min_win_end = j;
            }
            while (tmp[S[i]] > char_count[S[i]] && i < S.size()) {
                --tmp[S[i]];
                ++i;
            }
            if (c == T.size() && j - i < min_win_len) {
                min_win_len = j - i;
                min_win_beg = i;
                min_win_end = j;
            }
            --tmp[S[i]]; ++i; --c;
        }
        if (min_win_len == S.size() + 1) {
            return "";
        }
        return S.substr(min_win_beg, min_win_end - min_win_beg);
    }
};
