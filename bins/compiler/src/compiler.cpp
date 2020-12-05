#include <cstdio>

#include "compiler/lexer.h"

void print_token(const Token& token) {
  printf("Token: %s (%llu)\n", token_type_to_string(token.type), token.data.length());
}

int main() {
  auto source = R"(
    MOV  ax, 10
    JMP  0x5000
    MOV  [DS:DI], 0x30
    MOV  AX, [BP+6-2]
  )";

  Lexer lexer(range_from(source));

  for (;;) {
    auto token = lexer.consume_token();

    print_token(token);

    if (token.type == TokenType::EndOfSource || token.type == TokenType::Unknown) {
      break;
    }
  }

  return 0;
}
