#include <cstdio>

#include "base/object_pool.h"

struct Token {
  const char* start;
  size_t length;
  Token* next;
};

int main() {
  printf("Compiler\n");

  // const char* source = "This is the source";

  base::ObjectPool<Token> tokenPool;
  for (auto i = 0; i < 500; ++i) {
    tokenPool.emplace();
  }

  return 0;
}
