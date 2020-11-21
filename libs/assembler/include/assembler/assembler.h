#pragma once

#include <emulator/cpu.h>

namespace assembler {

U8 emit_mov_reg_from_reg(U8* data, emulator::Register to, emulator::Register from);
U8 emit_mov_reg_from_lit(U8* data, emulator::Register to, U16 value);
U8 emit_mov_addr_from_lit(U8* data, U16 addr, U8 value);
U8 emit_mov_reg_addr_from_lit(U8* data, emulator::Register reg, U8 value);
U8 emit_jump_addr(U8* data, U16 addr);
U8 emit_jump_if_equal(U8* data, U16 addr);
U8 emit_jump_if_not_equal(U8* data, U16 addr);
U8 emit_add(U8* data, emulator::Register reg, U16 value);
U8 emit_subtract(U8* data, emulator::Register reg, U16 value);
U8 emit_multiply(U8* data, emulator::Register reg, U16 value);
U8 emit_compare_reg_to_lit(U8* data, emulator::Register reg, U16 value);
U8 emit_halt(U8* data);

}  // namespace assembler
