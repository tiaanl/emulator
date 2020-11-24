#pragma once

namespace vm {

class Address {
public:
  Address(U16 segment, U16 offset) : segment_(segment), offset_(offset) {}

  inline U16 segment() const {
    return segment_;
  }

  inline U16 offset() const {
    return offset_;
  }

  inline U32 flat() const {
    return (segment_ << 4u) + offset_;
  }

private:
  U16 segment_;
  U16 offset_;
};

}  // namespace vm
