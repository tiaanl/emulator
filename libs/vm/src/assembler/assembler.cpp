#include "vm/assembler/assembler.h"

#include "vm/emulator/cpu.h"
#include "vm/emulator/op_codes.h"

namespace vm {

Assembler::Assembler() = default;

void Assembler::copy_to_bus(Bus* bus, Address addr) {
  bus->copy_range(addr, data_.size(), data_.data());
}

U16 Assembler::label() const {
  return U16(data_.size());
}

U8 Assembler::emit_mov_reg_from_reg(Register to, Register from) {
  auto count = emit_op_code(OpCode::MOV_REG_FROM_REG);
  count += emit_register(to);
  count += emit_register(from);

  return count;
}

U8 Assembler::emit_mov_reg_from_lit(Register to, U16 value) {
  auto count = emit_op_code(OpCode::MOV_REG_FROM_LIT);
  count += emit_register(to);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_mov_addr_from_lit(U16 addr, U8 value) {
  auto count = emit_op_code(OpCode::MOV_ADDR_FROM_LIT);
  count += emit_u16(addr);
  count += emit_u8(value);

  return count;
}

U8 Assembler::emit_mov_reg_addr_from_lit(Register reg, U8 value) {
  auto count = emit_op_code(OpCode::MOV_REG_ADDR_FROM_LIT);
  count += emit_u8(U8(reg));
  count += emit_u8(value);

  return count;
}

U8 Assembler::emit_jump_addr(U16 addr) {
  auto count = emit_op_code(OpCode::JUMP_ADDR);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_jump_if_equal(U16 addr) {
  auto count = emit_op_code(OpCode::JUMP_IF_EQUAL);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_jump_if_not_equal(U16 addr) {
  auto count = emit_op_code(OpCode::JUMP_IF_NOT_EQUAL);
  count += emit_u16(addr);

  return count;
}

U8 Assembler::emit_add(Register reg, U16 value) {
  auto count = emit_op_code(OpCode::ADD);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_subtract(Register reg, U16 value) {
  auto count = emit_op_code(OpCode::SUBTRACT);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_multiply(Register reg, U16 value) {
  auto count = emit_op_code(OpCode::MULTIPLY);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_compare_reg_to_lit(Register reg, U16 value) {
  auto count = emit_op_code(OpCode::COMPARE_REG_TO_LIT);
  count += emit_register(reg);
  count += emit_u16(value);

  return count;
}

U8 Assembler::emit_halt() {
  auto count = emit_op_code(OpCode::HALT);

  return count;
}

U8 Assembler::emit_op_code(OpCode op_code) {
  return emit_u8(U8(op_code));
}

U8 Assembler::emit_register(Register reg) {
  return emit_u8(U8(reg));
}

U8 Assembler::emit_u8(U8 value) {
  data_.push_back(value);
  return 1;
}

U8 Assembler::emit_u16(U16 value) {
  data_.push_back(U8(value & 0xFFu));
  data_.push_back(U8(value >> 0x08u));
  return 2;
}

}  // namespace vm
