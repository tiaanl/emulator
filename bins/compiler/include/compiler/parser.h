#pragma once

#include "compiler/ast.h"
#include "compiler/token.h"

class Lexer;

class Parser {
public:
  explicit Parser(Lexer* lexer) : lexer_{lexer} {}

  std::unique_ptr<CompoundNode> parse_compound();
  std::unique_ptr<InstructionNode> parse_instruction();
  std::unique_ptr<OperandNode> parse_operand();
  std::unique_ptr<OperandNode> parse_immediate_operand();
  std::unique_ptr<OperandNode> parse_register_operand();
  std::unique_ptr<OperandNode> parse_direct_operand();
  std::unique_ptr<OperandNode> parse_indirect_operand();

private:
  Lexer* lexer_;
};
