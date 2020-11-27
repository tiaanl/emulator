#pragma once

#include "vm/emulator/bus.h"
#include "vm/emulator/cpu.h"
#include "vm/emulator/memory.h"

namespace vm {

class Emulator {
public:
  Emulator() : cpu_(&bus_) {}

  Bus& bus() {
    return bus_;
  }

  CPU& cpu() {
    return cpu_;
  }

  bool initialize();
  void upload_code(const U8* code, U16 code_size);
  void run();

private:
  Memory memory_;
  Bus bus_;
  CPU cpu_;
};

}  // namespace vm
