#include "vm/emulator/memory.h"

namespace vm {

Memory::Memory() = default;

Memory::~Memory() = default;

Address Memory::allocate_page() {
  pages_.emplace_back();

  return {U16(pages_.size() - 1), 0x0000};
}

}  // namespace vm
