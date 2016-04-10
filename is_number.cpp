#include "common/common.h"
using namespace std;

/** 
 *Validate if a given string is numeric.
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 */

bool isNumber(const char *s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (s == NULL) { return false; }
    if (strlen(s) == 0) { return false; }
    istringstream iss(s);
    double val = 1.0;
    double val2 = -1.0;
    iss >> val;
    iss.seekg(0, std::ios::beg);
    iss >> val2;
    std::cout<<"number:"<<val<<std::endl;
    std::string str;
    iss >> str;
    if ((val > 1.0 && val < 1.0) || (val > -1.0 && val < 1.0)) {
        return iss.eof();    
    }
    return false;
}

int main() {
    std::cout<<isNumber("   1.   ");
}
