/**
 * Return the length of the last word in a string.
 */

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        int len = strlen(s);
        if (len==0) {return 0;}
        int res=0;
        bool fl=false;
        while (len>=0){
            if ( (s[len]>='a' && s[len]<='z')||(s[len]>='A' && s[len]<='Z') ){fl=true; res=res+1;}
            if (s[len]==' ' && fl) { return res;}
            len--;
        }
        if (fl) {return res;}
        if (!fl){return 0;}
    }
};
