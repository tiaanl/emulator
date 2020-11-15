#include "op_codes.h"

#include <stdint.h>

const char* op_code_to_string(uint8_t op_code) {
  switch (op_code) {
    case MOV_REG_FROM_REG:
    case MOV_REG_FROM_LIT:
      return "MOV";

    default:
      return "???";
  }
}
