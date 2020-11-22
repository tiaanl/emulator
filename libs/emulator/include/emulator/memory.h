#pragma once

#include <cassert>
#include <memory>

namespace emulator {

class Memory {
public:
  explicit Memory(U16 size);
  ~Memory();

  U16 size() const {
    return size_;
  }

  U8* data() const {
    return data_.get();
  }

  static U8 load(void* obj, U16 addr) {
    auto memory = (Memory*)obj;
    assert(addr < memory->size_);
    return memory->data_[addr];
  }

  static void store(void* obj, U16 addr, U8 value) {
    auto memory = (Memory*)obj;
    assert(addr < memory->size_);
    memory->data_[addr] = value;
  }

private:
  U16 size_;
  std::unique_ptr<U8[]> data_;
};

}  // namespace emulator
