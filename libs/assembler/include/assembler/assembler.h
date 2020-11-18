#pragma once

#include <emulator/cpu.h>

namespace compiler {

U8 emit_mov_reg_from_reg(U8* data, emulator::Register to, emulator::Register from);

U8 emit_mov_reg_from_lit(U8* data, emulator::Register to, U16 value);

U8 emit_halt(U8* data);

}  // namespace compiler
