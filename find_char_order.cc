// Given a list of words that are sorted in alphabetic order. Return a sequence
// of all characters that follow the ordering specified in the word order.

#include "common/assert.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Return the first index for which the characters at this index from 2 input
// strings differ. For example, first_diff_index("aa", "ab") returns 1;
// first_diff_index("", "a") returns 0.
int first_diff_index(const std::string& a, const std::string& b) {
  int i = 0;
  for ( ; i < a.size() && i < b.size(); i++) {
    if (a[i] != b[i]) {
      return i;
    }
  }
  return i;
}

void test_first_diff_index() {
  EXPECT_EQ(0, first_diff_index("", ""));
  EXPECT_EQ(0, first_diff_index("", "a"));
  EXPECT_EQ(1, first_diff_index("a", "a"));
  EXPECT_EQ(1, first_diff_index("ab", "ac"));
  EXPECT_EQ(2, first_diff_index("ab", "abc"));
}

std::unordered_map<char, std::unordered_set<char>> get_predecessor_map(
    const std::vector<std::string>& words) {
  std::unordered_map<char, std::unordered_set<char>> result;
  for (int i = 0; i < words.size()-1; i++) {
    const auto& curr_word = words[i];
    const auto& next_word = words[i+1];
    auto diff_idx = first_diff_index(curr_word, next_word);
    if (diff_idx < curr_word.size() && diff_idx < next_word.size()) {
      result[next_word[diff_idx]].insert(curr_word[diff_idx]);
    }
    for (const auto c : curr_word) {
      result[c];
    }
  }
  for (const auto c : words.back()) {
    result[c];
  }
  return result;
}

void test_get_predecessor_map() {
  auto result = get_predecessor_map({"ab", "ac", "bd"});
  for (const auto& char_predecessor_pair : result) {
    std::cout << char_predecessor_pair.first << ": {";
    for (const auto c : char_predecessor_pair.second) {
      std::cout << c << ", ";
    }
    std::cout << "}" << std::endl;
  }
}

std::pair<bool, char> find_char_without_predecessor(
    const std::unordered_map<char, std::unordered_set<char>>& map) {
  for (const auto& v : map) {
    if (v.second.empty()) {
      return std::make_pair(true, v.first);
    }
  }
  return std::make_pair(false, ' ');
}

// From the current and the next word, we can the first position that characters
// differ and decide the order of the two characters.
std::string find_char_order(const std::vector<std::string>& words) {
  if (words.empty()) {
    return "";
  }
  if (words.size() == 1) {
    return words.front();
  }
  auto predecessor_map = get_predecessor_map(words);
  std::string result;
  while (!predecessor_map.empty()) {
    std::pair<bool, char> found =
      find_char_without_predecessor(predecessor_map);

    if (!found.first) {
      // There is no char that has no predecessor. Invalid input.
      return "";
    }
    predecessor_map.erase(found.second);
    result.push_back(found.second);

    for (auto& v : predecessor_map) {
      v.second.erase(found.second);
    }
  }
  return result;
}

void test_find_char_order() {
  EXPECT_EQ("abcd", find_char_order({"a", "b", "c", "d"}));
  EXPECT_EQ("", find_char_order({"a", "b", "a"}));
  EXPECT_EQ("a", find_char_order({"a", "a", "a"}));
  EXPECT_EQ("", find_char_order({}));
  EXPECT_EQ("abcd", find_char_order({"abcd"}));
}

int main() {
  test_first_diff_index();
  test_get_predecessor_map();
  test_find_char_order();
}
