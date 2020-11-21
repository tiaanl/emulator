#pragma once

#include "emulator/bus.h"

namespace emulator {

enum class Register : U8 {
  IP,
  CF,
  AX,
  BX,

  Count,
};

enum class StepResult : U8 {
  Continue,
  Halt,
};

struct CPU {
  Bus* bus;
  U16 registers[(U8)Register::Count];

  static CPU create(Bus* bus);

  StepResult step();

  void debug();

  inline U8 fetch() {
    auto ip = get_register(Register::IP);
    auto result = bus->fetch(ip);
    set_register(Register::IP, ip + 1);
    return result;
  }

  inline U16 fetch16() {
    auto ip = get_register(Register::IP);
    U16 result = U16(bus->fetch(ip)) | U16(bus->fetch(ip + 1) << 8ul);
    set_register(Register::IP, ip + 2);
    return result;
  }

  inline U16 get_register(Register reg) {
    return registers[U8(reg)];
  }

  inline void set_register(Register reg, U16 value) {
    registers[U8(reg)] = value;
  }
};

}  // namespace emulator
