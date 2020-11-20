#include <compiler/parser.h>

#include <cassert>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {
  auto source = R"(
    MOV   ax, 50
    MOV   ax, ip
    CMP   ax, 77
    JZ    after
    MOV   ax, 77
  after:
    HALT
  )";

  auto parser = compiler::Parser::create(source, strlen(source));

  auto parsing = true;
  while (parsing) {
    auto token = parser.consume_token();
    switch (token.type) {
      case compiler::TokenType::Whitespace: {
        printf("Whitespace (%d:%d)\n", token.start, token.length);
        break;
      }

      case compiler::TokenType::Word: {
        printf("Word (%d:%d)\n", token.start, token.length);
        break;
      }

      case compiler::TokenType::Number: {
        printf("Number (%d:%d)\n", token.start, token.length);
        break;
      }

      case compiler::TokenType::Comma: {
        printf("Comma (%d:%d)\n", token.start, token.length);
        break;
      }

      case compiler::TokenType::Colon: {
        printf("Colon (%d:%d)\n", token.start, token.length);
        break;
      }

      case compiler::TokenType::Eof: {
        parsing = false;
        printf("End of file\n");
        break;
      }

      case compiler::TokenType::Unknown: {
        parsing = false;
        printf("Unknown token found\n");
        break;
      }

      default:
        assert(false);
        break;
    }
  }

  return 0;
}
