#include "common.h"

bool validate(const std::string& input) {
    std::stack<char> h;
    
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == ')') {
            if (h.empty() || h.top() != '(') {
                return false;
            }
            
            h.pop();
        } else {
            h.push(input[i]);
        }
    }

    // after parsing, there should not be any left elements in stack
    // otherwise the input is invalid.
    return h.empty();
}

void test() {
    std::string brakets = ")))";
    std::cout<<validate(brakets)<<std::endl;
}

int main(int argc, char* argv[]) {
    std::cout<<validate(std::string(argv[1]))<<std::endl;
}
