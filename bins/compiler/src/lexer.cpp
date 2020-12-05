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
    return find_if_not(source, (Predicate));                                                       \
  }

#define PEEK_PUNCTUATION(Char)                                                                     \
  [](auto range) {                                                                                 \
    if (*range.begin() == (Char)) {                                                                \
      return range.front(1);                                                                       \
    }                                                                                              \
    return range.front(0);                                                                         \
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
    {TokenType::Whitespace, PEEK_CONTINUOUS(is_whitespace)},
    {TokenType::Identifier, PEEK_CONTINUOUS(is_alpha)},
    {TokenType::Number, PEEK_CONTINUOUS(is_numeric)},
};

}  // namespace

Lexer::Lexer(Range<char> source) : source_(source), current_(source) {}

Token Lexer::peek_token() {
  if (current_.empty()) {
    return {TokenType::EndOfSource, current_};
  }

  for (auto& token_entry : kTokenEntries) {
    auto found = token_entry.func(current_);
    if (!found.empty()) {
      return {token_entry.type, found};
    }
  }

  Token result{TokenType::Unknown, current_.front(1)};
  return result;
}

Token Lexer::consume_token() {
  auto token = peek_token();
  current_ = current_.middle(token.data.length());
  return token;
}
