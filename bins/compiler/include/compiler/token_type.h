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
  DecimalNumber,
  HexNumber,

  Unknown,
};

const char* token_type_to_string(TokenType token_type);
