#pragma once

#include <functional>

#include "vm/emulator/op_codes.h"
#include "vm/emulator/registers.h"

namespace vm {

class Disassembler {
public:
  using Emitter = std::function<void(const char*)>;

  Disassembler(U8* code, U16 code_size);

  void disassemble(Emitter&& emitter);

private:
  OpCode fetch_op_code();
  Register fetch_register();
  U8 fetch_u8();
  U16 fetch_u16();

  U8* code_;
  U16 code_size_;

  U8* current_;
};

}  // namespace vm
