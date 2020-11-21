#pragma once

namespace emulator {

enum OpCode : U8 {
  // MOV AX, SP
  MOV_REG_FROM_REG = 0x01,

  // MOV AX, 10h
  MOV_REG_FROM_LIT,

  // MOV [addr], 32h
  MOV_ADDR_FROM_LIT,

  // MOV [AX], 32h
  MOV_REG_ADDR_FROM_LIT,

  // CMP AX, 0
  COMPARE_REG_TO_LIT,

  // JMP addr
  JUMP_ADDR,

  // JE addr
  JUMP_IF_EQUAL,

  // JNE addr
  JUMP_IF_NOT_EQUAL,

  // ADD AX, 1
  ADD,

  // SUB AX, 1
  SUBTRACT,

  // MUL AX, 3
  MULTIPLY,

  // HALT
  HALT = 0xFF,
};

const char* op_code_to_string(U8 op_code);

}  // namespace emulator
