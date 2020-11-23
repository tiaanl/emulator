#include <vm/assembler/assembler.h>
#include <vm/emulator/bus.h>
#include <vm/emulator/memory.h>

int main() {
  vm::Memory memory(1024);

  vm::Assembler a(memory.data(), memory.size());
  a.emit_mov_reg_from_lit(vm::Register::AX, 52);
  a.emit_mov_reg_from_reg(vm::Register::SP, vm::Register::AX);
  a.emit_halt();

  vm::Bus bus;
  bus.add_range(0x0000, 0x0000, memory.size(), &vm::Memory::load, &vm::Memory::store, &memory);

  vm::CPU cpu(&bus);

  cpu.debug();
  while (cpu.step() == vm::StepResult::Continue) {
    cpu.debug();
  }

  return 0;
}
