#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>

int compute_overlap(int jump_table[], const char* pattern) {
    if(pattern == 0 || jump_table == 0) {
        // the Bjane recommended way to test NULL
        // set jump_table to -1 when no input is given
        return -1;      // invalid input
    }

    int len = strlen(pattern);  // c style string
    jump_table[0] = -1;

    for(int i = 1; i <= len; ++i) {
        jump_table[i] = jump_table[i-1] + 1;
        while(jump_table[i] > 0 && pattern[jump_table[i] - 1] != pattern[i - 1] ) {
            jump_table[i] = jump_table[jump_table[i] - 1] + 1;
        }
    }
    return 0;
}

bool test_compute_overlap_with_identical_pattern() {
    const char* pattern = "aaaaaaaa";
    int* jump_table = new int[strlen(pattern) + 1];
    compute_overlap(jump_table, pattern);
    for( int i = 0; i <= strlen(pattern); ++i ) {
        assert(jump_table[i] == i - 1);
    }
    return true;
}

int kmp(const char* text, const char* pattern) {
    if(text == 0 || pattern == 0) {
        return -1;
    }
    
    int pattern_len = strlen(pattern);
    int *jump_table = new int[pattern_len + 1];
    
    compute_overlap(jump_table, pattern);
    int loop_count = 0;
    for(int i = 0, j = 0; text[i] != '\0'; ++i) {
        for( ; pattern[j] != '\0'; ) {
            loop_count++;
            if(text[i] == pattern[j]) {
                i++; j++;
            } else {
                break;
            }
        }

        if(pattern[j] == '\0') {
            // find a match
            printf("find a match at %d\n", i - pattern_len);
            printf("Loop count: %d\n", loop_count);
            return 0;
        } else {
            // no match lookup jumptable
            if( jump_table[j] != -1 ) {
                // jump table is safe
                j = jump_table[j];
            }
        }
    }
    printf("Loop count: %d\n", loop_count);
    return 1;
}

int main(int argc, char* argv[]) {
    const char *t;
    const char *p;
    if( argc < 2 ) {
        t = "aaaaaa";
        p = "aaa";
    } else {
        t = argv[1];
        p = argv[2];
  }
    printf("%s\n%s\n", t, p);
    if(test_compute_overlap_with_identical_pattern()) {
        printf("Overlap test passed\n");
    }

    kmp(t, p);
}
