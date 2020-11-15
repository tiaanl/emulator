#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "op_codes.h"

typedef struct {
  U8 *data;
  U16 size;
} Memory;

void MEM_create(Memory *memory, U16 size) {
  memory->data = malloc(size);
  memory->size = size;
}

void MEM_destroy(Memory *memory) {
  free(memory->data);
  memory->data = NULL;
  memory->size = 0;
}

void MEM_write_u8(Memory *memory, U16 offset, U8 value) {
  memory->data[offset] = value;
}

void MEM_write_u16(Memory *memory, U16 offset, U16 value) {
  memcpy(memory->data + offset, &value, sizeof(value));
}

void MEM_write_u32(Memory *memory, U16 offset, U32 value) {
  memcpy(memory->data + offset, &value, sizeof(value));
}

U8 MEM_read_u8(Memory *memory, U16 offset) { return memory->data[offset]; }

U16 MEM_read_u16(Memory *memory, U16 offset) {
  return *(U16 *)(&memory->data[offset]);
}

U32 MEM_read_u32(Memory *memory, U16 offset) {
  return *(U32 *)(&memory->data[offset]);
}

void step(CPU *cpu, Memory *memory) {
  U8 op_code = MEM_read_u8(memory, cpu->ip);

  printf("OpCode: %s\n", op_code_to_string(op_code));

  switch (op_code) {
    case MOV_REG_FROM_REG: {
      U8 reg_to = MEM_read_u8(memory, cpu->ip + 1);
      U8 reg_from = MEM_read_u8(memory, cpu->ip + 2);
      cpu->ip += 3;
      CPU_set_register(cpu, reg_to, CPU_get_register(cpu, reg_from));
      break;
    }

    case MOV_REG_FROM_LIT: {
      U8 reg = MEM_read_u8(memory, cpu->ip + 1);
      U16 lit = MEM_read_u16(memory, cpu->ip + 2);
      cpu->ip += 4;
      CPU_set_register(cpu, reg, lit);
      break;
    }

    default:
      assert(0);
      break;
  }
}

int main() {
  Memory memory;

  MEM_create(&memory, 16 * 16);
  MEM_write_u8(&memory, 0, MOV_REG_FROM_LIT);
  MEM_write_u8(&memory, 1, REG_AX);
  MEM_write_u16(&memory, 2, 0x1234);

  CPU cpu;
  CPU_init(&cpu);

  step(&cpu, &memory);

  MEM_destroy(&memory);

  return 0;
}
