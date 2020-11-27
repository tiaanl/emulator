#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "bus.h"
#include "vm/emulator/address.h"

namespace vm {

class Memory {
public:
  Memory();
  ~Memory();

  Address allocate_page();

  static U8 fetch_func(void* obj, U32 flat) {
    auto memory = (Memory*)obj;
    auto page_num = flat / 0xFFFF;
    assert(page_num < memory->pages_.size());
    return memory->pages_[page_num].data[flat % 0xFFFF];
  }

  static void store_func(void* obj, U32 flat, U8 value) {
    auto memory = (Memory*)obj;
    auto page_num = flat / 0xFFFF;
    assert(page_num < memory->pages_.size());
    memory->pages_[page_num].data[flat % 0xFFFF] = value;
  }

private:
  struct Page {
    U8 data[0xFFF];
  };

  std::vector<Page> pages_;
};

inline void map_memory_page_to_bus(Bus* bus, Memory* memory, Address addr) {
  bus->add_range(addr, 0xFFFF, Memory::fetch_func, Memory::store_func, memory);
}

}  // namespace vm
