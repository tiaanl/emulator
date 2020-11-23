#include "vm/compiler/parser.h"

namespace compiler {

namespace {

bool is_whitespace(I8 ch) {
  return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

bool is_letter(I8 ch) {
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool is_number(I8 ch) {
  return ch >= '0' && ch <= '9';
}

Token eof_token(U16 length) {
  Token result = {};
  result.type = TokenType::Eof;
  result.start = length;
  result.length = 0;
  return result;
}

}  // namespace

Parser::Parser(const char* source, U16 length) : source_(source), length_(length), current_(0) {}

Token Parser::peek_token() {
  if (current_ >= length_) {
    return eof_token(length_);
  }

  auto ch = source_[current_];

  if (is_whitespace(ch)) {
    return peek_whitespace();
  }

  if (is_letter(ch)) {
    return peek_letters();
  }

  if (is_number(ch) || ch == '-') {
    return peek_numbers();
  }

  if (ch == ',') {
    return Token{
        TokenType::Comma,
        current_,
        1,
    };
  }

  if (ch == ':') {
    return Token{
        TokenType::Colon,
        current_,
        1,
    };
  }

  return {
      TokenType::Unknown,
      current_,
      0,
  };
}

Token Parser::consume_token() {
  auto token = peek_token();
  current_ += token.length;
  return token;
}

Token Parser::peek_whitespace() {
  U16 count = 0;
  while (is_whitespace(source_[current_ + count]) && current_ + count < length_) {
    ++count;
  }

  return {
      TokenType::Whitespace,
      current_,
      count,
  };
}

Token Parser::peek_letters() {
  U16 count = 0;
  while (is_letter(source_[current_ + count]) && current_ + count < length_) {
    ++count;
  }

  return {
      TokenType::Word,
      current_,
      count,
  };
}

Token Parser::peek_numbers() {
  U16 count = 0;
  while (is_number(source_[current_ + count]) && current_ + count < length_) {
    ++count;
  }

  return {
      TokenType::Number,
      current_,
      count,
  };
}

}  // namespace compiler
