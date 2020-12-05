#pragma once

#include "memory.h"
#include "op_codes.h"
#include "vm/emulator/registers.h"

namespace vm {

enum class StepResult : U8 {
  Continue,
  Halt,
};

class CPU {
public:
  explicit CPU(Memory* memory) : memory_{memory} {}

  StepResult step();

  void debug();

  inline U8 fetch() {
    auto ip = registers_.ip();
    auto result = memory_->fetch(ip);
    registers_.ip(ip + 1);
    return result;
  }

  inline U16 fetch16() {
    auto ip = registers_.ip();
    U16 result = U16(memory_->fetch(ip)) | U16(memory_->fetch(U16(ip + 1)) << 8ul);
    registers_.ip(ip + 2);
    return result;
  }

private:
  inline OpCode fetch_op_code() {
    return OpCode{fetch()};
  }

  Memory* memory_;

  Registers registers_;
};

}  // namespace vm
