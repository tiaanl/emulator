#pragma once

#include "emulator/bus.h"
#include "emulator/registers.h"

namespace emulator {

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
    auto ip = registers_.IP();
    auto result = bus_->fetch(registers_.CS(), ip);
    registers_.IP(ip + 1);
    return result;
  }

  inline U16 fetch16() {
    auto cs = registers_.CS();
    auto ip = registers_.IP();
    U16 result = U16(bus_->fetch(cs, ip)) | U16(bus_->fetch(cs, ip + 1) << 8ul);
    registers_.IP(ip + 2);
    return result;
  }

private:
  Bus* bus_;
  Registers registers_;
};

}  // namespace emulator
