class Solution {
public:
    void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int>::iterator it = num.end() - 1;
    
        while (it!=num.begin() && (*(it-1) >= *it)) it--; //find *(it-1) < *it
        if (it == num.begin()) { //last element, rewind to the first one, i.e, ascending order
            reverse(it, num.end());
            return;
        }
        it--; //left elem to be exchanged
    
        vector<int>::iterator rit = it+1;
        while (rit!=num.end() && *rit > *it) rit++;
        rit--; //right elem to be exchanged
    
        //swap (left,right), then reverse right part to ascending order
        iter_swap(it, rit);
        reverse(it+1, num.end());
    }
};
