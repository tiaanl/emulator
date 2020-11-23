#ifndef PLATFORM_H_
#define PLATFORM_H_

using U8 = unsigned char;
using U16 = unsigned short;
using U32 = unsigned int;
using U64 = unsigned long long;

static_assert(sizeof(U8) == 1);
static_assert(sizeof(U16) == 2);
static_assert(sizeof(U32) == 4);
static_assert(sizeof(U64) == 8);

using I8 = char;
using I16 = short;
using I32 = int;
using I64 = long long;

static_assert(sizeof(I8) == 1);
static_assert(sizeof(I16) == 2);
static_assert(sizeof(I32) == 4);
static_assert(sizeof(I64) == 8);

using F32 = float;
using F64 = double;

static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);

#endif  // PLATFORM_H_