#include "vm/emulator/registers.h"

#include <cassert>

namespace vm {

const char* register_to_string(Register reg) {
  switch (reg) {
    case Register::AX:
      return "AX";

    case Register::BX:
      return "BX";

    case Register::CX:
      return "CX";

    case Register::DX:
      return "DX";

    case Register::CS:
      return "CS";

    case Register::DS:
      return "DS";

    case Register::ES:
      return "ES";

    case Register::SS:
      return "SS";

    case Register::SI:
      return "SI";

    case Register::DI:
      return "DI";

    case Register::BP:
      return "BP";

    case Register::SP:
      return "SP";

    case Register::IP:
      return "IP";

    case Register::CF:
      return "CF";

    default:
      assert(0);
  }

  return "";
}

}  // namespace vm
