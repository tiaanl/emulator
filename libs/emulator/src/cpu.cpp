#include "emulator/cpu.h"

#include <base/data.h>

#include <cassert>
#include <cstdio>

#include "emulator/op_codes.h"

namespace emulator {

namespace {

inline Register read_register(U8* data) {
  return static_cast<Register>(read_u8(data));
}

const char* register_to_string(Register reg) {
  switch (reg) {
    case Register::IP:
      return "IP";

    case Register::SP:
      return "SP";

    case Register::FP:
      return "FP";

    case Register::AX:
      return "AX";

    default:
      return "<unknown>";
  }
}

}  // namespace

CPU CPU::create(Memory* memory) {
  return {memory, 0, 0, 0, 0};
}

StepResult CPU::step() {
  auto op_code = OpCode(fetch());

  switch (op_code) {
    case OpCode::MOV_REG_FROM_REG: {
      auto to = Register(fetch());
      auto from = Register(fetch());
      set_register(to, get_register(from));
      printf("Executing: %s %s, %s\n", op_code_to_string(op_code), register_to_string(to),
             register_to_string(from));
      return StepResult::Continue;
    }

    case OpCode::MOV_REG_FROM_LIT: {
      auto to = Register(fetch());
      auto value = fetch16();
      set_register(to, value);
      printf("Executing: %s %s, 0x%04x\n", op_code_to_string(op_code), register_to_string(to),
             value);
      return StepResult::Continue;
    }

    case OpCode::HALT:
      printf("Executing: HLT\n");
      return StepResult::Halt;

    default: {
      assert(0);
      return StepResult::Halt;
    }
  }
}

void CPU::debug() {
  printf("IP: 0x%04x  SP: 0x%04x  FP: 0x%04x  AX: 0x%04x\n",  //
         registers[0], registers[1], registers[2], registers[3]);
}

}  // namespace emulator
