#include "emulator/memory.h"

#include <malloc.h>

namespace emulator {

Memory Memory::create(U16 size) {
  Memory result = {};
  result.data = static_cast<U8*>(malloc(size));
  result.size = size;
  result.owning = 1;
  return result;
}

void Memory::destroy() {
  if (owning) {
    free(data);
  }

  data = nullptr;
  size = 0;
  owning = 0;
}

}  // namespace emulator
