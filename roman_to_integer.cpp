class Solution {
public:
    
    int romanToInt(string s) {
        if (s.length()==0) return 0;
    
        map<char, int> m;
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
    
        int n = s.length();
        int sum = m[s[n-1]];
        for (int i=n-2; i>=0; i--) {
            if (m[s[i+1]] <= m[s[i]])
                sum += m[s[i]];
            else
                sum -= m[s[i]];
        }
        return sum;
    }
};
