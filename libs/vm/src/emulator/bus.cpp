#include "vm/emulator/bus.h"

#include <cstdio>

namespace vm {

// static
Bus::Bus() : first_node_(nullptr) {}

void Bus::add_range(U16 segment, U16 offset, U32 size, FetchFunc fetch_func, StoreFunc store_func,
                    void* obj) {
  U32 address = (segment << 4u) + offset;
  auto new_node = bus_node_pool_.emplace(address, size, fetch_func, store_func, obj, first_node_);
  first_node_ = new_node;
}

U8 Bus::fetch(U16 segment, U16 offset) const {
  U16 address = (segment << 4u) + offset;
  for (auto current = first_node_; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      return current->fetch_func(current->obj, address - current->start_address);
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", segment, offset);
  assert(0);  // No address in range.

  return 0x00;
}

void Bus::store(U16 segment, U16 offset, U8 value) const {
  U16 address = (segment << 4u) + offset;
  for (auto current = first_node_; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      current->store_func(current->obj, address - current->start_address, value);
      return;
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", segment, offset);
  assert(0);  // No address in range.
}

}  // namespace vm
