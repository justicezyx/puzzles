// Given a list busy time range for multiple users; find the time slots for
// which all users are free.

// Use similar approach as skyline. Maintain a list of open slots for a sweeping
// line; and count the slots that are currently overlapping with the sweeping
// line.
//
// Records the point the overlapping slots increases from 0 to 1 (ending of a
// free slot), and from 1 to 0 (beginning).

#include "common/util.h"

#include <iostream>
#include <vector>

struct TimeSlot {
  int begin;
  int end;
};

struct EndPoint {
  int time;
  bool is_begin;
};

EndPoint Begin(const TimeSlot& slot) {
  return EndPoint({slot.begin, true});
}

EndPoint End(const TimeSlot& slot) {
  return EndPoint({slot.end, false});
}

std::vector<EndPoint> EndPoints(const std::vector<TimeSlot>& slots) {
  std::vector<EndPoint> result;
  for (const auto& slot : slots) {
    result.push_back(Begin(slot));
    result.push_back(End(slot));
  }
  return result;
}

typedef std::vector<EndPoint>::const_iterator itor_type;
bool heap_less(
    const std::pair<itor_type, itor_type>& lhs,
    const std::pair<itor_type, itor_type>& rhs) {
  return lhs.first->time > rhs.first->time;
}

std::vector<TimeSlot> GetFreeTimeSlots(
    const std::vector<std::vector<TimeSlot>>& busy_slots) {
  std::vector<TimeSlot> result;
  if (busy_slots.empty()) {
    return result;
  }

  std::vector<std::vector<EndPoint>> end_points;
  end_points.reserve(busy_slots.size());

  for (const auto& slots : busy_slots) {
    end_points.push_back(EndPoints(slots));
  }

  // Each item is a pair of current iterator and the end iterator.
  std::vector<std::pair<itor_type, itor_type>> heap;
  heap.reserve(busy_slots.size());
  for (const auto& points : end_points) {
    heap.push_back(std::make_pair(points.begin(), points.end()));
  }
  std::make_heap(heap.begin(), heap.end(), heap_less);

  int left = 0;
  int right = 0;
  int open_slots = 0;
  while (!heap.empty()) {
    auto pair = heap.front();
    std::pop_heap(heap.begin(), heap.end(), heap_less);
    heap.pop_back();

    EndPoint curr = *pair.first;
    if (curr.is_begin) {
      open_slots++;
      if (open_slots == 1) {
        right = curr.time;
        if (right > left) {
          std::cout << "right: " << right << " left: " << left << std::endl;
          result.push_back({left, right});
        }
      }
    } else {
      open_slots--;
      if (open_slots == 0) {
        left = curr.time;
      }
    }

    ++pair.first;
    if (pair.first != pair.second) {
      heap.push_back(pair);
      std::push_heap(heap.begin(), heap.end(), heap_less);
    }
  }
  return result;
}

void test_GetFreeTimeSlots() {
  auto result = GetFreeTimeSlots({
      {{0, 1}, {2, 3}},
      {{0, 1}, {2, 3}, {4, 5}},
      {{0, 2}, {4, 5}}});
  for (const auto& slot : result) {
    std::cout << "{" << slot.begin << "," << slot.end << "}" << std::endl;
  }
}

int main() {
  test_GetFreeTimeSlots();
}
