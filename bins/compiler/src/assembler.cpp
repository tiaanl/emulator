#include "compiler/assembler.h"

#include "vm/cpu.h"
#include "vm/op_codes.h"

namespace vm {

Assembler::Assembler() = default;

U16 Assembler::label() const {
  return U16(data_.size());
}

U8 Assembler::emit_mov_reg_from_reg(Register destination, Register source) {
  return emit_instruction(
      {InstructionType::Move, operand_register(destination), operand_register(source)});
}

U8 Assembler::emit_mov_reg_from_lit(Register destination, U16 value) {
  return emit_instruction({
      InstructionType::Move,
      operand_register(destination),
      operand_immediate(value),
  });
}

U8 Assembler::emit_mov_addr_from_lit(U16 addr, U8 value) {
  return emit_instruction({
      InstructionType::Move,
      operand_direct(addr),
      operand_immediate(value),
  });
}

U8 Assembler::emit_mov_reg_addr_from_lit(Register reg, U8 value) {
  return emit_instruction({
      InstructionType::Move,
      operand_indirect(reg),
      operand_immediate(value),
  });
}

U8 Assembler::emit_compare_reg_to_lit(Register left, U16 right) {
  return emit_instruction({
      InstructionType::Compare,
      operand_register(left),
      operand_immediate(right),
  });
}

U8 Assembler::emit_jump_unconditional(U16 addr) {
  return emit_instruction({
      InstructionType::Jump,
      {U8(JumpCondition::Unconditional), addr},
      {},
  });
}

U8 Assembler::emit_jump_if_equal(U16 addr) {
  return emit_instruction({
      InstructionType::Jump,
      {U8(JumpCondition::IfEqual), addr},
      {},
  });
}

U8 Assembler::emit_jump_if_not_equal(U16 addr) {
  return emit_instruction({
      InstructionType::Jump,
      {U8(JumpCondition::IfNotEqual), addr},
      {},
  });
}

U8 Assembler::emit_add(Register destination, U16 source) {
  return emit_instruction({
      InstructionType::Add,
      operand_register(destination),
      operand_immediate(source),
  });
}

U8 Assembler::emit_subtract(Register destination, U16 source) {
  return emit_instruction({
      InstructionType::Subtract,
      operand_register(destination),
      operand_immediate(source),
  });
}

U8 Assembler::emit_multiply(Register destination, U16 source) {
  return emit_instruction({
      InstructionType::Multiply,
      operand_register(destination),
      operand_immediate(source),
  });
}

U8 Assembler::emit_halt() {
  return emit_instruction({
      InstructionType::Halt,
      {},
      {},
  });
}

U8 Assembler::emit_instruction(const Instruction& instruction) {
  U8 count = 0;
  count += emit_u8(U8(instruction.type));
  count += emit_operand(instruction.destination);
  count += emit_operand(instruction.source);
  return count;
}

U8 Assembler::emit_operand(const Operand& operand) {
  U8 count = 0;
  count += emit_u8(operand.meta);
  count += emit_u16(operand.value);
  return count;
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
