class Solution {
public:
    void solve(vector<vector<char>> &board) {
        int m = board.size();
        if (m == 0) { return; }
        
        int n = board[0].size();
        if (n == 0) { return; }
        
        std::vector<std::vector<int>> visited(m);
        for (int i = 0; i < m; ++i) {
            visited[i].resize(n, 0);
        }
        
        for (int i = 0; i < n; ++i) {
            if (board[0][i] == 'O') dfs(board, visited, 0, i, m, n, 'O');
            
            if (m - 1 > 0 && board[m-1][i] == 'O') {
                dfs(board, visited, m-1, i, m, n, 'O');
            }
        }
        
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') dfs(board, visited, i, 0, m, n, 'O');
            
            if (n - 1 > 0 && board[i][n-1] == 'O') {
                dfs(board, visited, i, n-1, m, n, 'O');
            }
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j] && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
    
    void dfs(const std::vector<std::vector<char>>& board,
             std::vector<std::vector<int>>& visited,
             int i, int j, int m, int n, char c) {
         if (visited[i][j]) {
             return;
         }
         visited[i][j] = 1;
         
         if (i-1 > 0 && board[i-1][j] == c && !visited[i-1][j]) {
             dfs(board, visited, i-1, j, m, n, c);
         }
         if (i+1 < m && board[i+1][j] == c && !visited[i+1][j]) {
             dfs(board, visited, i+1, j, m, n, c);
         }
         if (j-1 > 0 && board[i][j-1] == c && !visited[i][j-1]) {
             dfs(board, visited, i, j-1, m, n, c);
         }
         if (j+1 < n && board[i][j+1] == c && !visited[i][j+1]) {
             dfs(board, visited, i, j+1, m, n, c);
         }
     }
};
