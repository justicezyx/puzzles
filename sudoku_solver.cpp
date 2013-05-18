class Solution {
public:
    // 返回第一个空白的位置，如果没找到就返回 (-1, -1)
    pair<int, int> findFirstEmpty(const vector< vector<char> >& board) {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (board[i][j] == '.') return make_pair(i, j);
        return make_pair(-1, -1);
    }

    // 检查连续的 9 个格子是否有效
    bool isValid(const vector<char>& vec) {
        vector<bool> occur(9, false);
        for (int i = 0; i < 9; ++i) {
            if (isdigit(vec[i])) {
                if (occur[vec[i]-'1']) return false;
                else occur[vec[i]-'1'] = true;
            }
        }
        return true;
    }

    // 检查往某个位置填入一个数之后整个 board 是否有效（只需要考虑当前行、
    // 当前列和所属的田字格）
    bool isValidBoard(const vector< vector<char> >& board, pair<int, int> pos) {
        // 检查当前行是否有效
        if (!isValid(board[pos.first])) return false;

        // 检查当前列是否有效
        vector<char> column(9);
        for (int i = 0; i < 9; ++i)
            column[i] = board[i][pos.second];
        if (!isValid(column)) return false;

        // 检查所在的田字格是否有效
        int block_row = pos.first / 3;
        int block_col = pos.second / 3;
        vector<char> block;
        for (int i = block_row * 3; i < block_row * 3 + 3; ++i)
            for (int j = block_col * 3; j < block_col * 3 + 3; ++j)
                block.push_back(board[i][j]);
        if (!isValid(block)) return false;

        // 如果以上都有效，则返回 true
        return true;
    }

    // 检查从当前局面开始是否能够得到最终合法有效的解
    bool solveSudoku(vector<vector<char> >& board) {
        // 如果没有找到空白的格子，说明已经填满了，成功返回
        pair<int, int> pos = findFirstEmpty(board);
        if (pos.first == -1 && pos.second == -1)
            return true;
        // 否则依次尝试往当前格子中填入数字 1-9，并判断能否得到可行的解
        for (int i = 1; i <= 9; ++i) {
            board[pos.first][pos.second] = i + '0';
            if (isValidBoard(board, pos) && solveSudoku(board))
                return true;
            // 恢复原样
            board[pos.first][pos.second] = '.';
        }
        return false;
    }
};
