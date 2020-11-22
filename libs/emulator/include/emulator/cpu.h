#pragma once

#include "emulator/bus.h"

namespace emulator {

// 8086/8088
//
// AX (AH/AL) = Primary Accumulator
// BX (BH/BL) = Base Accumulator
// CX (CH/CL) = Counter Accumulator
// DX (DH/DL) = Other Accumulator
//
// CS = Code Segment
// DS = Data Segment
// ES = Extra Segment
// SS = Stack Segment
//
// SI = Source Index
// DI = Destination Index
// BP = Base Pointer
// SP = Stack Pointer
// IP = Instruction Pointer
// Flags = Various CPU Flags

enum class Register : U8 {
  CS,  // Code Segment
  IP,  // Instruction Pointer

  DS,  // Data Segment
  DI,  // Data Index

  CF,  // Carrier Flags

  AX,  // Accumulator
  BX,
  CX,  // Counter
  DX,  // Data

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
    auto cs = get_register(Register::CS);
    auto ip = get_register(Register::IP);
    auto result = bus->fetch(cs, ip);
    set_register(Register::IP, ip + 1);
    return result;
  }

  inline U16 fetch16() {
    auto cs = get_register(Register::CS);
    auto ip = get_register(Register::IP);
    U16 result = U16(bus->fetch(cs, ip)) | U16(bus->fetch(cs, ip + 1) << 8ul);
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
