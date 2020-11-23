#pragma once

#include "vm/emulator/bus.h"
#include "vm/emulator/registers.h"

namespace vm {

enum class StepResult : U8 {
  Continue,
  Halt,
};

class CPU {
public:
  explicit CPU(Bus* bus) : bus_(bus) {}

  StepResult step();

  void debug();

  inline U8 fetch() {
    auto ip = registers_.ip();
    auto result = bus_->fetch(registers_.cs(), ip);
    registers_.ip(ip + 1);
    return result;
  }

  inline U16 fetch16() {
    auto cs = registers_.cs();
    auto ip = registers_.ip();
    U16 result = U16(bus_->fetch(cs, ip)) | U16(bus_->fetch(cs, ip + 1) << 8ul);
    registers_.ip(ip + 2);
    return result;
  }

private:
  Bus* bus_;
  Registers registers_;
};

}  // namespace vm
