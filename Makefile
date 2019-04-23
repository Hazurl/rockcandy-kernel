CC=gcc
CFLAGS=-ffreestanding -Iinclude -std=c17
LD=x86_64-w64-mingw32-ld
LDFLAGS=-nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main

OBJECTS=main.o

kernel: $(addprefix src/, $(OBJECTS))
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(addprefix src/, $(OBJECTS))
