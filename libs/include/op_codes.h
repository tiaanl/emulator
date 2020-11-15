#ifndef OPCODES_H_
#define OPCODES_H_

#include "platform.h"

// MOV AX, SP
#define MOV_REG_FROM_REG 0x10

// MOV AX, 10h
#define MOV_REG_FROM_LIT 0x11

const char* op_code_to_string(U8 op_code);

#endif  // OPCODES_H_
