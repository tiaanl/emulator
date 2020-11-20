#include "emulator/op_codes.h"

namespace emulator {

const char* op_code_to_string(OpCode op_code) {
  switch (op_code) {
    case OpCode::MOV_REG_FROM_REG:
    case OpCode::MOV_REG_FROM_LIT:
      return "MOV";

    case OpCode::HALT:
      return "HALT";

    default:
      return "???";
  }
}

}  // namespace emulator
