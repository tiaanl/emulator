#include "vm/registers.h"

#include <cassert>

namespace vm {

const char* register_to_string(Register reg) {
  switch (reg) {
    case Register::R1:
      return "R1";

    case Register::R2:
      return "R2";

    case Register::R3:
      return "R3";

    case Register::R4:
      return "R4";

    case Register::IP:
      return "IP";

    case Register::SP:
      return "SP";

    case Register::BP:
      return "BP";

    case Register::FL:
      return "FL";

    default:
      assert(0);
  }

  return "";
}

}  // namespace vm
