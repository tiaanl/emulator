#include "compiler/token.h"

#include <cassert>

const char* token_type_to_string(TokenType token_type) {
  switch (token_type) {
    case TokenType::EndOfSource:
      return "EndOfSource";

    case TokenType::Whitespace:
      return "Whitespace";

    case TokenType::NewLine:
      return "NewLine";

    case TokenType::Comma:
      return "Comma";

    case TokenType::OpenSquareBracket:
      return "OpenSquareBracket";

    case TokenType::CloseSquareBracket:
      return "CloseSquareBracket";

    case TokenType::Colon:
      return "Colon";

    case TokenType::Plus:
      return "Plus";

    case TokenType::Minus:
      return "Minus";

    case TokenType::Identifier:
      return "Identifier";

    case TokenType::Number:
      return "Number";

    case TokenType::Unknown:
      return "Unknown";
  }

  assert(false);
  return "<invalid>";
}
