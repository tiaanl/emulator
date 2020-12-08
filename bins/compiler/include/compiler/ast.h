#pragma once

#include <memory>
#include <vector>

#include "vm/emulator/instruction.h"

namespace vm {
class Assembler;
}  // namespace vm

enum class NodeType : U8 {
  ImmediateOperand,
  RegisterOperand,
  DirectOperand,
  IndirectOperand,

  SingleOperandInstruction,
  DoubleOperandInstruction,
  Compound,
};

class Node {
public:
  virtual ~Node() = default;

  virtual NodeType type() const = 0;

  virtual void emit(vm::Assembler*) {}
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

  U16 value() const {
    return value_;
  }

  NodeType type() const override {
    return NodeType::ImmediateOperand;
  }

protected:
  U16 value_;
};

class RegisterOperandNode : public OperandNode {
public:
  explicit RegisterOperandNode(vm::Register reg)
    : OperandNode{vm::AddressingMode::Register}, reg_{reg} {}

  ~RegisterOperandNode() override = default;

  vm::Register reg() const {
    return reg_;
  }

  NodeType type() const override {
    return NodeType::RegisterOperand;
  }

protected:
  vm::Register reg_;
};

class DirectOperandNode : public OperandNode {
public:
  explicit DirectOperandNode(U16 addr) : OperandNode{vm::AddressingMode::Direct}, addr_{addr} {}

  ~DirectOperandNode() override = default;

  U16 addr() const {
    return addr_;
  }

  NodeType type() const override {
    return NodeType::DirectOperand;
  }

protected:
  U16 addr_;
};

class IndirectOperandNode : public OperandNode {
public:
  explicit IndirectOperandNode(vm::Register reg)
    : OperandNode{vm::AddressingMode::Indirect}, reg_{reg} {}

  ~IndirectOperandNode() override = default;

  vm::Register reg() const {
    return reg_;
  }

  NodeType type() const override {
    return NodeType::IndirectOperand;
  }

protected:
  vm::Register reg_;
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

  NodeType type() const override {
    return NodeType::SingleOperandInstruction;
  }

  void emit(vm::Assembler* assembler) override;

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

  NodeType type() const override {
    return NodeType::DoubleOperandInstruction;
  }

protected:
  std::unique_ptr<OperandNode> destination_;
  std::unique_ptr<OperandNode> source_;
};

class CompoundNode : public Node {
public:
  explicit CompoundNode(std::vector<std::unique_ptr<InstructionNode>> instructions)
    : instructions_(std::move(instructions)) {}

  ~CompoundNode() override = default;

  NodeType type() const override {
    return NodeType::Compound;
  }

  void emit(vm::Assembler* assembler) override {
    for (auto& instruction : instructions_) {
      instruction->emit(assembler);
    }
  }

protected:
  std::vector<std::unique_ptr<InstructionNode>> instructions_;
};
