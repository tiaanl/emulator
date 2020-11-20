#include <assembler/assembler.h>

using namespace emulator;

int main() {
  auto memory = Memory::create(1024);

  U8* ptr = memory.data;
  ptr += assembler::emit_mov_reg_from_lit(ptr, Register::AX, 52);
  ptr += assembler::emit_mov_reg_from_reg(ptr, Register::SP, Register::AX);
  assembler::emit_halt(ptr);

  auto cpu = CPU::create(&memory);

  cpu.debug();
  while (cpu.step() == StepResult::Continue) {
    cpu.debug();
  }

  memory.destroy();

  return 0;
}
