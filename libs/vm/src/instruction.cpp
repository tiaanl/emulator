#include "vm/instruction.h"

namespace vm {

bool encode(Instruction* instruction, Range<char> dest) {
  if (dest.length() < sizeof(Instruction)) {
    return false;
  }

  std::memcpy((void*)dest.begin(), instruction, sizeof(Instruction));

  return true;
}

bool decode(Instruction* instruction, Range<char> source) {
  if (source.length() < sizeof(Instruction)) {
    return false;
  }

  std::memcpy(instruction, source.begin(), sizeof(Instruction));

  return true;
}

}  // namespace vm
