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

#define DECL_REG_16(Name, FName)                                                                   \
  U16 FName() {                                                                                    \
    return values_[U8(Register::Name)];                                                            \
  }                                                                                                \
  void FName(U16 value) {                                                                          \
    values_[U8(Register::Name)] = value;                                                           \
  }

  DECL_REG_16(AX, ax)
  DECL_REG_16(BX, bx)
  DECL_REG_16(CX, cx)
  DECL_REG_16(DX, dx)
  DECL_REG_16(CS, cs)
  DECL_REG_16(DS, ds)
  DECL_REG_16(ES, es)
  DECL_REG_16(SS, ss)
  DECL_REG_16(SI, si)
  DECL_REG_16(DI, di)
  DECL_REG_16(BP, bp)
  DECL_REG_16(SP, sp)
  DECL_REG_16(IP, ip)
  DECL_REG_16(CF, cf)

#undef DECL_REG_16

private:
  U16 values_[U8(Register::Count)] = {};
};

const char* register_to_string(Register reg);

}  // namespace emulator
