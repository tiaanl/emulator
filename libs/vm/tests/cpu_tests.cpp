#include <vm/emulator/cpu.h>
#include <vm/emulator/memory.h>

#include <catch2/catch.hpp>

namespace vm {

TEST_CASE("registers") {
  Memory memory;
  Bus bus;
  CPU cpu(&bus);
}

}  // namespace vm
