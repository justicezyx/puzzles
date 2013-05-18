#include <iostream>
#include <string>

int mincut(const std::string& s) {
    int* dp = new int[s.size() + 1];
    int** is_par = new int*[s.size()];
    for (int i = 0; i < s.size(); i++) {
        is_par[i] = new int[s.size()];
        memset(is_par[i], 0, s.size());
        is_par[i][0] = 1; // substring starting at i with length 1 is a parlindrome.
        dp[i] = i;
    }
    dp[s.size()] = s.size();
    
    for (int i = 2; i <= s.size(); i++) {
        for (int j = 1; j <= i; j++) {
            if (s[i-j] == s[i-1] && (j <= 2 || is_par[i-j+1][j-2])) {
                is_par[i-j][j] = 1;
                dp[i] = std::min(1 + dp[i - j], dp[i]);
            }
        }
    }

    return dp[s.size()] - 1;
}

void test() {
    std::string s = "aabaa";
    std::cout<<mincut(s)<<std::endl;
}
            
int main(int argc, char* argv[]) {
    std::cout<<mincut(argv[1])<<std::endl;
}
