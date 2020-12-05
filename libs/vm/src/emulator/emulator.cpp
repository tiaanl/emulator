#include "vm/emulator/emulator.h"

namespace vm {

void Emulator::upload_code(const U8* code, U16 code_size) {
  for (U16 i = 0; i < code_size; ++i) {
    memory_.store(i, code[i]);
  }
}

void Emulator::run() {
  while (cpu_.step() != vm::StepResult::Halt) {
  }
}

}  // namespace vm
