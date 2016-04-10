// Implement a class that provides a
// RunAfter(std::function<void()> fn, std::chrono::duration delay)
// Such that |fn| will be executed in time period of |delay|.

#include <chrono>
#include <vector>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>

struct ScheduledJob {
  // The function that represent the actual job.
  std::function<void()> job;

  // The time point when the job should be executed.
  std::chrono::system_clock::time_point scheduled_run_time;
};

bool ScheduledJobLess(const ScheduledJob& lhs, const ScheduledJob& rhs) {
  return lhs.scheduled_run_time > rhs.scheduled_run_time;
}

struct Clock {
  virtual std::chrono::system_clock::time_point now() = 0;
};

struct SystemClock : public Clock {
  std::chrono::system_clock::time_point now() override {
    return std::chrono::system_clock::now();
  }
};

struct TestClock : public Clock {
  std::chrono::system_clock::time_point now() override {
    if (idx_ == to_return_.size()) {
      return to_return_.back();
    }
    return to_return_[idx_++];
  }

  int idx_;
  std::vector<std::chrono::system_clock::time_point> to_return_;
};

class Executor {
  public:
    Executor(std::unique_ptr<Clock> clock) : clock_(std::move(clock)) {}

    void RunAfter(
        std::function<void()> fn, std::chrono::milliseconds delay_ms) {
      pending_queue_.push_back({fn, Now() + delay_ms});
      std::push_heap(
          pending_queue_.begin(), pending_queue_.end(), ScheduledJobLess);
    }

    void Run(std::chrono::seconds duration) {
      std::chrono::system_clock::time_point end = Now() + duration;
      if (duration == std::chrono::seconds::zero()) {
        end = std::chrono::system_clock::time_point::max();
      }

      int i = 0;
      while (true) {
        auto now = Now();

        if (now >= end) {
          break;
        }
        if (pending_queue_.empty()) {
          std::cout << "Queue is empty, sleep for 0.1 second..." << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
          continue;
        }
        const auto& job = pending_queue_.front();
        if (now >= job.scheduled_run_time) {
          job.job();
        }
        std::pop_heap(
            pending_queue_.begin(), pending_queue_.end(), ScheduledJobLess);
        pending_queue_.pop_back();
      }
    }

  private:
    std::chrono::system_clock::time_point Now() {
      return clock_->now();
    }
    std::vector<ScheduledJob> pending_queue_;
    std::unique_ptr<Clock> clock_;
};

void test_Executor() {
  auto now = std::chrono::system_clock::now();
  auto one_sec_later = now + std::chrono::seconds(1);
  auto two_sec_later = now + std::chrono::seconds(2);
  auto ten_sec_later = now + std::chrono::seconds(10);

  TestClock* test_clock = new TestClock();
  test_clock->idx_ = 0;
  test_clock->to_return_ = {now, now, one_sec_later, one_sec_later, one_sec_later, two_sec_later, ten_sec_later};

  std::unique_ptr<Clock> clock(test_clock);
  Executor executor(std::move(clock));

  executor.RunAfter([]() {
      std::cout << "test_fn_1" << std::endl;
  }, std::chrono::milliseconds(100));

  executor.RunAfter([]() {
      std::cout << "test_fn_2" << std::endl;
  }, std::chrono::milliseconds(200));

  executor.Run(std::chrono::seconds(5));
}

int main() {
  test_Executor();
}
