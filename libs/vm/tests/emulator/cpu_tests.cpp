#include <assembler/assembler.h>
#include <emulator/cpu.h>

#include <cassert>

void test_registers() {
  auto memory = emulator::Memory::create(1024);
  auto cpu = emulator::CPU::create(&memory);

  cpu.set_register(emulator::Register::AX, 10);
  assert(cpu.get_register(emulator::Register::AX) == 10);
}

void test_mov_reg_from_reg() {
  auto memory = emulator::Memory::create(1024);
  auto cpu = emulator::CPU::create(&memory);

  cpu.set_register(emulator::Register::IP, 0);
  auto advance =
      compiler::emit_mov_reg_from_reg(memory.data, emulator::Register::AX, emulator::Register::IP);

  cpu.step();

  assert(cpu.get_register(emulator::Register::AX) == advance);
}

void test_mov_reg_from_lit() {
  auto memory = emulator::Memory::create(1024);
  auto cpu = emulator::CPU::create(&memory);

  cpu.set_register(emulator::Register::IP, 0);
  compiler::emit_mov_reg_from_lit(memory.data, emulator::Register::AX, 9);

  cpu.step();

  assert(cpu.get_register(emulator::Register::AX) == 9);
}

int main() {
  test_registers();
  test_mov_reg_from_reg();
  test_mov_reg_from_lit();
}
