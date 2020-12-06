#include "compiler/lexer.h"

#include <cassert>
#include <cstdio>

namespace {

inline bool is_whitespace(char ch) {
  return (ch == ' ') || (ch == '\t');
}

inline bool is_new_line(char ch) {
  return (ch == '\n') || (ch == '\r');
}

inline bool is_alpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

inline bool is_numeric(char ch) {
  return (ch >= '0' && ch <= '9');
}

inline bool is_hex_numeric(char ch) {
  return ch == 'x' || ch == 'X' || is_numeric(ch);
}

inline bool is_alpha_numeric(char ch) {
  return is_alpha(ch) || is_numeric(ch);
}

inline bool is_numeric_extra(char ch) {
  return is_numeric(ch) || ch == '.' || ch == 'X' || ch == 'x' || ch == 'b' || ch == 'B';
}

inline bool is_punctuation(char ch) {
  static const char* punctuation = ",[]:+-";
  for (const char* p = punctuation; *p; ++p) {
    if (ch == *p) {
      return true;
    }
  }
  return false;
}

#define PEEK_CONTINUOUS(Predicate)                                                                 \
  [](auto source) {                                                                                \
    return front_until_not(source, (Predicate));                                                   \
  }

#define PEEK_PUNCTUATION(Char)                                                                     \
  [](auto range) {                                                                                 \
    if (*range.begin() == (Char)) {                                                                \
      return front(range, 1);                                                                      \
    }                                                                                              \
    return Range<char>{};                                                                          \
  }

Range<char> peek_identifier(Range<char> source) {
  if (is_alpha(*source.begin())) {
    return front_until_not(source, is_alpha_numeric);
  }

  return {};
}

Range<char> peek_hex_number(Range<char> source) {
  if (source.length() < 3) {
    return {};
  }

  const char* c = source.begin();
  if (c[0] != '0' || (c[1] != 'x' && c[1] != 'X')) {
    return {};
  }

  if (is_numeric(*source.begin())) {
    return front_until_not(source, is_hex_numeric);
  }

  return {};
}

using TokenTypeFunc = Range<char> (*)(Range<char>);

struct {
  TokenType type;
  TokenTypeFunc func;
} kTokenEntries[] = {
    {TokenType::Comma, PEEK_PUNCTUATION(',')},
    {TokenType::OpenSquareBracket, PEEK_PUNCTUATION('[')},
    {TokenType::CloseSquareBracket, PEEK_PUNCTUATION(']')},
    {TokenType::Colon, PEEK_PUNCTUATION(':')},
    {TokenType::Plus, PEEK_PUNCTUATION('+')},
    {TokenType::Minus, PEEK_PUNCTUATION('-')},
    {TokenType::NewLine, PEEK_CONTINUOUS(is_new_line)},
    {TokenType::HexNumber, peek_hex_number},
    {TokenType::DecimalNumber, PEEK_CONTINUOUS(is_numeric)},
    {TokenType::Identifier, peek_identifier},
};

}  // namespace

Lexer::Lexer(Range<char> source) : source_(source), current_(source) {}

void Lexer::push() {
  stack_.push(current_);
}

void Lexer::pop() {
  if (stack_.empty()) {
    return;
  }

  current_ = stack_.top();
  stack_.pop();
}

void Lexer::commit() {
  if (stack_.empty()) {
    return;
  }

  stack_.pop();
}

Token Lexer::peek_token() {
  auto range_to_check = advance_until_not(current_, is_whitespace);

  if (range_to_check.empty()) {
    return {TokenType::EndOfSource, {}};
  }

  for (auto& token_entry : kTokenEntries) {
    auto found = token_entry.func(range_to_check);
    if (!found.empty()) {
      return {token_entry.type, found};
    }
  }

  Token result{TokenType::Unknown, front(current_, 1)};
  return result;
}

Token Lexer::consume_token() {
  auto token = peek_token();
  current_ = {token.data.end(), current_.end()};
  return token;
}
