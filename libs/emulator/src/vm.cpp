#include "emulator/vm.h"

#include <cstdio>

namespace emulator {

VM VM_create_with_memory(U8* data, U16 size) {
  VM result;

  init_memory(&result.memory, data, size);
  CPU_init(&result.cpu);

  return result;
}

void VM_run(VM* vm) {
  while (CPU_step(&vm->cpu, &vm->memory) != StepResult::Halt) {
  }
}

void VM_destroy(VM* vm) {
  destroy_memory(&vm->memory);
}

}  // namespace emulator
