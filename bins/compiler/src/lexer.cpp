#include "compiler/lexer.h"

#include <cassert>
#include <cstdio>

namespace {

bool is_whitespace(I8 ch) {
  return (ch == ' ') || (ch == '\t');
}

bool is_new_line(I8 ch) {
  return (ch == '\n') || (ch == '\r');
}

bool is_alpha(I8 ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_numeric(I8 ch) {
  return (ch >= '0' && ch <= '9');
}

bool is_alpha_numeric(I8 ch) {
  return is_alpha(ch) || is_numeric(ch);
}

bool is_numeric_extra(I8 ch) {
  return is_numeric(ch) || ch == '.' || ch == 'X' || ch == 'x' || ch == 'b' || ch == 'B';
}

bool is_punctuation(I8 ch) {
  static const char* punctuation = ",[]:+-";
  for (const char* p = punctuation; *p; ++p) {
    if (ch == *p) {
      return true;
    }
  }
  return false;
}

}  // namespace

Lexer::Lexer(std::string_view source)
  : source_(source.data()), source_length_(source.size()), current_pos_(0) {}

Token Lexer::consume_token() {
  if (current_pos_ >= source_length_) {
    return {TokenType::EndOfSource, current_pos_};
  }

  I8 ch = source_[current_pos_];

  if (is_whitespace(ch)) {
    return consume_whitespace();
  }

  if (is_new_line(ch)) {
    return consume_new_line();
  }

  if (is_alpha(ch)) {
    return consume_identifier();
  }

  if (is_numeric(ch)) {
    return consume_number();
  }

  if (is_punctuation(ch)) {
    return consume_punctuation();
  }

  return {TokenType::Unknown, current_pos_++, 1};
}

Token Lexer::consume_whitespace() {
  Token result(TokenType::Whitespace, current_pos_);

  while (current_pos_ < source_length_ && is_whitespace(source_[current_pos_])) {
    ++current_pos_;
  }

  result.length = current_pos_ - result.start;

  return result;
}

Token Lexer::consume_new_line() {
  Token result(TokenType::NewLine, current_pos_);

  while (current_pos_ < source_length_ && is_new_line(source_[current_pos_])) {
    ++current_pos_;
  }

  result.length = current_pos_ - result.start;

  return result;
}

Token Lexer::consume_punctuation() {
  MemSize start = current_pos_++;
  I8 ch = source_[start];

  switch (ch) {
    case ',':
      return {TokenType::Comma, start, 1};

    case '[':
      return {TokenType::OpenSquareBracket, start, 1};

    case ']':
      return {TokenType::CloseSquareBracket, start, 1};

    case ':':
      return {TokenType::Colon, start, 1};

    case '+':
      return {TokenType::Plus, start, 1};

    case '-':
      return {TokenType::Minus, start, 1};

    default:
      assert(0);
      return {TokenType::Unknown, start, 1};
  }
}

Token Lexer::consume_identifier() {
  Token result(TokenType::Identifier, current_pos_);

  while (current_pos_ < source_length_ && is_alpha_numeric(source_[current_pos_])) {
    ++current_pos_;
  }

  result.length = current_pos_ - result.start;
  return result;
}

Token Lexer::consume_number() {
  Token result(TokenType::Number, current_pos_);

  while (current_pos_ < source_length_ && is_numeric_extra(source_[current_pos_])) {
    ++current_pos_;
  }

  result.length = current_pos_ - result.start;
  return result;
}
