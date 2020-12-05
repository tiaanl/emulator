#pragma once

namespace vm {

enum class InstructionType : U8 {
  Move,
};

enum class AddressingMode : U8 {
  Immediate,
  Direct,
};

struct Operand {
  AddressingMode addressing_mode;
  U16 value;
};

struct Instruction {
  InstructionType type;
  Operand destination;
  Operant source;
};

}  // namespace vm
