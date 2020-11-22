#include "emulator/cpu.h"

#include <cassert>
#include <cstdio>

#include "emulator/op_codes.h"

#define PRINT_ASSEMBLY 0

namespace emulator {

namespace {

enum CompareFlags : U16 {
  Equal = 0x0001,
  NotEqual = 0x0002,
  LessThan = 0x0004,
  LessThanOrEqual = 0x0008,
  GreaterThan = 0x0010,
  GreaterThanOrEqual = 0x0040,
};

}  // namespace

StepResult CPU::step() {
  U8 op_code = fetch();

#if PRINT_ASSEMBLY > 0
  debug();
  printf("Executing: %s ", op_code_to_string(op_code));
#endif

  switch (op_code) {
    case OpCode::MOV_REG_FROM_REG: {
      auto to = Register(fetch());
      auto from = Register(fetch());
      registers_.set(to, registers_.get(from));
#if PRINT_ASSEMBLY > 0
      printf("%s, %s\n", register_to_string(to), register_to_string(from));
#endif
      break;
    }

    case OpCode::MOV_REG_FROM_LIT: {
      auto to = Register(fetch());
      auto value = fetch16();
      registers_.set(to, value);
#if PRINT_ASSEMBLY > 0
      printf("%s, 0x%04x\n", register_to_string(to), value);
#endif
      break;
    }

    case OpCode::MOV_ADDR_FROM_LIT: {
      auto addr = fetch16();
      auto value = fetch();
      auto ds = registers_.ds();
      bus_->store(ds, addr, value);
#if PRINT_ASSEMBLY > 0
      printf("0x%04x, %d\n", addr, value);
#endif
      break;
    }

    case OpCode::MOV_REG_ADDR_FROM_LIT: {
      auto reg = fetch();
      auto value = fetch();
      auto ds = registers_.ds();
      bus_->store(ds, registers_.get(emulator::Register(reg)), value);
#if PRINT_ASSEMBLY > 0
      printf("[%s], %d\n", emulator::register_to_string(emulator::Register(reg)), value);
#endif
      break;
    }

    case OpCode::JUMP_ADDR: {
      auto addr = fetch16();
      registers_.ip(addr);
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case JUMP_IF_EQUAL: {
      auto addr = fetch16();
      auto cf = registers_.cf();
      if (cf & CompareFlags::Equal) {
        registers_.ip(addr);
      }
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case JUMP_IF_NOT_EQUAL: {
      auto addr = fetch16();
      auto cf = registers_.cf();
      if (cf & CompareFlags::NotEqual) {
        registers_.ip(addr);
      }
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case OpCode::COMPARE_REG_TO_LIT: {
      auto reg = Register(fetch());
      auto value = fetch16();
      auto register_value = registers_.get(reg);
      U16 cf = 0;
      if (register_value == value) cf |= CompareFlags::Equal;
      if (register_value != value) cf |= CompareFlags::NotEqual;
      if (register_value < value) cf |= CompareFlags::LessThan;
      if (register_value <= value) cf |= CompareFlags::LessThanOrEqual;
      if (register_value > value) cf |= CompareFlags::GreaterThan;
      if (register_value >= value) cf |= CompareFlags::GreaterThanOrEqual;
      registers_.cf(cf);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::SUBTRACT: {
      auto reg = Register(fetch());
      auto value = fetch16();
      registers_.set(reg, registers_.get(reg) - value);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::MULTIPLY: {
      auto reg = Register(fetch());
      auto value = fetch16();
      registers_.set(reg, registers_.get(reg) * value);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::ADD: {
      auto reg = Register(fetch());
      auto value = fetch16();
      registers_.set(reg, registers_.get(reg) + value);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::HALT:
#if PRINT_ASSEMBLY > 0
      printf("\n");
#endif
      return StepResult::Halt;

    default: {
      printf("Invalid op_code: %d\n", op_code);
      assert(0);
    }
  }

  return StepResult::Continue;
}

void CPU::debug() {
  for (U8 i = 0; i < U8(Register::Count); ++i) {
    printf("%s: 0x%04x  ", register_to_string(Register(i)), registers_.get(Register(i)));
  }
  putchar('\n');
}

}  // namespace emulator
