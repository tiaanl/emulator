#pragma once

#include "vm/cpu.h"
#include "vm/memory.h"

namespace vm {

class Emulator {
public:
  Emulator() : cpu_(&memory_) {}

  CPU& cpu() {
    return cpu_;
  }

  void upload_code(const U8* code, U16 code_size);
  void run();

private:
  Memory memory_;
  CPU cpu_;
};

}  // namespace vm
