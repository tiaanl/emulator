#include <compiler/disassembler.h>

#include <cstdio>

#include "compiler/assembler.h"
#include "compiler/lexer.h"
#include "compiler/parser.h"

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
  if (node) {
    node->emit(&assembler);
  }

  vm::Disassembler disassembler{(U8*)assembler.code(), U16(assembler.size())};
  disassembler.disassemble([](const char* line) {
    printf("%s\n", line);
  });

  return 0;
}
