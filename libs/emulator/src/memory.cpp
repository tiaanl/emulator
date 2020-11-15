#include "emulator/memory.h"

#include <malloc.h>

namespace emulator {

void create_memory(Memory* memory, U16 size) {
  memory->data = static_cast<U8*>(malloc(size));
  memory->size = size;
  memory->owning = 1;
}

void init_memory(Memory* memory, U8* data, U16 size) {
  memory->data = data;
  memory->size = size;
  memory->owning = 0;
}

void destroy_memory(Memory* memory) {
  if (memory->owning) {
    free(memory->data);
  }

  memory->data = nullptr;
  memory->size = 0;
  memory->owning = 0;
}

}  // namespace emulator
