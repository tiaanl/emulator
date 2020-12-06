#pragma once

#include <memory>
#include <vector>

#include "vm/emulator/instruction.h"

namespace vm {
class Assembler;
}  // namespace vm

class Node {
public:
  virtual ~Node() = default;

  virtual void emit(vm::Assembler* assembler) = 0;
};

class NumberNode : public Node {
public:
  ~NumberNode() override = default;

protected:
  U64 number_;
};

enum class BinaryOperationType : U8 {
  Plus,
  Minus,
  Multiply,
  Divide,
};

class BinaryNode : public Node {
public:
  BinaryNode(BinaryOperationType type, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : type_{type}, left_{std::move(left)}, right_{std::move(right)} {}

  ~BinaryNode() override = default;

protected:
  BinaryOperationType type_;
  std::unique_ptr<Node> left_;
  std::unique_ptr<Node> right_;
};

class OperandNode : public Node {
public:
  explicit OperandNode(vm::AddressingMode addressing_mode) : addressing_mode_{addressing_mode} {}

  ~OperandNode() override = default;

protected:
  vm::AddressingMode addressing_mode_;
};

class ImmediateOperandNode : public OperandNode {
public:
  explicit ImmediateOperandNode(U16 value)
    : OperandNode{vm::AddressingMode::Register}, value_{value} {}

  ~ImmediateOperandNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  U16 value_;
};

class RegisterOperandNode : public OperandNode {
public:
  explicit RegisterOperandNode(vm::Register reg)
    : OperandNode{vm::AddressingMode::Register}, register_{reg} {}

  ~RegisterOperandNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  vm::Register register_;
};

class DirectOperandNode : public OperandNode {
public:
  explicit DirectOperandNode(U16 addr) : OperandNode{vm::AddressingMode::Direct}, addr_{addr} {}

  ~DirectOperandNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  U16 addr_;
};

class IndirectOperandNode : public OperandNode {
public:
  explicit IndirectOperandNode(vm::Register reg)
    : OperandNode{vm::AddressingMode::Indirect}, register_{reg} {}

  ~IndirectOperandNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  vm::Register register_;
};

class InstructionNode : public Node {
public:
  explicit InstructionNode(vm::InstructionType type) : type_{type} {}

  ~InstructionNode() override = default;

protected:
  vm::InstructionType type_;
};

class SingleOperandInstructionNode : public InstructionNode {
public:
  SingleOperandInstructionNode(vm::InstructionType instruction_type,
                               std::unique_ptr<OperandNode> destination)
    : InstructionNode{instruction_type}, destination_{std::move(destination)} {}
  ~SingleOperandInstructionNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  std::unique_ptr<OperandNode> destination_;
};

class DoubleOperandInstructionNode : public InstructionNode {
public:
  DoubleOperandInstructionNode(vm::InstructionType instruction_type,
                               std::unique_ptr<OperandNode> destination,
                               std::unique_ptr<OperandNode> source)
    : InstructionNode{instruction_type},
      destination_{std::move(destination)},
      source_{std::move(source)} {}
  ~DoubleOperandInstructionNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  std::unique_ptr<OperandNode> destination_;
  std::unique_ptr<OperandNode> source_;
};

class CompoundNode : public Node {
public:
  explicit CompoundNode(std::vector<std::unique_ptr<InstructionNode>> instructions)
    : instructions_(std::move(instructions)) {}
  ~CompoundNode() override = default;

  void emit(vm::Assembler*) override {}

protected:
  std::vector<std::unique_ptr<InstructionNode>> instructions_;
};
