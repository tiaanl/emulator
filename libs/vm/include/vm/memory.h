#pragma once

#include "vm/address.h"

namespace vm {

class Memory {
public:
  Memory();
  ~Memory();

  U8 fetch(U16 addr) {
    return data_[addr];
  }

  void store(U16 addr, U8 value) {
    data_[addr] = value;
  }

private:
  U8 data_[0xFFFF];
};

}  // namespace vm
