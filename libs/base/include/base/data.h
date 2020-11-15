#pragma once

inline U8 read_u8(const U8* data) {
  return *data;
}

inline U16 read_u16(const U8* data) {
  return *(U16*)data;
}

inline void write_u8(U8* data, U8 value) {
  *data = value;
}

inline void write_u16(U8* data, U16 value) {
  *((U16*)data) = value;
}
