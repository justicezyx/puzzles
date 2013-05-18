#include <iostream>
#include <cstdio>

#include "common.h"

int main() {
    int a = convert<int>("100");
    printf("%d\n", a);
    test_has_enough_arg();
}
