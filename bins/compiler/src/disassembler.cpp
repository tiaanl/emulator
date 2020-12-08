#include "../include/compiler/disassembler.h"

#include <cassert>
#include <cstdio>

namespace vm {

namespace {

template <typename T>
struct AddressFrom {
  T value;
};

template <typename T>
AddressFrom<T> address_from(T from) {
  return {from};
}

U16 output(char* data, AddressFrom<Register> address_from_register) {
  auto reg = Register(address_from_register.value);
  return U16(sprintf(data, "[%s]", register_to_string(reg)));
}

U16 output(char* data, AddressFrom<U16> address_from_register) {
  return U16(sprintf(data, "[0x%04x]", address_from_register.value));
}

U16 output(char* data, Register reg) {
  return U16(sprintf(data, "%s", register_to_string(reg)));
}

U16 output(char* data, U16 value) {
  return U16(sprintf(data, "0x%04x", value));
}

U8 build_line(char* buffer, U16 offset, OpCode op_code) {
  return U8(sprintf(buffer, "0x%04x:  %-6s", offset, op_code_to_string(op_code)));
}

template <typename A>
U8 build_line(char* buffer, U16 offset, OpCode op_code, A&& a) {
  int o = build_line(buffer, offset, op_code);
  o += output(buffer + o, a);

  return U8(o);
}

template <typename A, typename B>
U8 build_line(char* buffer, U16 offset, OpCode op_code, A&& a, B&& b) {
  int o = build_line(buffer, offset, op_code, a);
  o += sprintf(buffer + o, ", ");
  o += output(buffer + o, b);

  return U8(o);
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
      case OpCode::MOV_REG_FROM_REG: {
        auto to = fetch_register();
        auto from = fetch_register();
        build_line(buffer, offset, op_code, to, from);
        emitter(buffer);
        break;
      }

      case OpCode::MOV_REG_FROM_LIT: {
        auto to = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, to, value);
        emitter(buffer);
        break;
      }

      case OpCode::MOV_ADDR_FROM_LIT: {
        auto addr = fetch_u16();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, address_from(addr), value);
        emitter(buffer);
        break;
      }

      case OpCode::MOV_REG_ADDR_FROM_LIT: {
        auto reg = fetch_register();
        auto value = fetch_u8();
        build_line(buffer, offset, op_code, address_from(reg), value);
        emitter(buffer);
        break;
      }

      case OpCode::COMPARE_REG_TO_LIT: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case OpCode::JUMP_ADDR: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case OpCode::JUMP_IF_EQUAL: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case OpCode::JUMP_IF_NOT_EQUAL: {
        auto addr = fetch_u16();
        build_line(buffer, offset, op_code, addr);
        emitter(buffer);
        break;
      }

      case OpCode::ADD: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case OpCode::SUBTRACT: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case OpCode::MULTIPLY: {
        auto reg = fetch_register();
        auto value = fetch_u16();
        build_line(buffer, offset, op_code, reg, value);
        emitter(buffer);
        break;
      }

      case OpCode::HALT: {
        build_line(buffer, offset, op_code);
        emitter(buffer);
        break;
      }

      default: {
        printf("Invalid op_code found: %d\n", U8(op_code));
        assert(0);
        break;
      }
    }

    if (op_code == OpCode::HALT) {
      break;
    }
  }
}

OpCode Disassembler::fetch_op_code() {
  return OpCode(fetch_u8());
}

Register Disassembler::fetch_register() {
  return Register(fetch_u8());
}

U8 Disassembler::fetch_u8() {
  return *current_++;
}

U16 Disassembler::fetch_u16() {
  U16 result = *(U16*)(current_);
  current_ += 2;
  return result;
}

}  // namespace vm
