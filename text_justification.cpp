#include "common.h"

using namespace std;

vector<string> fullJustify(vector<string> &words, int L) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    std::vector<std::string> res;
    if (words.empty()) { return res; }
    std::vector<std::vector<std::string> > lines;
    std::vector<int> line_lengths;
    for (int i = 0; i < words.size(); ) {
        std::cout<<"i:"<<i<<std::endl;
        std::vector<std::string> line;
        int line_length = 0;
        int char_num = 0;
        for (; i < words.size() && line_length <= L;) {
            std::cout<<"i:"<<i<<std::endl;
            int min_space = line.size();
            int new_len = line_length + words[i].size() + min_space;
            int new_char_num = char_num + words[i].size();
            if (new_len <= L) {
                std::cout<<"new len:"<<new_len<<std::endl;
                line.push_back(words[i]); ++i;
            }
            if (new_len >= L || i >= words.size()) {
                std::cout<<"new len:"<<new_len<<std::endl;
                int len = new_len > L ? char_num : new_char_num;
                line_lengths.push_back(len);
                lines.push_back(line); 
                std::cout<<"current line:";
                print(line.begin(), line.end());
                break;
            } else {
                line_length = new_len;
                char_num = new_char_num;
            }
        }
    }
    
    for (int i = 0; i < lines.size(); ++i) {
        std::cout<<"line number:"<<i<<std::endl;
        int len_length = line_lengths[i];
        std::vector<std::string>& line_words = lines[i];
        
        int spaces = L - len_length;
        int slots = line_words.size() - 1;
        int padding = 0;
        int word_space = 0;
        if (slots == 0) {
            padding = spaces;
            word_space = 0;
        } else {
            padding = spaces % slots;
            word_space = spaces / slots;
        }
        std::string line;
        line += line_words[0];
        line.insert(line.end(), padding, ' ');
        for (int j = 1; j < line_words.size(); ++j) {
            line.insert(line.end(), word_space, ' ');
            line += line_words[j];
        }
        res.push_back(line);
    }
    return res;
}

void test() {
    vector<string> input;
    input.push_back("a");
    input.push_back("b");
    input.push_back("c");
    input.push_back("d");
    input.push_back("e");
    int L = 3;
    std::vector<std::string> res = fullJustify(input, L);
}

int main() {
    test();
}

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> ret;
        int begin = 0, len = 0, n = words.size();
        for (int i = 0; i < n; ++i) {
            if (len + words[i].size() + (i - begin) > L) {
                ret.push_back(connect(words, begin, i - 1, len, L, false));
                begin = i;
                len = 0;
            } 
            len += words[i].size();
        }
        ret.push_back(connect(words, begin, n - 1, len, L, true));
        return ret;
    }

    string connect(vector<string> &words, int begin, int end, int len, int L, bool leftJustify) {
        string s;
        int n = end - begin + 1;
        for (int i = 0; i < n; ++i) {
            s += words[begin + i];
            addSpaces(s, i, n - 1, L - len, leftJustify);
        }

        if (s.size() < L) s.append(L - s.size(), ' ');
        return s;
    }

    void addSpaces(string &s, int i, int n, int L, bool leftJustify) {
        if (n < 1 || i > n - 1) return;
        int spaces = leftJustify ? 1 : (L / n + (i < (L % n) ? 1 : 0));
        s.append(spaces, ' ');
    }
};
    
   
["Don't","go","around","saying","the","world","owes","you","a","living;","the","world","owes","you","nothing;","it","was","here","first."], 30  
["Don't  go  around  saying  the","world   owes you a living; the","world owes you nothing; it was","here first.                   "]   
["Don't  go  around  saying  the","world  owes  you a living; the","world owes you nothing; it was","here first.                   "]    
  
