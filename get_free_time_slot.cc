// Given a list busy time range for multiple users; find the time slots for
// which all users are free.

#include "common/assert.h"
#include "common/util.h"

#include <iostream>
#include <vector>
#include <utility>

bool all_finished(
    const std::vector<std::vector<std::pair<int, int>>>& busy_slots,
    std::vector<int>& search_pos) {
  for (int i = 0; i < search_pos.size(); i++) {
    if (search_pos[i] < busy_slots[i].size()) {
      return false;
    }
  }
  return true;
}

// For the pointed position in |search_pos| find the left most start point.
int left_most(
    const std::vector<std::vector<std::pair<int, int>>>& busy_slots,
    std::vector<int>& search_pos) {
  // Note that the time stamp is in [0, -), here use -1 to indicate an
  // uninitialized value.
  int result = -1;

  for (int i = 0; i < search_pos.size(); i++) {
    if (search_pos[i] >= busy_slots[i].size()) {
      continue;
    }
    if (result == -1) {
      result = busy_slots[i][search_pos[i]].first;
    } else {
      result = std::min(result, busy_slots[i][search_pos[i]].first);
    }
  }
  return result;
}

int right_most(const std::vector<std::pair<int, int>>& slots) {
  int result = slots.front().second;
  for (const auto& slot : slots) {
    result = std::max(result, slot.second);
  }
  return result;
}

int right_most(
    const std::vector<std::vector<std::pair<int, int>>>& busy_slots,
    std::vector<int>& search_pos) {
  // Note that the time stamp is in [0, -), here use -1 to indicate an
  // uninitialized value.
  int result = -1;

  for (int i = 0; i < search_pos.size(); i++) {
    if (search_pos[i] >= busy_slots[i].size()) {
      continue;
    }
    if (result == -1) {
      result = busy_slots[i][search_pos[i]].second;
    } else {
      result = std::min(result, busy_slots[i][search_pos[i]].second);
    }
  }
  return result;
}

// Get the slots that overlap with |time| for all users, and advance the
// |search_pos| for the user has an overlapping slot.
std::vector<std::pair<int, int>> get_overlapped_slots(
    const std::vector<std::vector<std::pair<int, int>>>& busy_slots,
    const int time, std::vector<int>& search_pos) {
  std::vector<std::pair<int, int>> result;
  for (int i = 0; i < search_pos.size(); i++) {
    int& slot_idx = search_pos[i];
    if (slot_idx >= busy_slots[i].size()) {
      continue;
    }
    const std::pair<int, int>& slot = busy_slots[i][slot_idx];
    if (slot.first <= time) {
      slot_idx++;
      result.push_back(slot);
    }
  }
  return result;
}

void test_get_overlapped_slots() {
  std::vector<int> search_pos({0, 0});
  auto result = get_overlapped_slots(
      {{{0, 1}, {4, 8}}, {{3, 4}, {5, 6}}},
      0, search_pos);
  for (const auto& pair : result) {
    std::cout << "{" << pair.first << "," << pair.second << "}" << std::endl;
  }
  EXPECT_EQ(std::vector<int>({1, 0}), search_pos);
}

std::vector<std::pair<int, int>> get_free_time_slots(
    const std::vector<std::vector<std::pair<int, int>>>& busy_slots) {
  std::vector<std::pair<int, int>> result;
  if (busy_slots.empty()) {
    return result;
  }

  int left = 0;
  int right = 0;
  std::vector<int> search_pos(busy_slots.size(), 0);

  while (!all_finished(busy_slots, search_pos)) {
    auto right = left_most(busy_slots, search_pos);
    if (left < right) {
      result.push_back(std::make_pair(left, right));
    }

    left = right;
    auto open_slots = get_overlapped_slots(busy_slots, left, search_pos);
    while (!open_slots.empty()) {
      left = right_most(open_slots);
      open_slots = get_overlapped_slots(busy_slots, left, search_pos);
    }
  }
  return result;
}

void test_get_free_time_slots() {
  auto result = get_free_time_slots({
      {{0, 1}, {2, 3}},
      {{0, 1}, {2, 3}, {4, 5}},
      {{0, 2}, {4, 5}}});
  for (const auto& pair : result) {
    std::cout << ToString(pair) << std::endl;
  }
}

int main() {
  test_get_overlapped_slots();
  test_get_free_time_slots();
}
