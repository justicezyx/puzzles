#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <utility>
#include <sstream>

template <typename T1, typename T2>
std::string ToString(const std::pair<T1, T2>& pair) {
  std::ostringstream oss;
  oss << "{" << pair.first << "," << pair.second << "}";
  return oss.str();
}

#endif  // UTIL_H
