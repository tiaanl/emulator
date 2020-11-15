#pragma once

namespace emulator {

struct Memory {
  U8* data;
  U16 size;
  U8 owning;
};

void create_memory(Memory* memory, U16 size);
void init_memory(Memory* memory, U8* data, U16 size);
void destroy_memory(Memory* memory);

}  // namespace emulator
