#pragma once

#include <emulator/op_codes.h>
#include <emulator/registers.h>

#include <functional>

namespace assembler {

class Disassembler {
public:
  using Emitter = std::function<void(const char*)>;

  Disassembler(U8* code, U16 code_size);

  void disassemble(Emitter&& emitter);

private:
  emulator::OpCode fetch_op_code();
  emulator::Register fetch_register();
  U8 fetch_u8();
  U16 fetch_u16();

  U8* code_;
  U16 code_size_;

  U8* current_;
};

}  // namespace assembler
