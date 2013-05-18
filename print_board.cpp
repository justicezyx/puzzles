#include "common.h"
using namespace std;

vector<string> print_board(const vector<int>& poses) {
    int n = poses.size();
    vector<string> res(n, string(n, '.'));
    for (int i = 0; i < poses.size(); ++i) {
        res[i][poses[i]] = 'Q';
    }
    return res;
}

int main() {
    vector<int> poses;
    poses.push_back(0);
    poses.push_back(1);
    poses.push_back(2);
    vector<string> board = print_board(poses);
    print(board.begin(), board.end());
}
