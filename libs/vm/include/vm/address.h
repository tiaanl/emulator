#pragma once

namespace vm {

class Address {
public:
  Address() : address_(0) {}

  explicit Address(U32 address) : address_(address) {}

  Address(U16 segment, U16 offset) : address_((segment << 0x04u) + offset) {}

  bool operator==(const Address& right) const {
    return address_ == right.address_;
  }

  bool operator!=(const Address& right) const {
    return !operator==(right);
  }

  Address& operator+=(U32 right) {
    address_ += right;
    return *this;
  }

  friend Address operator+(Address left, U32 right) {
    return Address(left.address_ + right);
  }

  [[nodiscard]] U16 segment() const {
    return U16((address_ & 0xFFFF0000u) >> 0x04u);
  }

  [[nodiscard]] U16 offset() const {
    return U16(address_ & 0xFFFFu);
  }

  [[nodiscard]] U32 flat() const {
    return address_;
  }

private:
  U32 address_;
};

}  // namespace vm
