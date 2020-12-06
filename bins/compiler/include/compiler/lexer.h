#pragma once

#include <stack>

#include "compiler/token.h"

class Lexer {
public:
  explicit Lexer(Range<char> source);

  void push();
  void pop();
  void commit();

  Token peek_token();
  Token consume_token();

private:
  Range<char> source_;

  std::stack<Range<char>> stack_;
  Range<char> current_;
};

class Marker {
public:
  explicit Marker(Lexer* lexer) : lexer_{lexer} {
    lexer_->push();
  }

  Marker(const Marker&) = delete;

  Marker(Marker&& other) noexcept : lexer_{other.lexer_} {
    other.lexer_ = nullptr;
  }

  Marker& operator=(const Marker&) = delete;

  Marker& operator=(Marker&& other) noexcept {
    lexer_ = other.lexer_;
    other.lexer_ = nullptr;

    return *this;
  }

  ~Marker() {
    if (lexer_) {
      lexer_->pop();
    }
  }

  void commit() {
    lexer_->commit();
    lexer_ = nullptr;
  }

private:
  Lexer* lexer_;
};
