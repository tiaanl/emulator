#include "vm/emulator/bus.h"

#include <cstdio>

namespace vm {

// static
Bus::Bus() : first_node_(nullptr) {}

void Bus::add_range(Address addr, U32 size, FetchFunc fetch_func, StoreFunc store_func, void* obj) {
  auto new_node =
      bus_node_pool_.emplace(addr.flat(), size, fetch_func, store_func, obj, first_node_);
  first_node_ = new_node;
}

U8 Bus::fetch(Address addr) const {
  auto flat = addr.flat();
  for (auto current = first_node_; current; current = current->next) {
    if (flat >= current->start_address && flat < current->start_address + current->size) {
      return current->fetch_func(current->obj, flat - current->start_address);
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", addr.segment(), addr.offset());
  assert(0);  // No address in range.

  return 0x00;
}

void Bus::store(Address addr, U8 value) const {
  auto flat = addr.flat();
  for (auto current = first_node_; current; current = current->next) {
    if (flat >= current->start_address && flat < current->start_address + current->size) {
      current->store_func(current->obj, flat - current->start_address, value);
      return;
    }
  }

  printf("Address out of range: 0x%04x:0x%04x\n", addr.segment(), addr.offset());
  assert(0);  // No address in range.
}

}  // namespace vm
