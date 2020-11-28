#pragma once

enum class TokenType : U8 {
  EndOfSource,

  // Whitespace
  Whitespace,
  NewLine,

  // Punctuation
  Comma,               // ,
  OpenSquareBracket,   // [
  CloseSquareBracket,  // ]
  Colon,               // :
  Plus,                // +
  Minus,               // -

  // Literals
  Identifier,
  Number,

  Unknown,
};

struct Token {
  TokenType type;
  MemSize start;
  MemSize length;

  Token(TokenType type, MemSize start, MemSize length = 0)
    : type(type), start(start), length(length) {}
};

const char* token_type_to_string(TokenType token_type);
