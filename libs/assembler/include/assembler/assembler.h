#pragma once

#include <emulator/cpu.h>
#include <emulator/op_codes.h>

namespace assembler {

class Assembler {
public:
  Assembler(U8* data, U16 data_size);

  U16 label() const;

  U8 emit_mov_reg_from_reg(emulator::Register to, emulator::Register from);
  U8 emit_mov_reg_from_lit(emulator::Register to, U16 value);
  U8 emit_mov_addr_from_lit(U16 addr, U8 value);
  U8 emit_mov_reg_addr_from_lit(emulator::Register reg, U8 value);
  U8 emit_jump_addr(U16 addr);
  U8 emit_jump_if_equal(U16 addr);
  U8 emit_jump_if_not_equal(U16 addr);
  U8 emit_add(emulator::Register reg, U16 value);
  U8 emit_subtract(emulator::Register reg, U16 value);
  U8 emit_multiply(emulator::Register reg, U16 value);
  U8 emit_compare_reg_to_lit(emulator::Register reg, U16 value);
  U8 emit_halt();

private:
  U8 emit_op_code(emulator::OpCode op_code);
  U8 emit_register(emulator::Register reg);
  U8 emit_u8(U8 value);
  U8 emit_u16(U16 value);

  U8* data_;
  U16 data_size_;

  U8* current_;
};

}  // namespace assembler
