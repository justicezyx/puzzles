
class Solution {
public:
    struct cover_direction {
        bool left_dia;
        bool right_dia;
        bool vertical;
        cover_direction() {
            left_dia = false;
            right_dia = false;
            vertical = false;
        }
        
        bool can_place() {
            return !left_dia && !right_dia && !vertical;
        }
    };
    
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<cover_direction> cur_row(n);
        vector<vector<string> > res;
        h(cur_row, vector<int>(), n, res);
        return res;
    }
    
    void h(vector<cover_direction> cur_row, 
           vector<int> partial, int n,
           vector<vector<string> >& res) {
               
        if (partial.size() == n) {
            res.push_back(print_board(partial));
            return;
        }
        
        for (int i = 0; i < cur_row.size(); ++i) {
            if (cur_row[i].can_place()) {
                vector<int> tmp = partial;
                vector<cover_direction> next_row = place(cur_row, i);
                tmp.push_back(i);
                h(next_row, tmp, n, res);
            }
        }
    }
    
    vector<cover_direction> place(vector<cover_direction> cur, int pos) {
        cur[pos].left_dia = true;
        cur[pos].right_dia = true;
        cur[pos].vertical = true;
        
        vector<cover_direction> next(cur.size());
        for (int i = 0; i < cur.size(); ++i) {
            if (cur[i].can_place()) {
                continue;
            }
            if (cur[i].left_dia) {
                if (i - 1 >= 0) {
                    next[i-1].left_dia = true;
                }
            }
            if (cur[i].right_dia) {
                if (i + 1 < next.size()) {
                    next[i+1].right_dia = true;
                }
            }
            if (cur[i].vertical) {
                next[i].vertical = true;
            }
        }
        return next;
    }
    
    vector<string> print_board(const vector<int>& poses) {
        int n = poses.size();
        vector<string> res(n, string(n, '.'));
        for (int i = 0; i < poses.size(); ++i) {
            res[i][poses[i]] = 'Q';
        }
        return res;
    }
};
