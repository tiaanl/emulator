#ifndef PLATFORM_H_
#define PLATFORM_H_

using U8 = unsigned char;
using U16 = unsigned short;
using U32 = unsigned int;

static_assert(sizeof(U8) == 1);
static_assert(sizeof(U16) == 2);
static_assert(sizeof(U32) == 4);

using I8 = char;
using I16 = short;
using I32 = int;

static_assert(sizeof(I8) == 1);
static_assert(sizeof(I16) == 2);
static_assert(sizeof(I32) == 4);

#endif  // PLATFORM_H_
