/*
Given a 2D board and a word, find if the word exists in the grid.
 
The word can be constructed from letters of sequentially 
cell, where "adjacent" cells are those horizontally or vertically
neighboring. The same letter cell may not be used more than once.
 
For example,
Given board =
 
[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/
class Solution {
public:
    int m;
    int n;
 
    static const int dir_x[4];
    static const int dir_y[4];
 
    bool dfs(vector<vector<char> > &board, const string &word, int pos, int x, int y) {
        if (board[x][y] != word[pos]) {
            return false;
        }
        
        if (pos >= word.size() - 1) {
            return true;
        }
        
        char c = board[x][y];
        board[x][y] = '.';
        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dir_x[dir];
            int ny = y + dir_y[dir];
            if(nx >= 0 && nx < m && ny >= 0 && ny < n) {                
                if(dfs(board, word, pos+1, nx, ny)) {
                    return true;
                }
            }
        }
        board[x][y] = c;
        return false;
    }
 
    bool exist(vector<vector<char> > &board, string word) {
        m = board.size();
        n = board[0].size();
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (dfs(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
};
 
const int Solution::dir_x[] =  {-1, 0, 1, 0};
const int Solution::dir_y[] =  {0, 1, 0, -1};
