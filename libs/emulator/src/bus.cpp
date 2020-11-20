#include "emulator/bus.h"

namespace emulator {

// static
Bus Bus::create() {
  Bus result = {};
  result.first_node = nullptr;
  return result;
}

void Bus::add_range(U16 start_address, U16 size, FetchFunc fetch_func, StoreFunc store_func,
                    void* obj) {
  auto new_node =
      bus_node_pool.emplace(start_address, size, fetch_func, store_func, obj, first_node);
  first_node = new_node;
}

U8 Bus::fetch(U16 address) {
  for (auto current = first_node; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      return current->fetch_func(current->obj, address);
    }
  }

  return 0x00;
}

void Bus::store(U16 address, U8 value) {
  for (auto current = first_node; current; current = current->next) {
    if (address >= current->start_address && address < current->start_address + current->size) {
      current->store_func(current->obj, address, value);
      return;
    }
  }
}

}  // namespace emulator
