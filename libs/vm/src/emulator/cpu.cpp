#include "vm/emulator/cpu.h"

#include <cassert>
#include <cstdio>

#define PRINT_ASSEMBLY 1

namespace vm {

namespace {

enum CompareFlags : U16 {
  Equal = 0x0001,
  NotEqual = 0x0002,
  LessThan = 0x0004,
  LessThanOrEqual = 0x0008,
  GreaterThan = 0x0010,
  GreaterThanOrEqual = 0x0040,
};

void print_operand(const Operand& operand) {
  switch (AddressingMode(operand.meta)) {
    case AddressingMode::Immediate:
      printf("0x%04x", operand.value);
      break;

    case AddressingMode::Register:
      printf("%s", register_to_string(Register(operand.value)));
      break;

    case AddressingMode::Direct:
      printf("[0x%04x]", operand.value);
      break;

    case AddressingMode::Indirect:
      printf("[%s]", register_to_string(Register(operand.value)));
      break;
  }
}

void print_instruction(const Instruction& instruction) {
  switch (instruction.type) {
    case InstructionType::Move: {
      printf("MOV ");
      print_operand(instruction.destination);
      printf(", ");
      print_operand(instruction.source);
      putchar('\n');
      break;
    }

    case InstructionType::Compare: {
      printf("CMP ");
      print_operand(instruction.destination);
      printf(", ");
      print_operand(instruction.source);
      printf("\n");
      break;
    }

    case InstructionType::Jump: {
      auto jc = JumpCondition(instruction.destination.meta);
      switch (jc) {
        case JumpCondition::Unconditional:
          printf("JMP ");
          break;

        case JumpCondition::IfEqual:
          printf("JEQ ");
          break;

        case JumpCondition::IfNotEqual:
          printf("JNE ");
          break;
      }
      printf("0x%04x", instruction.destination.value);
      printf("\n");
      break;
    }

    case InstructionType::Add: {
      printf("ADD ");
      print_operand(instruction.destination);
      printf(", ");
      print_operand(instruction.source);
      printf("\n");
      break;
    }

    case InstructionType::Subtract: {
      printf("SUB ");
      print_operand(instruction.destination);
      printf(", ");
      print_operand(instruction.source);
      printf("\n");
      break;
    }

    case InstructionType::Multiply: {
      printf("MUL ");
      print_operand(instruction.destination);
      printf(", ");
      print_operand(instruction.source);
      printf("\n");
      break;
    }

    case InstructionType::Halt:
      puts("HALT");
      break;
  }
}

}  // namespace

StepResult CPU::step() {
  Instruction instruction;
  decode(&instruction);

#if PRINT_ASSEMBLY >= 0
  print_instruction(instruction);
#endif

  switch (instruction.type) {
    case InstructionType::Move: {
      store_value(instruction.destination, fetch_value(instruction.source));
      break;
    }

    case InstructionType::Compare: {
      U16 left = fetch_value(instruction.destination);
      U16 right = fetch_value(instruction.source);

      U16 flags = 0x0000u;
      if (left == right) flags |= CompareFlags::Equal;
      if (left != right) flags |= CompareFlags::NotEqual;
      if (left < right) flags |= CompareFlags::LessThan;
      if (left <= right) flags |= CompareFlags::LessThanOrEqual;
      if (left > right) flags |= CompareFlags::GreaterThan;
      if (left >= right) flags |= CompareFlags::GreaterThanOrEqual;

      registers_.set(Register::FL, flags);

      break;
    }

    case InstructionType::Jump: {
      U16 value = fetch_value(instruction.destination);
      switch (JumpCondition(instruction.destination.meta)) {
        case JumpCondition::Unconditional: {
          registers_.set(Register::IP, value);
          break;
        }

        case JumpCondition::IfEqual: {
          if (registers_.get(Register::FL) & CompareFlags::Equal) {
            registers_.set(Register::IP, value);
          }
          break;
        }

        case JumpCondition::IfNotEqual: {
          if (registers_.get(Register::FL) & CompareFlags::NotEqual) {
            registers_.set(Register::IP, value);
          }
          break;
        }
      }
      break;
    }

    case InstructionType::Add: {
      U16 left = fetch_value(instruction.destination);
      U16 right = fetch_value(instruction.source);
      U16 result = left + right;
      store_value(instruction.destination, result);
      break;
    }

    case InstructionType::Subtract: {
      U16 left = fetch_value(instruction.destination);
      U16 right = fetch_value(instruction.source);
      U16 result = left - right;
      store_value(instruction.destination, result);
      break;
    }

    case InstructionType::Multiply: {
      U16 left = fetch_value(instruction.destination);
      U16 right = fetch_value(instruction.source);
      U16 result = left * right;
      store_value(instruction.destination, result);
      break;
    }

    case InstructionType::Halt: {
      return StepResult::Halt;
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

void CPU::decode(Instruction* instruction) {
  instruction->type = InstructionType(fetch());
  instruction->destination.meta = fetch();
  instruction->destination.value = fetch16();
  instruction->source.meta = fetch();
  instruction->source.value = fetch16();
}

U16 CPU::fetch_value(const Operand& operand) {
  switch (AddressingMode(operand.meta)) {
    case AddressingMode::Immediate:
      return operand.value;

    case AddressingMode::Register:
      return registers_.get(Register(operand.value));

    case AddressingMode::Direct:
      return memory_->fetch(operand.value);

    case AddressingMode::Indirect: {
      return memory_->fetch(registers_.get(Register(operand.value)));
    }
  }

  assert(false);
  return 0;
}

void CPU::store_value(const Operand& operand, U16 value) {
  switch (AddressingMode(operand.meta)) {
    case AddressingMode::Immediate:
      assert(false);
      break;

    case AddressingMode::Register:
      registers_.set(Register(operand.value), value);
      break;

    case AddressingMode::Direct:
      memory_->store(operand.value, U8(value));
      break;

    case AddressingMode::Indirect:
      memory_->store(registers_.get(Register(operand.value)), U8(value));
      break;
  }
}

}  // namespace vm
