#include "assembler/assembler.h"

#include <emulator/cpu.h>
#include <emulator/op_codes.h>

namespace assembler {

Assembler::Assembler(U8* data, U16 data_size)
  : data_(data), data_size_(data_size), current_(data) {}

U16 Assembler::label() const {
  return U16(current_ - data_);
}

U8 Assembler::emit_mov_reg_from_reg(emulator::Register to, emulator::Register from) {
  auto count = emit_op_code(emulator::OpCode::MOV_REG_FROM_REG);
  count += emit_register(to);
  count += emit_register(from);

  return count;
}

U8 Assembler::emit_mov_reg_from_lit(emulator::Register to, U16 value) {
  auto count = emit_op_code(emulator::OpCode::MOV_REG_FROM_LIT);
  count += emit_register(to);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_mov_addr_from_lit(U16 addr, U8 value) {
  auto count = emit_op_code(emulator::MOV_ADDR_FROM_LIT);
  count += emit_u16(addr);
  count += emit_u8(value);

  return count;
}

U8 Assembler::emit_mov_reg_addr_from_lit(emulator::Register reg, U8 value) {
  auto count = emit_op_code(emulator::MOV_REG_ADDR_FROM_LIT);
  count += emit_u8(U8(reg));
  count += emit_u8(value);

  return count;
}

U8 Assembler::emit_jump_addr(U16 addr) {
  auto count = emit_op_code(emulator::OpCode::JUMP_ADDR);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_jump_if_equal(U16 addr) {
  auto count = emit_op_code(emulator::OpCode::JUMP_IF_EQUAL);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_jump_if_not_equal(U16 addr) {
  auto count = emit_op_code(emulator::OpCode::JUMP_IF_NOT_EQUAL);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_add(emulator::Register reg, U16 value) {
  auto count = emit_op_code(emulator::OpCode::ADD);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_subtract(emulator::Register reg, U16 value) {
  auto count = emit_op_code(emulator::OpCode::SUBTRACT);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_multiply(emulator::Register reg, U16 value) {
  auto count = emit_op_code(emulator::OpCode::MULTIPLY);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_compare_reg_to_lit(emulator::Register reg, U16 value) {
  auto count = emit_op_code(emulator::OpCode::COMPARE_REG_TO_LIT);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_halt() {
  auto count = emit_op_code(emulator::OpCode::HALT);

  return count;
}

U8 Assembler::emit_op_code(emulator::OpCode op_code) {
  *current_++ = op_code;
  return 1;
}

U8 Assembler::emit_register(emulator::Register reg) {
  *current_++ = U8(reg);
  return 1;
}

U8 Assembler::emit_u8(U8 value) {
  *current_++ = value;
  return 2;
}

U8 Assembler::emit_u16(U16 value) {
  *current_++ = U8(value & 0xFFu);
  *current_++ = U8(value >> 0x08u);
  return 2;
}

}  // namespace assembler
