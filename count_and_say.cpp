class Solution {
public: 
string countAndSay(int n) {

    if (n == 1)
        return "1";

    string str_con;
    string temp_ans = "";
    string ans = "1";

    for (int i=1; i<n; ++i)
    {
        int ctr = 0;
        char temp_char = ans[0];
        int ans_size = ans.size();

        for (int j=0; j<ans_size; ++j)
        {
            if (ans[j] == temp_char)
                ctr++;

            else if (ans[j] != temp_char)
            {
                ostringstream convert;
                convert << ctr;
                str_con = convert.str();
                temp_ans = temp_ans + str_con + temp_char;
                ctr = 1;
                temp_char = ans[j];
            }

            if (j == ans.size()-1)
            {
                    ostringstream convert;
                    convert << ctr;
                    str_con = convert.str();
                    ans = temp_ans + str_con + temp_char;
                    temp_ans = "";
            }
        }
    }

    return ans;
 }
};
