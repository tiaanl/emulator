#pragma once

#include <vector>

#include "vm/cpu.h"
#include "vm/instruction.h"
#include "vm/op_codes.h"

namespace vm {

class Assembler {
public:
  Assembler();

  const U8* code() const {
    return data_.data();
  }

  U16 size() const {
    return U16(data_.size());
  }

  U16 label() const;

  U8 emit_mov_reg_from_reg(Register to, Register from);
  U8 emit_mov_reg_from_lit(Register to, U16 value);
  U8 emit_mov_addr_from_lit(U16 addr, U8 value);
  U8 emit_mov_reg_addr_from_lit(Register reg, U8 value);
  U8 emit_jump_unconditional(U16 addr);
  U8 emit_jump_if_equal(U16 addr);
  U8 emit_jump_if_not_equal(U16 addr);
  U8 emit_add(Register reg, U16 value);
  U8 emit_subtract(Register reg, U16 value);
  U8 emit_multiply(Register reg, U16 value);
  U8 emit_compare_reg_to_lit(Register reg, U16 value);
  U8 emit_halt();

  U8 emit_instruction(const Instruction& instruction);

private:
  U8 emit_operand(const Operand& operand);

  U8 emit_u8(U8 value);
  U8 emit_u16(U16 value);

  std::vector<U8> data_;
};

}  // namespace vm
