#include <iostream>
#include <sstream>

int bpf(int v) {
  int f = 2;
  int orig_v = v;
  while (f * f <= orig_v && f < v) {
    if (v % f == 0) {
      v /= f;
    } else {
      f++;
    }
  }
  return v;
}

int main(int argc, char** argv) {
  if (argc >= 2) {
    std::istringstream iss(argv[1]);
    int v = 0;
    iss >> v;
    std::cout << "v: " << v << std::endl;
    assert(!iss.rdbuf()->in_avail());
    std::cout << bpf(v) << std::endl;
  }
}
