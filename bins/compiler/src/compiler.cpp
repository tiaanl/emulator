#include "compiler/ast.h"
#include "compiler/lexer.h"
#include "compiler/parser.h"
#include "vm/assembler/assembler.h"

int main() {
  auto source = R"(
    MOV  R1, 10
    JMP  0x5000
    MOV  [R2], 0x30
    MOV  [0x30], 9
  )";

  Lexer lexer(range_from(source));

  auto parser = Parser{&lexer};
  vm::Assembler assembler;
  auto node = parser.parse_compound();

  return 0;
}
