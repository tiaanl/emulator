#pragma once

namespace emulator {

enum class OpCode : U8 {
  // MOV AX, SP
  MOV_REG_FROM_REG = 0x10,

  // MOV AX, 10h
  MOV_REG_FROM_LIT = 0x11,

  // HALT
  HALT = 0xFF,
};

const char* op_code_to_string(OpCode op_code);

}  // namespace emulator
