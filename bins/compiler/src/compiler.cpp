#include <cassert>
#include <cstdio>
#include <vector>

#include "compiler/lexer.h"

int main() {
  auto source = R"(
    MOV  ax, 10
    JMP  0x5000
    MOV  [DS:DI], 0x30
    MOV  AX, [BP+6-2]
  )";

  std::vector<Token> tokens;
  Lexer lexer(source);

  for (Token token = lexer.consume_token(); token.type != TokenType::EndOfSource;
       token = lexer.consume_token()) {
    assert(token.type != TokenType::Unknown);
    if (token.type == TokenType::Whitespace) {
      continue;
    }
    printf("Token: %s (%llu, %llu)\n", token_type_to_string(token.type), token.start, token.length);
  }

  return 0;
}
