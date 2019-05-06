// This header is specifically for defining fixed-width data types

#ifndef FIXED_H
#define FIXED_H

typedef signed char s8;
typedef unsigned char u8;

#if __SIZEOF_SHORT__ == 2
typedef signed short s16;
typedef unsigned short u16;
#else
#error "Unable to define a 16-bit fixed-width integer"
#endif

#if __SIZEOF_INT__ == 4
typedef signed int s32;
typedef unsigned int u32;
#else
#error "Unable to define a 32-bit fixed-width integer"
#endif

#if __SIZEOF_LONG__ == 8
typedef signed long s64;
typedef unsigned long u64;
#elif __SIZEOF_LONG_LONG__ == 8
typedef signed long long s64;
typedef unsigned long long u64;
#else
#error "Unable to define a 64-bit fixed-width integer"
#endif

#endif
