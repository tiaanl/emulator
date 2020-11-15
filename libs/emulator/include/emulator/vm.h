#pragma once

#include "emulator/cpu.h"
#include "emulator/memory.h"

namespace emulator {

struct VM {
  CPU cpu;
  Memory memory;
};

VM VM_create_with_memory(U8* data, U16 size);
void VM_run(VM* vm);
void VM_destroy(VM* vm);

}  // namespace emulator
