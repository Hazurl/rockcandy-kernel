CC=x86_64-w64-mingw32-gcc
CFLAGS=-ffreestanding -Iinclude -std=c17
LD=x86_64-w64-mingw32-gcc
LDFLAGS=-nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main

OBJECTS=main.o elf.o

kernel: $(addprefix src/, $(OBJECTS))
	$(LD) $(LDFLAGS) -o rockcandy.efi $^
	dd if=/dev/zero of=rockcandy.img bs=1048576 count=64 status=none
	/sbin/mkfs.fat -F 32 -n ROCKCANDY rockcandy.img
	mkdir temp
	sudo mount -t vfat rockcandy.img temp/
	sudo mkdir -p temp/EFI/boot/
	sudo cp rockcandy.efi temp/EFI/boot/BOOTX64.efi
	sudo umount temp/
	rmdir temp

run: kernel
	qemu-system-x86_64 -L OVMF_dir/ -bios /usr/share/ovmf/OVMF.fd -hda rockcandy.img
runarch: kernel
	qemu-system-x86_64 -L OVMF_dir/ -bios /usr/share/ovmf/x64/OVMF_CODE.fd -hda rockcandy.img -boot c,menu=on -net none

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(addprefix src/, $(OBJECTS)) rockcandy.efi rockcandy.img
