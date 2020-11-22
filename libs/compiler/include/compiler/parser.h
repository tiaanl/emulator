#pragma once

namespace compiler {

enum class TokenType : U16 {
  Whitespace,
  Word,
  Number,
  Comma,
  Colon,
  Eof,
  Unknown,
};

struct Token {
  TokenType type;
  U16 start;
  U16 length;
};

class Parser {
public:
  Parser(const char* source, U16 length);

  Token peek_token();
  Token consume_token();

private:
  Token peek_whitespace();
  Token peek_letters();
  Token peek_numbers();

  const char* source_;
  U16 length_;

  U16 current_;
};

}  // namespace compiler
