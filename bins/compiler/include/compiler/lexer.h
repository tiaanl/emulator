#pragma once

#include <string_view>

#include "compiler/token.h"

class Lexer {
public:
  explicit Lexer(Range<char> source);

  Token peek_token();
  Token consume_token();

private:
  Range<char> source_;
  Range<char> current_;
};
