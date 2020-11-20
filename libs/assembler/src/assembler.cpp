#include <base/data.h>
#include <emulator/cpu.h>
#include <emulator/op_codes.h>

namespace assembler {

namespace {

void write_op_code(U8* data, emulator::OpCode op_code) {
  write_u8(data, static_cast<U8>(op_code));
}

void write_register(U8* data, emulator::Register reg) {
  write_u8(data, static_cast<U8>(reg));
}

}  // namespace

U8 emit_mov_reg_from_reg(U8* data, emulator::Register to, emulator::Register from) {
  write_op_code(data, emulator::OpCode::MOV_REG_FROM_REG);
  write_register(data + 1, to);
  write_register(data + 2, from);

  return 3;
}

U8 emit_mov_reg_from_lit(U8* data, emulator::Register to, U16 value) {
  write_op_code(data, emulator::OpCode::MOV_REG_FROM_LIT);
  write_register(data + 1, to);
  write_u16(data + 2, value);

  return 4;
}

U8 emit_halt(U8* data) {
  write_op_code(data, emulator::OpCode::HALT);
  return 1;
}

}  // namespace assembler
