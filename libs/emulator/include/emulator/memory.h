#pragma once

namespace emulator {

struct Memory {
  U8* data;
  U16 size;
  U8 owning;

  static Memory create(U16 size);

  void destroy();
};

inline U8 memory_fetch_func(void* obj, U16 addr) {
  auto memory = (Memory*)obj;
  return memory->data[addr];
}

inline void memory_store_func(void* obj, U16 addr, U8 value) {
  auto memory = (Memory*)obj;
  memory->data[addr] = value;
}

}  // namespace emulator
