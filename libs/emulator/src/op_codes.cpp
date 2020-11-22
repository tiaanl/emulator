#include "emulator/op_codes.h"

#include <cassert>
#include <cstdio>

namespace emulator {

const char* op_code_to_string(U8 op_code) {
  switch (op_code) {
    case OpCode::MOV_REG_FROM_REG:
    case OpCode::MOV_REG_FROM_LIT:
    case OpCode::MOV_ADDR_FROM_LIT:
    case OpCode::MOV_REG_ADDR_FROM_LIT:
      return "MOV";

    case OpCode::COMPARE_REG_TO_LIT:
      return "CMP";

    case OpCode::JUMP_ADDR:
      return "JMP";

    case OpCode::JUMP_IF_EQUAL:
      return "JE";

    case OpCode::JUMP_IF_NOT_EQUAL:
      return "JNE";

    case OpCode::ADD:
      return "ADD";

    case OpCode::SUBTRACT:
      return "SUB";

    case OpCode::MULTIPLY:
      return "MUL";

    case OpCode::HALT:
      return "HALT";

    default:
      printf("Invalid op_code found: %d\n", op_code);
      assert(0);
  }
}

}  // namespace emulator
