#include "common/common.h"

// need this to store the move for
// 1. there are m stons left
// 2. this move can take up to n stones.
std::vector<std::vector<int> > init_2d_array(int m, int n, int v) {
    std::vector<std::vector<int> > res(m);
    for (int i = 0; i < m; ++i) {
        res[i].resize(n, v);
    }
    return res;
}

bool win_strategy(int n) {
    if (n == 1) { return true; }
    if (n == 2) { return false; }

    std::vector<std::vector<int> > dp = init_2d_array(n + 1, n + 1, -1);
    dp[1][1] = 1;
    dp[2][1] = -1;
    dp[2][2] = 1;
    
    for (int cur_count = 3; cur_count <= n; ++cur_count) {
        for (int pick = 1; pick <= cur_count; ++pick) {
            int left = cur_count - pick;
            int oponent_max = std::min(2 * pick, left);
            
            bool will_win = true;
            for (int opo_pick = 1; opo_pick <= oponent_max; ++opo_pick) {
                std::cout<<"left: "<<left<<" pick: "<<opo_pick<<std::endl;

                if (dp[left][opo_pick] != -1) {
                    // There is a move of the oponent that will win.
                    will_win = false;
                }
            }

            if (will_win) {
                dp[cur_count][pick] = 1;
            }
        }
    }
    
    for (int i = 1; i <= n - 1; ++i) {
        if (dp[n][i] == 1) return true;
    }
}

int main(int argc, char* argv[]) {
    std::cout<<win_strategy(atoi(argv[1]))<<std::endl;
}
