class Solution {
public:
    int cnt,upper;
    int totalNQueens(int n) {
       cnt = 0;
       upper = (1<<n)-1 ;
       Queen(0,0,0);
       return cnt;

    }
    void Queen(int row,int ld,int rd)
    {
          int pos,p;
          if(row!=upper)
            {
                pos = upper & (~(row | ld |rd));
                while(pos!=0)
                {
                    p = pos & (-pos);
                    pos = pos - p;
                    Queen(row+p,(ld+p)<<1,(rd+p)>>1);
                }
            }
         else ++cnt;
    }
};
