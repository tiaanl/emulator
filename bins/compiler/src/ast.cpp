#include "compiler/ast.h"

#include <cstdio>

#include "compiler/assembler.h"

void SingleOperandInstructionNode::emit(vm::Assembler* assembler) {
  vm::Instruction instruction = {};
  instruction.type = type_;

  switch (destination_->type()) {
    case NodeType::ImmediateOperand: {
      auto destination = static_cast<ImmediateOperandNode*>(destination_.get());
      instruction.destination = vm::operand_immediate(destination->value());
      break;
    }

    case NodeType::RegisterOperand: {
      auto destination = static_cast<RegisterOperandNode*>(destination_.get());
      instruction.destination = vm::operand_register(destination->reg());
      break;
    }

    case NodeType::DirectOperand: {
      auto destination = static_cast<DirectOperandNode*>(destination_.get());
      instruction.destination = vm::operand_direct(destination->addr());
      break;
    }

    case NodeType::IndirectOperand: {
      auto destination = static_cast<IndirectOperandNode*>(destination_.get());
      instruction.destination = vm::operand_indirect(destination->reg());
      break;
    }

    default:
      fprintf(stderr, "Destination must be an operand.");
      break;
  }

  assembler->emit_instruction(instruction);
}
