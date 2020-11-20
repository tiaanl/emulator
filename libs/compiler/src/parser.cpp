#include "compiler/parser.h"

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

// static
Parser Parser::create(const char* source, U16 length) {
  Parser result = {};
  result.source = source;
  result.length = length;
  return result;
}

Token Parser::peek_token() {
  if (current >= length) {
    return eof_token(length);
  }

  auto ch = source[current];

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
        current,
        1,
    };
  }

  if (ch == ':') {
    return Token{
        TokenType::Colon,
        current,
        1,
    };
  }

  return {
      TokenType::Unknown,
      current,
      0,
  };
}

Token Parser::consume_token() {
  auto token = peek_token();
  current += token.length;
  return token;
}

Token Parser::peek_whitespace() {
  U16 count = 0;
  while (is_whitespace(source[current + count]) && current + count < length) {
    ++count;
  }

  return {
      TokenType::Whitespace,
      current,
      count,
  };
}

Token Parser::peek_letters() {
  U16 count = 0;
  while (is_letter(source[current + count]) && current + count < length) {
    ++count;
  }

  return {
      TokenType::Word,
      current,
      count,
  };
}

Token Parser::peek_numbers() {
  U16 count = 0;
  while (is_number(source[current + count]) && current + count < length) {
    ++count;
  }

  return {
      TokenType::Number,
      current,
      count,
  };
}

}  // namespace compiler
