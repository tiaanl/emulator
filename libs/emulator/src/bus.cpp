#include "emulator/bus.h"

#include <cstdio>

namespace emulator {

// static
Bus Bus::create() {
  Bus result = {};
  result.first_node = nullptr;
  return result;
}

void Bus::add_range(U16 segment, U16 offset, U32 size, FetchFunc fetch_func, StoreFunc store_func,
                    void* obj) {
  U32 address = (segment << 4u) + offset;
  auto new_node = bus_node_pool.emplace(address, size, fetch_func, store_func, obj, first_node);
  first_node = new_node;
}

U8 Bus::fetch(U16 segment, U16 offset) const {
  auto address = (segment << 4u) + offset;
  for (auto current = first_node; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      return current->fetch_func(current->obj, address - current->start_address);
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", segment, offset);
  assert(0);  // No address in range.

  return 0x00;
}

void Bus::store(U16 segment, U16 offset, U8 value) const {
  auto address = (segment << 4u) + offset;
  for (auto current = first_node; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      current->store_func(current->obj, address - current->start_address, value);
      return;
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", segment, offset);
  assert(0);  // No address in range.
}

}  // namespace emulator
