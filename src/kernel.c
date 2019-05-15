#include <kernel.h>

#define STDOUT_BUFFER_LENGTH 63

typedef struct STDOUT {
    // '+1' to be null-terminated
    u16 buffer[STDOUT_BUFFER_LENGTH + 1];
    u8 size;

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* outputProtocol;
} STDOUT;

STDOUT StdOut;

void initStdOut(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* outputProtocol) {
    StdOut.outputProtocol = outputProtocol;
    StdOut.size = 0;
}

void putc(u16 ch) {
    StdOut.buffer[StdOut.size] = ch;
    ++StdOut.size;

    if(StdOut.size >= STDOUT_BUFFER_LENGTH) {
        flush();
    }
};

void puts(u16* str) {
    for(u16 ch = *str; ch != '\0'; ch = *++str) {
        putc(ch);
    }
}

void puti(s32 i) {
    if (i < 0) {
        putc('-');
        i = -i;
    }

    putui((u32)i);
}

void putl(s64 l) {
    if (l < 0) {
        putc('-');
        l = -l;
    }

    putul((u64)l);
}

void _putui(u32 i) {
    if (i == 0) {
        return;
    }

    u32 rem = i % 10;
    u32 quot = i / 10;

    _putui(quot);
    putc(rem + '0');
}

void putui(u32 i) {
    if (i == 0) {
        putc('0');
    }
    else {
        _putui(i);
    }
}

void _putul(u64 l) {
    if (l == 0) {
        return;
    }

    u32 rem = l % 10;
    u32 quot = l / 10;

    _putul(quot);
    putc(rem + '0');
}

void putul(u64 l) {
    if (l == 0) {
        putc('0');
    }
    else {
        _putul(l);
    }
}

void puthex(u8 h) {
    u8 mask = 0xF;
    while(mask) {
        u8 value = h & mask;
        if (value < 10) {
            putc('0' + value);
        }
        else {
            putc('A' + value - 10);
        }
        mask >>= 4;
    }
}

void flush() {
    StdOut.buffer[StdOut.size] = '\0';
    StdOut.outputProtocol->OutputString(StdOut.outputProtocol, StdOut.buffer);
    StdOut.size = 0;
}
