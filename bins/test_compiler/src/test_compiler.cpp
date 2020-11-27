#include <vm/assembler/assembler.h>
#include <vm/emulator/emulator.h>

int main() {
  vm::Assembler a;
  a.emit_mov_reg_from_lit(vm::Register::AX, 52);
  a.emit_mov_reg_from_reg(vm::Register::SP, vm::Register::AX);
  a.emit_halt();

  vm::Emulator emulator;
  if (!emulator.initialize()) {
    return 1;
  }

  emulator.upload_code(a.code(), a.size());

  while (emulator.cpu().step() == vm::StepResult::Continue) {
  }

  return 0;
}
