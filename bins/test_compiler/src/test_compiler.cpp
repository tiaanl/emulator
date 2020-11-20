#include <assembler/assembler.h>
#include <emulator/bus.h>
#include <emulator/memory.h>

using namespace emulator;

int main() {
  auto memory = Memory::create(1024);

  U8* ptr = memory.data;
  ptr += assembler::emit_mov_reg_from_lit(ptr, Register::AX, 52);
  ptr += assembler::emit_mov_reg_from_reg(ptr, Register::SP, Register::AX);
  assembler::emit_halt(ptr);

  auto bus = Bus::create();
  bus.add_range(0, 1024, &memory_fetch_func, &memory_store_func, &memory);

  auto cpu = CPU::create(&bus);

  cpu.debug();
  while (cpu.step() == StepResult::Continue) {
    cpu.debug();
  }

  memory.destroy();

  return 0;
}
