#pragma once

#include "emulator/memory.h"

namespace emulator {

enum class Register : U8 {
  IP = 0x01,
  SP = 0x02,
  FP = 0x03,
  AX = 0x04,
};

typedef struct {
  U16 ip;  // Instruction pointer.
  U16 sp;  // Stack pointer.
  U16 fp;  // Frame pointer.
  U16 ax;  // Accumulator.
} CPU;

enum class StepResult : U8 {
  Continue,
  Halt,
};

void CPU_init(CPU* cpu);

StepResult CPU_step(CPU* cpu, Memory* memory);

U16 CPU_get_register(CPU* cpu, Register reg);
void CPU_set_register(CPU* cpu, Register reg, U16 value);

}  // namespace emulator
