# ######################################################### #
#     ____             __                        __         #
#    / __ \____  _____/ /___________ _____  ____/ /_  __    #
#   / /_/ / __ \/ ___/ //_/ ___/ __ `/ __ \/ __  / / / /    #
#  / _, _/ /_/ / /__/ ,< / /__/ /_/ / / / / /_/ / /_/ /     #
# /_/ |_|\____/\___/_/|_|\___/\__,_/_/ /_/\__,_/\__, /      #
#                                              /____/       #
#                       - Kernel -                          #
# ######################################################### #
#
# ####################
# # Variable section #
# ####################
#
INCLUDE_DIR=./include
SOURCE_DIR=./src
OBJECT_DIR=./.obj
TEMP_DIR=./temp
IMG_DIR=./files
SILENT=NO
#
TARGET_DIR=.
TRGT_EFI=$(TARGET_DIR)/rockcandy.efi
TRGT_IMG=$(TARGET_DIR)/rockcandy.img
#
#
#
# The objects we will want to build
OBJECT_NAMES=	\
				main \
				elf \
#
#
# ##################
# # Meta-variables #
# ##################
#
S=@
D=@
#
#
# ######################
# # Auto-gen variables #
# ######################
#
OBJECTS=$(patsubst %, $(OBJECT_DIR)/%.o, $(OBJECT_NAMES))
SOURCES=$(patsubst %, $(SOURCE_DIR)/%.c, $(OBJECT_NAMES))
#
# #####################
# # Compiler settings #
# #####################
#
# Warning flags to keep us sane
#
WFLAGS=-Werror -Wextra -Wall
#
# Includes
IFLAGS=-I$(INCLUDE_DIR)
#
# Leave empty, pass to `make`
EXTRA=
#
#		-ffreestanding - Don't rely on system
#		Also supply the warning flags,
#       include flags and user provided flags
CFLAGS= \
		-ffreestanding \
		-std=c17 \
		$(WFLAGS) \
		$(IFLAGS) \
		$(EXTRA) \

#
# 			Flags for linking
#			-nostdlib          - Don't use the standard library
#			-Wl,-dll           - Compile as a dll
#			-shared            - Make it a shared library
#			-Wl,--subsystem,10 - Use Subsystem 10 (UEFI)
#			-e efi-main        - Set the entry point to `efi_main`

LDFLAGS=	\
			-nostdlib \
			-Wl,-dll \
			-shared \
			-Wl,--subsystem,10 \
			-e efi_main \
#
AC=x86_64-w64-mingw32-as
CC=x86_64-w64-mingw32-gcc
LD=x86_64-w64-mingw32-gcc
QEMU=qemu-system-x86_64
#
#
# ############
# # Building #
# ############
#
all: $(TRGT_EFI)
$(TRGT_EFI): $(OBJECTS)
	$D echo "[+] Linking $(TRGT_EFI)"
	$S $(LD) $(LDFLAGS) -o $(TRGT_EFI) $^
	$D echo "[+] Building system image"
	$S dd if=/dev/zero of=$(TRGT_IMG) bs=1048576 count=64 status=none
	$S /sbin/mkfs.fat -F 32 -n ROCKCANDY $(TRGT_IMG) >/dev/null
	$S mkdir $(TEMP_DIR)
	$S sudo mount -t vfat $(TRGT_IMG) $(TEMP_DIR)
	$S sudo mkdir -p $(TEMP_DIR)/EFI/boot/
	$S sudo cp -r $(wildcard $(IMG_DIR)/*) $(TRGT_EFI) $(TEMP_DIR)/EFI/boot/BOOTX64.efi
	$S sudo umount $(TEMP_DIR)
	$S rmdir $(TEMP_DIR)
	$D echo "[*] Enjoy!"

#
# rules on how to build C11 files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	$D echo "[+] Making object $@"
	$S @mkdir -p $(OBJECT_DIR)
	$S $(CC) $(CFLAGS) -c -o $@ $<
#
# rules on how to build ASSEMBLY files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.s
	$D echo "[+] Making object $@"
	$S @mkdir -p $(OBJECT_DIR)
	$S $(AC) -c -o $@ $<
#
#
#
# ###########
# # Cleanup #
# ###########
#
# Clean all of our object files
clean:
	$D echo "[-] Removing $(strip $(OBJECTS))"
	$S $(RM) $(OBJECTS)
	$D echo "[-] Removing $(strip $(OBJECT_DIR))"
	$S $(RM) -r $(OBJECT_DIR)
#
# Full clean, clean everything, including our images
#
fclean: clean
	$D echo "[-] Removing $(strip $(TRGT_EFI)), $(strip $(TRGT_IMG)) and $(TEMP_DIR)"
	$S $(RM) $(TRGT_EFI) $(TRGT_IMG)
	$S if [ -d "$(TEMP_DIR)" ]; then sudo umount $(TEMP_DIR); $(RM) -r $(TEMP_DIR); fi

#
# Recompile fully
# NOTE: This can be useful when a header file has changed
re:
	$S $(MAKE) -sB $(EXTRA)
#
#
# ##########
# # Macros #
# ##########
#
# For now, we'll have multiple macros for running
# hopefully we'll change this later.
#
# The directory where it's located on Pop_OS! it would be nice
# to get this directory from some user configuration.
USR_OVMF_DIR_POP=/usr/share/OVMF/OVMF_CODE.fd
#
#
run:
	$S $(QEMU) -L OVMF_dir/ -bios /usr/share/qemu/ovmf-x86_64.bin -hda $(TRGT_IMG)
#
runarch:
	$S $(QEMU) -L OVMF_dir/ -bios /usr/share/ovmf/x64/OVMF_CODE.fd -hda $(TRGT_IMG) -boot c,menu=on -net none
#
runpop:
	$S $(QEMU) -L OVMF_dir/ -bios $(USR_OVMF_DIR_POP) -hda $(TRGT_IMG) -boot c,menu=on -net none
#
# Recompile: ignoring advanced warnings
simple:
	$S $(MAKE) -sB WFLAGS=
# Recompile: ignoring all warnings
nowarn:
	$S $(MAKE) -sB WFLAGS=-w
# Recompile: printing out all commands ran
verbose: fclean
	make WFLAGS=-w S= D=@#
