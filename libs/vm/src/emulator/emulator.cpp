#include "vm/emulator/emulator.h"

namespace vm {

bool Emulator::initialize() {
  auto addr = memory_.allocate_page();

  // First 0xFFFF bytes are for code.
  map_memory_page_to_bus(&bus_, &memory_, addr);

  return true;
}

void Emulator::upload_code(const U8* code, U16 code_size) {
  bus_.copy_range(Address(0), code_size, code);
}

void Emulator::run() {
  while (cpu_.step() != vm::StepResult::Halt) {
  }
}

}  // namespace vm
