#pragma once

class TokenIterator {
public:
  TokenIterator next();

private:
  Source source_;
};
