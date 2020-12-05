#pragma once

#include "vm/emulator/registers.h"

namespace vm {

enum class InstructionType : U8 {
  Move,

  // Comparison
  Compare,

  // Branching
  Jump,

  // Arithmetic
  Add,
  Subtract,
  Multiply,

  // Internal
  Halt,
};

enum class AddressingMode : U8 {
  Immediate,
  Register,
  Direct,
  Indirect,
};

enum class JumpCondition : U8 {
  Unconditional,
  IfEqual,
  IfNotEqual,
};

struct Operand {
  U8 meta;
  U16 value;
};

inline Operand operand_immediate(U16 value) {
  return {U8(AddressingMode::Immediate), value};
}

inline Operand operand_register(Register reg) {
  return {U8(AddressingMode::Register), U16(reg)};
}

inline Operand operand_direct(U16 addr) {
  return {U8(AddressingMode::Direct), addr};
}

inline Operand operand_indirect(Register reg) {
  return {U8(AddressingMode::Indirect), U16(reg)};
}

struct Instruction {
  InstructionType type;
  Operand destination;
  Operand source;
};

}  // namespace vm
