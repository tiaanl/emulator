#pragma once

#include "emulator/memory.h"

namespace emulator {

enum class Register : U8 {
  IP = 0x00,
  SP = 0x01,
  FP = 0x02,
  AX = 0x03,

  Count,
};

enum class StepResult : U8 {
  Continue,
  Halt,
};

struct CPU {
  Memory* memory;
  U16 registers[(U8)Register::Count];

  static CPU create(Memory* memory);

  StepResult step();

  void debug();

  U8 fetch() {
    auto ip = get_register(Register::IP);
    auto result = memory->data[ip];
    set_register(Register::IP, ip + 1);
    return result;
  }

  U16 fetch16() {
    auto ip = get_register(Register::IP);
    U16 result = memory->data[ip] | (memory->data[ip] << 8);
    set_register(Register::IP, ip + 2);
    return result;
  }

  U16 get_register(Register reg) {
    return registers[U8(reg)];
  }

  void set_register(Register reg, U16 value) {
    registers[U8(reg)] = value;
  }
};

}  // namespace emulator
