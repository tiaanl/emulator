#pragma once

#include <string_view>

#include "compiler/token.h"

class Lexer {
public:
  explicit Lexer(std::string_view source);

  Token consume_token();

private:
  Token consume_whitespace();
  Token consume_new_line();
  Token consume_punctuation();
  Token consume_identifier();
  Token consume_number();

  const char* source_;
  MemSize source_length_;

  MemSize current_pos_;
};
