#include "vm/emulator/memory.h"

namespace vm {

Memory::Memory(U16 size) : size_(size), data_(new U8[size]) {}

Memory::~Memory() = default;

}  // namespace vm
