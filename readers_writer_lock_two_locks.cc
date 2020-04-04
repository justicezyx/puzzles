#include <iostream>
#include <mutex>
#include <thread>

struct ReadersWriterLock {
  void WriteLock() {
    g_.lock();
  }

  void WriteUnlock() {
    g_.unlock();
  }

  void ReadLock() {
    std::lock_guard<std::mutex> r(r_);
    ++readers_count_;
    if (readers_count_ == 1) {
      g_.lock();
    }
  }

  void ReadUnlock() {
    std::lock_guard<std::mutex> r(r_);
    --readers_count_;
    if (readers_count_ == 0) {
      g_.unlock();
    }
  }

  std::mutex g_;
  std::mutex r_;
  int readers_count_ = 0;
};

int main(int argc, char** argv) {
  ReadersWriterLock lock;
  std::thread a([&lock]() {
    for (int i = 0; i < 10; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
      lock.ReadLock();
      std::cout << "[i-1: " << i << std::flush;
      std::cout << "]" << std::endl;
      lock.ReadUnlock();
    }
  });
  std::thread b([&lock]() {
    for (int i = 0; i < 10; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
      lock.WriteLock();
      std::cout << "[i-2: " << i << std::flush;
      std::cout << "]" << std::endl;
      lock.WriteUnlock();
    }
  });
  a.join();
  b.join();
  return 0;
}
