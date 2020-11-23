#pragma once

#include "vm/object_pool.h"

namespace vm {

class Bus {
public:
  using FetchFunc = U8 (*)(void*, U16);
  using StoreFunc = void (*)(void*, U16, U8);

  Bus();

  void add_range(U16 segment, U16 offset, U32 size, FetchFunc fetch_func, StoreFunc store_func,
                 void* obj);

  U8 fetch(U16 segment, U16 offset) const;
  void store(U16 segment, U16 offset, U8 value) const;

private:
  struct BusNode {
    U32 start_address;
    U32 size;
    FetchFunc fetch_func;
    StoreFunc store_func;
    void* obj;
    BusNode* next;
  };

  base::ObjectPool<BusNode> bus_node_pool_;
  BusNode* first_node_;
};

}  // namespace vm
