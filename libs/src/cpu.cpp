#include "cpu.h"

#include <assert.h>

void CPU_init(CPU* cpu) {
  cpu->ip = 0;
  cpu->sp = 0;
  cpu->fp = 0;
  cpu->ax = 0;
}

U16 CPU_get_register(CPU* cpu, U8 reg) {
  switch (reg) {
    case REG_IP:
      return cpu->ip;

    case REG_SP:
      return cpu->sp;

    case REG_FP:
      return cpu->fp;

    case REG_AX:
      return cpu->ax;

    default:
      assert(0);
      return 0;
  }
}

void CPU_set_register(CPU* cpu, U8 reg, U16 value) {
  switch (reg) {
    case REG_IP:
      cpu->ip = value;
      break;

    case REG_SP:
      cpu->sp = value;
      break;

    case REG_FP:
      cpu->fp = value;
      break;

    case REG_AX:
      cpu->ax = value;
      break;

    default:
      assert(0);
      break;
  }
}
