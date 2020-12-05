#pragma once

#include "compiler/range.h"
#include "compiler/token_type.h"

struct Token {
  TokenType type;
  Range<char> data;

  Token(TokenType type, Range<char> data) : type(type), data(data) {}
};

const char* token_type_to_string(TokenType token_type);
