class Solution {
public:
    string intToRoman(int num) {
        const static char* Roman = "IVXLCDM";
        string ret;
        for (int base = 0; num; num /= 10, base += 2) {
            int x = num % 10;
            switch (x) {
                case 1: case 2: case 3:
                    ret = string(x, Roman[base]) + ret;
                    break;
                case 4:
                    ret = Roman[base+1] + ret;
                    ret = Roman[base] + ret;
                    break;
                case 5:
                    ret = Roman[base+1] + ret;
                    break;
                case 6: case 7: case 8:
                    ret = string(x-5, Roman[base]) + ret;
                    ret = Roman[base+1] + ret;
                    break;
                case 9:
                    ret = Roman[base+2] + ret;
                    ret = Roman[base] + ret;
                    break;
                default:
                    break;
            }
        }
        return ret;
    }
};
