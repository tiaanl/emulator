#include "emulator/cpu.h"

#include <base/data.h>

#include <cassert>
#include <cstdio>

#include "emulator/op_codes.h"

namespace emulator {

namespace {

Register read_register(U8* data) {
  return static_cast<Register>(read_u8(data));
}

}  // namespace

void CPU_init(CPU* cpu) {
  cpu->ip = 0;
  cpu->sp = 0;
  cpu->fp = 0;
  cpu->ax = 0;
}

StepResult CPU_step(CPU* cpu, Memory* memory) {
  auto op_code = static_cast<OpCode>(memory->data[cpu->ip]);

  printf("Executing: %s\n", op_code_to_string(op_code));

  switch (op_code) {
    case OpCode::MOV_REG_FROM_REG: {
      auto to = read_register(memory->data + 1);
      auto from = read_register(memory->data + 2);
      cpu->ip += 3;
      CPU_set_register(cpu, to, CPU_get_register(cpu, from));
      return StepResult::Continue;
    }

    case OpCode::MOV_REG_FROM_LIT: {
      auto to = read_register(memory->data + 1);
      auto value = read_u16(memory->data + 2);
      cpu->ip += 4;
      CPU_set_register(cpu, to, value);
      return StepResult::Continue;
    }

    case OpCode::HALT:
      cpu->ip += 1;
      return StepResult::Halt;

    default: {
      assert(0);
      return StepResult::Halt;
    }
  }
}

U16 CPU_get_register(CPU* cpu, Register reg) {
  switch (reg) {
    case Register::IP:
      return cpu->ip;

    case Register::SP:
      return cpu->sp;

    case Register::FP:
      return cpu->fp;

    case Register::AX:
      return cpu->ax;

    default:
      assert(0);
      return 0;
  }
}

void CPU_set_register(CPU* cpu, Register reg, U16 value) {
  switch (reg) {
    case Register::IP:
      cpu->ip = value;
      break;

    case Register::SP:
      cpu->sp = value;
      break;

    case Register::FP:
      cpu->fp = value;
      break;

    case Register::AX:
      cpu->ax = value;
      break;

    default:
      assert(0);
      break;
  }
}

}  // namespace emulator
