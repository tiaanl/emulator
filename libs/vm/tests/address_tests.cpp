#include <vm/emulator/address.h>

#include <catch2/catch.hpp>
#include <iomanip>
#include <ostream>

namespace vm {

std::ostream& operator<<(std::ostream& os, const Address& address) {
  os << std::setfill('0') << std::setw(4) << std::hex << address.segment() << ":"
     << address.offset();
  return os;
}

TEST_CASE("address") {
  Address with_default;
  CHECK(with_default.segment() == 0);
  CHECK(with_default.offset() == 0);

  Address with_flat(100);
  CHECK(with_flat.segment() == 0);
  CHECK(with_flat.offset() == 100);

  Address with_flat_and_segment(0x00001FFFF);
  CHECK(with_flat_and_segment.offset() == 0xFFFF);
  CHECK(with_flat_and_segment.segment() == 0x0100);

  CHECK(Address(0x00001FFFF) == Address(0x0100, 0xFFFF));
  CHECK(Address(0x00001FFFE) != Address(0x0100, 0xFFFF));
}

}  // namespace vm
