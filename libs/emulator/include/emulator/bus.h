#pragma once

#include <base/object_pool.h>

namespace emulator {

struct Bus {
  using FetchFunc = U8 (*)(void*, U16);
  using StoreFunc = void (*)(void*, U16, U8);

  struct BusNode {
    U32 start_address;
    U32 size;
    FetchFunc fetch_func;
    StoreFunc store_func;
    void* obj;
    BusNode* next;
  };

  base::ObjectPool<BusNode> bus_node_pool;
  BusNode* first_node;

  static Bus create();

  void add_range(U16 segment, U16 offset, U32 size, FetchFunc fetch_func, StoreFunc store_func,
                 void* obj);

  U8 fetch(U16 segment, U16 offset) const;
  void store(U16 segment, U16 offset, U8 value) const;
};

}  // namespace emulator
