#include "assembler/disassembler.h"

#include <cassert>
#include <cstdio>

namespace assembler {

namespace {

template <typename T>
struct AddressFrom {
  T value;
};

template <typename T>
AddressFrom<T> address_from(T from) {
  return {from};
}

U16 output(char* data, AddressFrom<emulator::Register> address_from_register) {
  auto reg = emulator::Register(address_from_register.value);
  return sprintf(data, "[%s]", emulator::register_to_string(reg));
}

U16 output(char* data, AddressFrom<U16> address_from_register) {
  return sprintf(data, "[0x%04x]", address_from_register.value);
}

U16 output(char* data, emulator::Register reg) {
  return sprintf(data, "%s", emulator::register_to_string(reg));
}

U16 output(char* data, U16 value) {
  return sprintf(data, "0x%04x", value);
}

U8 build_line(char* buffer, U16 offset, emulator::OpCode op_code) {
  return sprintf(buffer, "0x%04x:  %-6s", offset, emulator::op_code_to_string(op_code));
}

template <typename A>
U8 build_line(char* buffer, U16 offset, emulator::OpCode op_code, A&& a) {
  auto o = build_line(buffer, offset, op_code);
  o += output(buffer + o, a);

  return o;
}

template <typename A, typename B>
U8 build_line(char* buffer, U16 offset, emulator::OpCode op_code, A&& a, B&& b) {
  auto o = build_line(buffer, offset, op_code, a);
  o += sprintf(buffer + o, ", ");
  o += output(buffer + o, b);

  return o;
}

}  // namespace

Disassembler::Disassembler(U8* code, U16 code_size)
  : code_(code), code_size_(code_size), current_(code) {}

void Disassembler::disassemble(Emitter&& emitter) {
  char buffer[1024];

  for (;;) {
    auto offset = U16(current_ - code_);
    auto op_code = fetch_op_code();

    if (offset >= code_size_) {
      break;
    }

    switch (op_code) {
      case emulator::MOV_REG_FROM_REG: {
        auto to = fetch_register();
        auto from = fetch_register();
        build_line(buffer, offset, op_code, to, from);
        emitter(buffer);
        break;
      }

      case emulator::MOV_REG_FROM_LIT: {
        auto to = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, to, value);
        emitter(buffer);
        break;
      }

      case emulator::MOV_ADDR_FROM_LIT: {
        auto addr = fetch_u16();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, address_from(addr), value);
        emitter(buffer);
        break;
      }

      case emulator::MOV_REG_ADDR_FROM_LIT: {
        auto reg = fetch_register();
        auto value = fetch_u8();
        build_line(buffer, offset, op_code, address_from(reg), value);
        emitter(buffer);
        break;
      }

      case emulator::COMPARE_REG_TO_LIT: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case emulator::JUMP_ADDR: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case emulator::JUMP_IF_EQUAL: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case emulator::JUMP_IF_NOT_EQUAL: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case emulator::ADD: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case emulator::SUBTRACT: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case emulator::MULTIPLY: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case emulator::HALT: {
        build_line(buffer, offset, op_code);
        emitter(buffer);
        break;
      }

      default: {
        printf("Invalid op_code found: %d\n", op_code);
        assert(0);
        break;
      }
    }

    if (op_code == emulator::OpCode::HALT) {
      break;
    }
  }
}

emulator::OpCode Disassembler::fetch_op_code() {
  return emulator::OpCode(fetch_u8());
}

emulator::Register Disassembler::fetch_register() {
  return emulator::Register(fetch_u8());
}

U8 Disassembler::fetch_u8() {
  return *current_++;
}

U16 Disassembler::fetch_u16() {
  U16 result = *(U16*)(current_);
  current_ += 2;
  return result;
}

}  // namespace assembler
