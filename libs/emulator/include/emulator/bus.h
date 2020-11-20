#pragma once

#include <base/object_pool.h>

namespace emulator {

struct Bus {
  using FetchFunc = U8 (*)(void*, U16);
  using StoreFunc = void (*)(void*, U16, U8);

  struct BusNode {
    U16 start_address;
    U16 size;
    FetchFunc fetch_func;
    StoreFunc store_func;
    void* obj;
    BusNode* next;
  };

  base::ObjectPool<BusNode> bus_node_pool;
  BusNode* first_node;

  static Bus create();

  void add_range(U16 start_address, U16 size, FetchFunc fetch_func, StoreFunc store_func,
                 void* obj);

  U8 fetch(U16 address);
  void store(U16 address, U8 value);
};

}  // namespace emulator
