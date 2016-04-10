// A circular buffer remove or add items both at the begin and end sides.

#include "common/assert.h"

#include <vector>

template <typename ItemType>
class CircularBuffer {
  public:
    CircularBuffer(int size) : data_(size) {}
    ItemType front() {
      return data_[begin_];
    }
    void push_front(ItemType v) {
      --begin_;
      ++size_;
      if (begin_ < 0) {
        begin_ = data_.size() - 1;
      }
      data_[begin_] = v;
    }
    ItemType pop_front() {
      ItemType result = front();
      begin_ = (begin_ + 1) % data_.size();
      --size_;
      return result;
    }

    ItemType back() {
      return data_[end_-1];
    }
    ItemType pop_back() {
      ItemType result = back();
      --end_;
      --size_;
      if (end_ == 0) {
        end_ = size_;
      }
      return result;
    }
    void push_back(ItemType v) {
      ++size_;
      ++end_;
      if (end_ > data_.size()) {
        end_ = 1;
      }
      data_[end_-1] = v;
    }
    int size() {
      return size_;
    }
    int capacity() {
      return data_.size();
    }

  private:
    std::vector<ItemType> data_;

    int begin_ = 0;
    int end_ = 0;
    int size_ = 0;
};

void test_CircularBuffer() {
  CircularBuffer<int> buffer(2);
  EXPECT_EQ(0, buffer.size());

  buffer.push_back(12345);
  EXPECT_EQ(1, buffer.size());
  EXPECT_EQ(12345, buffer.front());
  EXPECT_EQ(12345, buffer.back());

  EXPECT_EQ(12345, buffer.pop_front());
  EXPECT_EQ(0, buffer.size());

  buffer.push_front(54321);
  EXPECT_EQ(1, buffer.size());
  EXPECT_EQ(54321, buffer.pop_back());
  EXPECT_EQ(0, buffer.size());

  buffer.push_back(13);
  buffer.push_back(37);
  EXPECT_EQ(2, buffer.size());
  EXPECT_EQ(13, buffer.pop_front());
  EXPECT_EQ(37, buffer.pop_front());
  EXPECT_EQ(0, buffer.size());
}

int main() {
  test_CircularBuffer();
}
