#include "emulator/cpu.h"

#include <cassert>
#include <cstdio>

#include "emulator/op_codes.h"

#define PRINT_ASSEMBLY 0

namespace emulator {

namespace {

const char* register_to_string(Register reg) {
  switch (reg) {
    case Register::CS:
      return "CS";

    case Register::IP:
      return "IP";

    case Register::DS:
      return "DS";

    case Register::DI:
      return "DI";

    case Register::CF:
      return "CF";

    case Register::AX:
      return "AX";

    case Register::BX:
      return "BX";

    case Register::CX:
      return "CX";

    case Register::DX:
      return "DX";

    default:
      assert(0);
  }
}

enum CompareFlags : U16 {
  Equal = 0x0001,
  NotEqual = 0x0002,
  LessThan = 0x0004,
  LessThanOrEqual = 0x0008,
  GreaterThan = 0x0010,
  GreaterThanOrEqual = 0x0040,
};

}  // namespace

CPU CPU::create(Bus* bus) {
  CPU result = {};
  result.bus = bus;
  return result;
}

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
      set_register(to, get_register(from));
#if PRINT_ASSEMBLY > 0
      printf("%s, %s\n", register_to_string(to), register_to_string(from));
#endif
      break;
    }

    case OpCode::MOV_REG_FROM_LIT: {
      auto to = Register(fetch());
      auto value = fetch16();
      set_register(to, value);
#if PRINT_ASSEMBLY > 0
      printf("%s, 0x%04x\n", register_to_string(to), value);
#endif
      break;
    }

    case OpCode::MOV_ADDR_FROM_LIT: {
      auto addr = fetch16();
      auto value = fetch();
      auto ds = get_register(Register::DS);
      bus->store(ds, addr, value);
#if PRINT_ASSEMBLY > 0
      printf("0x%04x, %d\n", addr, value);
#endif
      break;
    }

    case OpCode::MOV_REG_ADDR_FROM_LIT: {
      auto reg = fetch();
      auto value = fetch();
      auto ds = get_register(Register::DS);
      bus->store(ds, get_register(emulator::Register(reg)), value);
#if PRINT_ASSEMBLY > 0
      printf("[%s], %d\n", emulator::register_to_string(emulator::Register(reg)), value);
#endif
      break;
    }

    case OpCode::JUMP_ADDR: {
      auto addr = fetch16();
      set_register(Register::IP, addr);
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case JUMP_IF_EQUAL: {
      auto addr = fetch16();
      auto cf = get_register(Register::CF);
      if (cf & CompareFlags::Equal) {
        set_register(Register::IP, addr);
      }
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case JUMP_IF_NOT_EQUAL: {
      auto addr = fetch16();
      auto cf = get_register(Register::CF);
      if (cf & CompareFlags::NotEqual) {
        set_register(Register::IP, addr);
      }
#if PRINT_ASSEMBLY > 0
      printf("0x%04x\n", addr);
#endif
      break;
    }

    case OpCode::COMPARE_REG_TO_LIT: {
      auto reg = Register(fetch());
      auto value = fetch16();
      auto register_value = get_register(reg);
      U16 cf = 0;
      if (register_value == value) cf |= CompareFlags::Equal;
      if (register_value != value) cf |= CompareFlags::NotEqual;
      if (register_value < value) cf |= CompareFlags::LessThan;
      if (register_value <= value) cf |= CompareFlags::LessThanOrEqual;
      if (register_value > value) cf |= CompareFlags::GreaterThan;
      if (register_value >= value) cf |= CompareFlags::GreaterThanOrEqual;
      set_register(Register::CF, cf);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::SUBTRACT: {
      auto reg = Register(fetch());
      auto value = fetch16();
      set_register(reg, get_register(reg) - value);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::MULTIPLY: {
      auto reg = Register(fetch());
      auto value = fetch16();
      set_register(reg, get_register(reg) * value);
#if PRINT_ASSEMBLY > 0
      printf("%s, %d\n", emulator::register_to_string(reg), value);
#endif
      break;
    }

    case OpCode::ADD: {
      auto reg = Register(fetch());
      auto value = fetch16();
      set_register(reg, get_register(reg) + value);
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
    printf("%s: 0x%04x  ", register_to_string(Register(i)), registers[i]);
  }
  puts("");
}

}  // namespace emulator
