#include "emulator/memory.h"

namespace emulator {

Memory::Memory(U16 size) : size_(size), data_(new U8[size]) {}

Memory::~Memory() = default;

}  // namespace emulator
