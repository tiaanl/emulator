#pragma once

#include "compiler/range.h"
#include "compiler/token_type.h"

struct Token {
  TokenType type;
  Range<char> data;

  Token(TokenType type, Range<char> data) : type(type), data(data) {}
};
