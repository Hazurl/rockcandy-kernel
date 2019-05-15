#include <fixed.h>
#include <uefi.h>

#ifndef KERNEL_H
#define KERNEL_H

#define WITH_STD_OUT for(u8 __flag = 1; __flag; __flag = (flush(), 0))

/*
    Initialise buffered output
*/
void initStdOut(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* outputProtocol);

/*
    Push a character to the buffer
*/
void putc(u16 ch);

/*
    Push a null-terminated string to the buffer
*/
void puts(u16* str);

/*
    Push a formatted 10-based signed 32 bits integer
*/
void puti(s32 i);

/*
    Push a formatted 10-based signed 64 bits integer
*/
void putl(s64 l);

/*
    Push a formatted 10-based unsigned 32 bits integer
*/
void putui(u32 i);

/*
    Push a formatted 10-based unsigned 64 bits integer
*/
void putul(u64 l);

/*
    Push a formatted 16-based 8 bits integer
*/
void puthex(u8 h);

/*
    Force the buffer to be flushed to the output
*/
void flush();

#endif