#ifndef CPU_H_
#define CPU_H_

#include "platform.h"

#define REG_IP 0x01
#define REG_SP 0x02
#define REG_FP 0x03
#define REG_AX 0x04

typedef struct {
  U16 ip;  // Instruction pointer.
  U16 sp;  // Stack pointer.
  U16 fp;  // Frame pointer.
  U16 ax;  // Accumulator.
} CPU;

void CPU_init(CPU* cpu);

U16 CPU_get_register(CPU* cpu, U8 reg);
void CPU_set_register(CPU* cpu, U8 reg, U16 value);

#endif  // CPU_H_
