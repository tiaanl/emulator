#include <assembler/assembler.h>

int main() {
  auto memory = emulator::Memory::create(1024);

  U8* ptr = memory.data;
  ptr += compiler::emit_mov_reg_from_reg(ptr, emulator::Register::AX, emulator::Register::SP);
  ptr += compiler::emit_mov_reg_from_lit(ptr, emulator::Register::AX, 52);
  compiler::emit_halt(ptr);

  auto cpu = emulator::CPU::create(&memory);

  cpu.debug();
  while (cpu.step() == emulator::StepResult::Continue) {
      cpu.debug();
  }

  memory.destroy();

  return 0;
}
