#pragma once

namespace vm {

enum class Register : U8 {
  R1,
  R2,
  R3,
  R4,

  IP,
  SP,
  BP,
  FL,

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

#define DEFINE_REG_16(Name, FName)                                                                 \
  U16 FName() {                                                                                    \
    return values_[U8(Register::Name)];                                                            \
  }                                                                                                \
  void FName(U16 value) {                                                                          \
    values_[U8(Register::Name)] = value;                                                           \
  }

  DEFINE_REG_16(R1, r1)
  DEFINE_REG_16(R2, r2)
  DEFINE_REG_16(R3, r3)
  DEFINE_REG_16(R4, r4)
  DEFINE_REG_16(IP, ip)
  DEFINE_REG_16(SP, sp)
  DEFINE_REG_16(BP, bp)
  DEFINE_REG_16(FL, flags)

#undef DEFINE_REG_16

private:
  U16 values_[U8(Register::Count)] = {};
};

const char* register_to_string(Register reg);

}  // namespace vm
