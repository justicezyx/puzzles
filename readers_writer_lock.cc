#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>

class ReadersWriterLock {
 public:
  void WriteLock();
  void WriteUnlock();
  void ReadLock();
  void ReadUnlock();

 private:
  std::mutex mutex_;
  std::condition_variable cond_var_;

  bool writer_active_ = false;
  int waiting_writers_count_ = 0;
  int active_readers_count_ = 0;
};

void ReadersWriterLock::WriteLock() {
  std::unique_lock<std::mutex> lock(mutex_);
  ++waiting_writers_count_;
  while (writer_active_ || active_readers_count_ > 0) {
    cond_var_.wait(lock);
  }
  writer_active_ = true;
  --waiting_writers_count_;
}

void ReadersWriterLock::WriteUnlock() {
  std::unique_lock<std::mutex> lock(mutex_);
  writer_active_ = false;
  cond_var_.notify_all();
}

void ReadersWriterLock::ReadLock() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (writer_active_ || waiting_writers_count_ > 0) {
    cond_var_.wait(lock);
  }
  ++active_readers_count_;
}

void ReadersWriterLock::ReadUnlock() {
  std::unique_lock<std::mutex> lock(mutex_);
  --active_readers_count_;
  if (active_readers_count_ == 0) {
    cond_var_.notify_all();
  }
}

int main(int argc, char** argv) {
  ReadersWriterLock lock;
  std::thread a([&lock]() {
    for (int i = 0; i < 10; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
      lock.WriteLock();
      std::cout << "[i-1: " << i << std::flush;
      std::cout << "]" << std::endl;
      lock.WriteUnlock();
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
