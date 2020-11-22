#pragma once

namespace emulator {

// 8086/8088
//
// AX (AH/AL) = Primary Accumulator
// BX (BH/BL) = Base Accumulator
// CX (CH/CL) = Counter Accumulator
// DX (DH/DL) = Other Accumulator
//
// CS = Code Segment
// DS = Data Segment
// ES = Extra Segment
// SS = Stack Segment
//
// SI = Source Index
// DI = Destination Index
// BP = Base Pointer
// SP = Stack Pointer
// IP = Instruction Pointer
// Flags = Various CPU Flags

enum class Register : U8 {
  AX,  // Primary Accumulator
  BX,  // Base Accumulator
  CX,  // Counter Accumulator
  DX,  // Other Accumulator

  CS,  // Code Segment
  DS,  // Data Segment
  ES,  // Extra Segment
  SS,  // Stack Segment

  SI,  // Source Index
  DI,  // Destination Index
  BP,  // Base Pointer
  SP,  // Stack Pointer
  IP,  // Instruction Pointer

  CF,  // Various CPU Flags

  Count,  // Number Of Registers
};

class Registers {
public:
  inline U16 get(Register reg) {
    return values_[U8(reg)];
  }

  inline void set(Register reg, U16 value) {
    values_[U8(reg)] = value;
  }

#define DECL_REG_16(Name)                                                                          \
  U16 Name() {                                                                                     \
    return values_[U8(Register::Name)];                                                            \
  }                                                                                                \
  void Name(U16 value) {                                                                           \
    values_[U8(Register::Name)] = value;                                                                                                 \
  }

  DECL_REG_16(AX)
  DECL_REG_16(BX)
  DECL_REG_16(CX)
  DECL_REG_16(DX)
  DECL_REG_16(CS)
  DECL_REG_16(DS)
  DECL_REG_16(ES)
  DECL_REG_16(SS)
  DECL_REG_16(SI)
  DECL_REG_16(DI)
  DECL_REG_16(BP)
  DECL_REG_16(SP)
  DECL_REG_16(IP)
  DECL_REG_16(CF)

#undef DECL_REG_16

private:
  U16 values_[U8(Register::Count)] = {};
};

const char* register_to_string(Register reg);

}  // namespace emulator
