#pragma once

namespace emulator {

struct Memory {
  U8* data;
  U16 size;
  U8 owning;

  static Memory create(U16 size);

  void destroy();
};

}  // namespace emulator
