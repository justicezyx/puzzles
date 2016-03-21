#include "common.h"
using namespace std;

bool check_words(const string& S, int s, int begin, int len, const map<string,int>& wc) {
    map<string,int> count;
    for (int i = 0; i < len; i += s) {
        cout<<"i:"<<i<<endl;
        string t = S.substr(begin + i, s);
        cout<<"t:"<<t<<endl;
        if (wc.find(t) == wc.end()) {
            cout<<"cannot find "<<t<<endl;
            return false;
        }
        ++count[t];
    }
    return count == wc;
}

int main() {
    string S = "barfoothefoobarman";
    map<string,int> wc;
    wc["foo"] = 1;
    wc["bar"] = 1;
    int size = 3;
    int len = 6;
    vector<int> res;
    for (int i = 0; i + len <= S.size(); ++i) {
        //cout<<"i:"<<i<<" i+len:"<<i+len<<endl;
        if (check_words(S, size, i, len, wc)) {
            //cout<<"matched"<<endl;
            
            //cout<<"i:"<<i<<" i+len:"<<i+len<<endl;
            res.push_back(i);
            i += len;
        } else {
            ++i;
        }
    }
    //cout<<"ressize:"<<res.size()<<endl;
    cout << check_words(S, 3, 0, 6, wc)<<endl;
    cout << check_words(S, 3, 9, 6, wc)<<endl;
}
