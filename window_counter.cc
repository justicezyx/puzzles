// Implement a counter class. It provides Inc() and Get() methods. Inc()
// increments the counter by 1. Get() returns the counter incremented during a
// fixed window T.

#include <chrono>
#include <deque>
#include <iostream>
#include <thread>

std::chrono::system_clock::time_point Now() {
    return std::chrono::system_clock::now();
}

bool heap_less(
    const std::pair<int, std::chrono::system_clock::time_point>& lhs,
    const std::pair<int, std::chrono::system_clock::time_point>& rhs) {
  return lhs.second < rhs.second;
}

std::string ToString(const std::chrono::system_clock::time_point& time_point) {
  auto t = std::chrono::system_clock::to_time_t(time_point);
  return std::ctime(&t);
}

class WindowCounter {
  public:
    WindowCounter(std::chrono::seconds duration) : window_(duration) {}

    void Inc() {
      auto now = Now();

      counter_++;
      history_.push_back(std::make_pair(counter_, now));

      auto limit = Now() - window_;
      auto itor = std::lower_bound(
          history_.begin(), history_.end(), std::make_pair(0, limit), heap_less);
      history_.erase(history_.begin(), itor);
    }

    int Get() {
      auto now = Now();
      std::chrono::system_clock::time_point limit = now - window_;

      auto itor = std::lower_bound(
          history_.begin(), history_.end(), std::make_pair(0, limit), heap_less);

      if (itor == history_.end()) {
        history_.erase(history_.begin(), history_.end());
        return 0;
      } else {
        auto result = history_.back().first - itor->first + 1;
        history_.erase(history_.begin(), itor);
        return result;
      }
    }

  private:
    int counter_ = 0;
    std::deque<std::pair<int, std::chrono::system_clock::time_point>> history_;
    std::chrono::seconds window_;
};

void test_WindowCounter() {
  WindowCounter counter(std::chrono::seconds(2));
  auto now = Now();
  while (Now() < now + std::chrono::seconds(10)) {
    counter.Inc();
    std::cout << "Counter: " << counter.Get() << std::endl;
  }
}

int main() {
  test_WindowCounter();
}
