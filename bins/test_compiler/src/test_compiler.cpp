#include <compiler/compiler.h>
#include <emulator/cpu.h>
#include <emulator/vm.h>

using namespace emulator;

int main() {
  U8 data[16 * 16] = {};

  U8* ptr = data;
  ptr += compiler::emit_mov_reg_from_reg(ptr, Register::AX, Register::SP);
  ptr += compiler::emit_mov_reg_from_lit(ptr, Register::AX, 52);
  ptr += compiler::emit_halt(ptr);

  VM vm = VM_create_with_memory(data, sizeof(data));
  VM_run(&vm);
  VM_destroy(&vm);

  return 0;
}
