#pragma once

#include "vm/emulator/address.h"
#include "vm/object_pool.h"

namespace vm {

class Bus {
public:
  using FetchFunc = U8 (*)(void*, U32 Address);
  using StoreFunc = void (*)(void*, U32 Address, U8);

  Bus();

  void add_range(Address addr, U32 size, FetchFunc fetch_func, StoreFunc store_func, void* obj);
  void copy_range(Address start, U32 size, const U8* source) const;

  U8 fetch(Address addr) const;
  void store(Address addr, U8 value) const;

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
