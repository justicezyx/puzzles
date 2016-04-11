// Given multiple lists of sorted appearance positions of words, find the
// minimal range of words in the original text, which contains all words.
// The appearance position of a word is its index in the original text.

#include "common/util.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

typedef std::vector<int>::const_iterator itor_type;

struct HeapItem {
  // The index to the word. The pos_itor and end points to the position in the
  // word's position list.
  int word_index;

  // Iterator points to the word position in the input word sequence.
  itor_type pos_itor;

  // Iterator points to the end, when pos_itor == end, there is no more position
  // to search.
  itor_type end;
};

// Compares 2 HeapItem and returns true if lhs comes after rhs after sorting.
bool HeapLess(const HeapItem& lhs, const HeapItem& rhs) {
  return *lhs.pos_itor > *rhs.pos_itor;
}

bool heap_less(
    const std::tuple<int, itor_type, itor_type>& lhs,
    const std::tuple<int, itor_type, itor_type>& rhs) {
  return *std::get<1>(lhs) > *std::get<1>(rhs);
}

std::pair<int, int> GetMinimalSnippet(
    const std::vector<std::vector<int>>& positions) {
  if (positions.empty()) {
    return std::make_pair(0, 0);
  }

  int left = 0;
  int right = 0;

  std::vector<std::tuple<int, itor_type, itor_type>> heap;
  heap.reserve(positions.size());

  for (int i = 0; i < positions.size(); i++) {
    heap.push_back(
        std::make_tuple(i, positions[i].begin(), positions[i].end()));
  }
  std::make_heap(heap.begin(), heap.end(), heap_less);

  std::vector<std::tuple<int, itor_type, itor_type>> end_heap = heap;

  std::vector<int> word_count(positions.size(), 0);
  int unique_word_count = 0;

  std::pair<int, int> result(0, 1000);
  while (!heap.empty() && !end_heap.empty()) {
    // First increment the right end point of the window.
    while (!end_heap.empty()) {
      std::pop_heap(end_heap.begin(), end_heap.end(), heap_less);
      auto three_tuple = end_heap.back();
      end_heap.pop_back();

      int word_index = std::get<0>(three_tuple);
      right = *std::get<1>(three_tuple);

      std::get<1>(three_tuple)++;
      if (std::get<1>(three_tuple) != std::get<2>(three_tuple)) {
        end_heap.push_back(three_tuple);
        std::push_heap(end_heap.begin(), end_heap.end(), heap_less);
      }

      word_count[word_index]++;
      if (word_count[word_index] == 1) {
        unique_word_count++;
        if (unique_word_count == positions.size()) {
          break;
        }
      }
    }

    while (!heap.empty()) {
      std::pop_heap(heap.begin(), heap.end(), heap_less);
      auto three_tuple = heap.back();
      heap.pop_back();

      int word_index = std::get<0>(three_tuple);
      left = *std::get<1>(three_tuple);

      std::get<1>(three_tuple)++;
      if (std::get<1>(three_tuple) != std::get<2>(three_tuple)) {
        heap.push_back(three_tuple);
        std::push_heap(heap.begin(), heap.end(), heap_less);
      }

      word_count[word_index]--;
      if (word_count[word_index] == 0) {
        unique_word_count--;
        if (result.second - result.first > right - left) {
          result = std::make_pair(left, right);
        }
        break;
      }
    }
  }
  return result;
}

// This function is a straightforward window scan algorithm. The left and right
// side of the window is being kept increasing. The value being selected is from
// the input word position.
void test_GetMinimalSnippet() {
  std::vector<std::vector<int>> input = {
    {0, 100, 200},
    {10, 70, 150},
    {20, 70, 150},
  };
  auto result = GetMinimalSnippet(input);
  std::cout << "result: " << ToString(result) << std::endl;
}

int main() {
  test_GetMinimalSnippet();
}
