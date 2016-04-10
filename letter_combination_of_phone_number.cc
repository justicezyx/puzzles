class Solution {/*Straightforward, and easy**/
private:
    vector<string> rep;
    vector<string> result;
    void build(string const& digits, int digitIndex, string ss){
        int const num = digits[digitIndex]-'0';
        if (digitIndex + 1 == digits.length()){
            for(int buttonIndex = 0; buttonIndex < rep[num].length(); ++buttonIndex){
                result.push_back(ss+rep[num][buttonIndex]);
            }
            return;
        }
        for(int buttonIndex = 0; buttonIndex < rep[num].length(); ++buttonIndex){
            build(digits, digitIndex+1,ss+rep[num][buttonIndex]);
        }
        return;
    }
public:
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (digits.empty()) return vector<string>(1,"");
        result.clear();
        rep.resize(10);
        rep[2]="abc";
        rep[3]="def";
        rep[4]="ghi";
        rep[5]="jkl";
        rep[6]="mno";
        rep[7]="pqrs";
        rep[8]="tuv";
        rep[9]="wxyz";
        build(digits, 0, ""); 
        return result;
    }
};
