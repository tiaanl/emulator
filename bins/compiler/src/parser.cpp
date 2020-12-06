#include "compiler/parser.h"

#include <cstdio>
#include <optional>

#include "compiler/lexer.h"

namespace {

bool range_equal(Range<char> data, const char* text) {
  auto text_length = strlen(text);
  if (data.length() != text_length) {
    return false;
  }

  return strncmp(data.begin(), text, text_length) == 0;
}

std::optional<vm::Register> range_to_register(Range<char> source) {
  if (range_equal(source, "R1")) {
    return vm::Register::R1;
  }

  if (range_equal(source, "R2")) {
    return vm::Register::R2;
  }

  if (range_equal(source, "R3")) {
    return vm::Register::R3;
  }

  if (range_equal(source, "R4")) {
    return vm::Register::R4;
  }

  if (range_equal(source, "BP")) {
    return vm::Register::BP;
  }

  if (range_equal(source, "SP")) {
    return vm::Register::SP;
  }

  return {};
}

std::optional<U16> range_to_u16(Range<char> source, int radix) {
  char* end;
  auto value = std::strtoul(source.begin(), &end, radix);
  if (end == source.begin()) {
    return {};
  }

  // TODO: Check ranges.
  return U16(value);
}

}  // namespace

std::unique_ptr<CompoundNode> Parser::parse_compound() {
  std::vector<std::unique_ptr<InstructionNode>> instructions;
  for (;;) {
    auto token = lexer_->peek_token();
    if (token.type == TokenType::Unknown || token.type == TokenType::EndOfSource) {
      break;
    }

    auto node = parse_instruction();
    if (!node) {
      fprintf(stderr, "Could not parse code.\n");
      break;
    }

    instructions.emplace_back(std::move(node));
  }

  return std::make_unique<CompoundNode>(std::move(instructions));
}

std::unique_ptr<InstructionNode> Parser::parse_instruction() {
  auto marker = Marker{lexer_};

  auto token = lexer_->consume_token();

  if (token.type == TokenType::NewLine) {
    marker.commit();
    return parse_instruction();
  }

  if (token.type != TokenType::Identifier) {
    fprintf(stderr, "Mnemonic expected.\n");
    return {};
  }

  if (range_equal(token.data, "MOV")) {
    auto destination = parse_operand();
    if (!destination) {
      fprintf(stderr, "Destination operand expected for MOV instruction.\n");
      return {};
    }

    auto comma = lexer_->consume_token();
    if (comma.type != TokenType::Comma) {
      fprintf(stderr, "Comma expected!\n");
      return {};
    }

    auto source = parse_operand();
    if (!source) {
      fprintf(stderr, "Source operand expected for MOV instruction.\n");
      return {};
    }

    marker.commit();

    return std::make_unique<DoubleOperandInstructionNode>(
        vm::InstructionType::Move, std::move(destination), std::move(source));
  }

  if (range_equal(token.data, "JMP")) {
    auto addr = parse_operand();
    if (!addr) {
      fprintf(stderr, "JMP requires operand\n");
      return {};
    }

    marker.commit();

    return std::make_unique<SingleOperandInstructionNode>(vm::InstructionType::Jump,
                                                          std::move(addr));
  }

  fprintf(stderr, "Invalid identifier (%s)\n", token.data.begin());

  return {};
}

std::unique_ptr<OperandNode> Parser::parse_operand() {
  if (auto operand = parse_immediate_operand(); operand) {
    return operand;
  }

  if (auto operand = parse_register_operand(); operand) {
    return operand;
  }

  if (auto operand = parse_direct_operand(); operand) {
    return operand;
  }

  if (auto operand = parse_indirect_operand(); operand) {
    return operand;
  }

  return {};
}

std::unique_ptr<OperandNode> Parser::parse_immediate_operand() {
  auto marker = Marker{lexer_};

  auto token = lexer_->consume_token();

  std::optional<U16> value;

  if (token.type == TokenType::DecimalNumber) {
    value = range_to_u16(token.data, 10);
  } else if (token.type == TokenType::HexNumber) {
    value = range_to_u16(token.data, 16);
  }

  if (!value) {
    return {};
  }

  marker.commit();

  return std::make_unique<ImmediateOperandNode>(U16(*value));
}

std::unique_ptr<OperandNode> Parser::parse_register_operand() {
  auto marker = Marker{lexer_};

  auto token = lexer_->consume_token();

  if (token.type != TokenType::Identifier) {
    return {};
  }

  auto reg = range_to_register(token.data);
  if (!reg) {
    return {};
  }

  marker.commit();
  return std::make_unique<RegisterOperandNode>(*reg);
}

std::unique_ptr<OperandNode> Parser::parse_direct_operand() {
  auto marker = Marker{lexer_};

  auto token = lexer_->consume_token();
  if (token.type != TokenType::OpenSquareBracket) {
    return {};
  }

  auto middle = lexer_->consume_token();
  if (middle.type != TokenType::DecimalNumber && middle.type != TokenType::HexNumber) {
    return {};
  }

  token = lexer_->consume_token();
  if (token.type != TokenType::CloseSquareBracket) {
    return {};
  }

  std::optional<U16> value;
  if (middle.type == TokenType::HexNumber) {
    value = range_to_u16(middle.data, 16);
  } else if (middle.type == TokenType::DecimalNumber) {
    value = range_to_u16(middle.data, 10);
  }

  if (!value) {
    fprintf(stderr, "Invalid number value.");
    return {};
  }

  marker.commit();
  return std::make_unique<DirectOperandNode>(value.value());
}

std::unique_ptr<OperandNode> Parser::parse_indirect_operand() {
  auto marker = Marker{lexer_};

  auto token = lexer_->consume_token();
  if (token.type != TokenType::OpenSquareBracket) {
    return {};
  }

  auto middle = lexer_->consume_token();
  if (middle.type != TokenType::Identifier) {
    return {};
  }

  token = lexer_->consume_token();
  if (token.type != TokenType::CloseSquareBracket) {
    return {};
  }

  auto reg = range_to_register(middle.data);
  if (!reg) {
    return {};
  }

  marker.commit();
  return std::make_unique<IndirectOperandNode>(reg.value());
}
