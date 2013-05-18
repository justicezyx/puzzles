ass Solution {
public:
    bool isNumber(const char *s) {
        if (s == NULL || s[0] == '\0') return false;
        bool cansign = true;
        bool cane = false;
        bool havee = false;
        bool candot = true;
        bool onlyspace = false;
        bool havenum = false;
        bool numbegin = false;
        while(*s != '\0') {
            char c = *(s++);
            if (c == ' '){
                if (numbegin)
                    onlyspace = true;
                continue;//skip space
            } else if (onlyspace) {
                return false;
            }
            if (c == '+' || c == '-') {
                if(!cansign) return false;
                cansign = false;
                numbegin = true;
                continue;
            }
            if (c == 'e') {
                if(!cane) return false;
                cane = false;
                havenum = false;
                numbegin = true;
                cansign = true;
                havee = true;
                candot = false;
                continue;
            }
            if (c == '.') {
                if(!candot) return false;
                candot = false;
                numbegin = true;
                cansign = false;
                continue;
            }
            if (c >= '0' && c <= '9') {
                havenum = true;
                numbegin = true;
                cansign = false;
                if(!havee) cane = true;
            } else {
                return false;
            }
        }
        return havenum;
    }
};
