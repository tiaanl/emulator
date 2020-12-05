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
