#include <elf.h>
#include <fixed.h>
#include <uefi.h>

typedef struct {
	void (*clear)();
	u16 (*getc)();
	void (*puts)(u16 *);
	void (*setattr)(u8 attr);
} ROCKCANDY_LIBRARY;

EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

void clear() {
	ConOut->ClearScreen(ConOut);
}

u16 getc() {
	EFI_INPUT_KEY key;
	if(ConIn->ReadKeyStroke(ConIn, &key) == EFI_SUCCESS) {
		return (u16)key.UnicodeChar;
	}
	return 0;
}

void puts(u16 *str) {
	ConOut->OutputString(ConOut, u"Call puts!\r\n");
	ConOut->OutputString(ConOut, (CHAR16 *)str);
}

void setattr(u8 attr) {
	ConOut->SetAttribute(ConOut, attr);
}

u16 digit_to_hex(u8 digit) {
	digit &= 0xF;
	return digit >= 10 ? 'A' + (digit - 10) : digit + '0';
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	ConIn = SystemTable->ConIn;
	ConOut = SystemTable->ConOut;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	ConOut->OutputString(ConOut, u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	EFI_GUID FileInfoGUID = EFI_FILE_INFO_GUID;
	EFI_PHYSICAL_ADDRESS ShellInfoAddr;
	EFI_FILE_INFO* ShellInfo = 0;
	UINTN FileInfoSize = (4 * 4096) / sizeof(EFI_FILE_INFO);
	EFI_STATUS error;
	{
		u16 str[] = u"____ is the size of the buffer\r\n";
		str[0] = ((FileInfoSize / 1000) % 10) + '0';
		str[1] = ((FileInfoSize / 100) % 10) + '0';
		str[2] = ((FileInfoSize / 10) % 10) + '0';
		str[3] = (FileInfoSize % 10) + '0';
		ConOut->OutputString(ConOut, str);

	}
	if((error = SystemTable->BootServices->AllocatePages(AllocateAnyPages, EfiLoaderData, 4, &ShellInfoAddr)) != EFI_SUCCESS) {
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		u16 str[] = u"____: An unexpected error occured!!!\r\n";
		str[0] = (((error & ~(EFI_HIGH_BIT)) / 1000) % 10) + '0';
		str[1] = (((error & ~(EFI_HIGH_BIT)) / 100) % 10) + '0';
		str[2] = (((error & ~(EFI_HIGH_BIT)) / 10) % 10) + '0';
		str[3] = ((error & ~(EFI_HIGH_BIT)) % 10) + '0';
		ConOut->OutputString(ConOut, str);
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
		while(1);
	}
	ShellInfo = (EFI_FILE_INFO*)ShellInfoAddr;
	EFI_FILE_PROTOCOL *FileProtocol = 0;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = 0;
	EFI_GUID FileSystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_PHYSICAL_ADDRESS ShellBuffer;
	u64 (*ShellEntry)(ROCKCANDY_LIBRARY*);
	Elf64_Ehdr *ShellHeader;
	EFI_FILE_PROTOCOL *ShellProtocol;
	ROCKCANDY_LIBRARY SystemLibrary;
	if(SystemTable->BootServices->LocateProtocol(&FileSystemGUID, 0, (void**)&FileSystem) == EFI_SUCCESS) {
		if(FileSystem->OpenVolume(FileSystem, &FileProtocol) == EFI_SUCCESS) {
			if(FileProtocol->Open(FileProtocol, &ShellProtocol, u"shell.elf", EFI_FILE_MODE_READ, EFI_FILE_SYSTEM) == EFI_SUCCESS) {
				if((error = ShellProtocol->GetInfo(ShellProtocol, &FileInfoGUID, &FileInfoSize, ShellInfo)) == EFI_SUCCESS) {
					if(SystemTable->BootServices->AllocatePages(AllocateAnyPages, EfiLoaderData, (ShellInfo[0].FileSize / 4096) + 1, &ShellBuffer) == EFI_SUCCESS) {
						if(ShellProtocol->Read(ShellProtocol, &ShellInfo[0].FileSize, (VOID *)ShellBuffer) == EFI_SUCCESS) {
							ShellHeader = (Elf64_Ehdr *)ShellBuffer;
							if(ShellHeader->e_ident[0] == 0x7F && ShellHeader->e_ident[1] == 'E' && ShellHeader->e_ident[2] == 'L' && ShellHeader->e_ident[3] == 'F') {

								{
									u16 str[] = u"0x______, ABI: __, TYPE: __\r\n";
									Elf64_Phdr* ProgramHeaderTable = (Elf64_Phdr*)(ShellBuffer + ShellHeader->e_phoff);
									str[7] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr));
									str[6] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr) >> 4);
									str[5] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr) >> 8);
									str[4] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr) >> 12);
									str[3] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr) >> 16);
									str[2] = digit_to_hex((ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr) >> 20);

									str[16] = digit_to_hex(ShellHeader->e_ident_osabi);
									str[15] = digit_to_hex(ShellHeader->e_ident_osabi>>4);

									str[26] = digit_to_hex(ShellHeader->e_type);
									str[25] = digit_to_hex(ShellHeader->e_type>>4);
									ConOut->OutputString(ConOut, str);
								}

								if(ShellHeader->e_ident_osabi == ELFOSABI_ROCKCANDY && ShellHeader->e_ident_class == ELFCLASS64 && ShellHeader->e_type == ET_EXEC) {
									Elf64_Phdr* ProgramHeaderTable = (Elf64_Phdr*)(ShellBuffer + ShellHeader->e_phoff);

									ShellEntry = (u64 (*)(ROCKCANDY_LIBRARY*))(ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr);
									SystemLibrary.clear = &clear;
									SystemLibrary.getc = &getc;
									SystemLibrary.puts = &puts;
									SystemLibrary.setattr = &setattr;

									SystemLibrary.puts(u"Launching Shell\r\n");
									if(!ShellEntry(&SystemLibrary)) {
										ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
										ConOut->OutputString(ConOut, u"An unexpected error occured!\r\n");
										ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
									} else {
										ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
										ConOut->OutputString(ConOut, u"Worked!\r\n");
										ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
									}
								} else {
									ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
									ConOut->OutputString(ConOut, u"Invalid ELF binary!\r\n");
									ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
								}
							} else {
								ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
								ConOut->OutputString(ConOut, u"Unable to find the ELF signature!\r\n");
								ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
							}
						} else {
							ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
							ConOut->OutputString(ConOut, u"Unable to read the shell!\r\n");
							ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
						}
					} else {
						ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
						ConOut->OutputString(ConOut, u"Unable to reserve enough memory for the shell!\r\n");
						ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
					}
				} else {
					ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
					u16 str[] = u"Unable to find shell metadata! (__, _____)\r\n";
					str[32] = (((error & ~(EFI_HIGH_BIT)) / 10) % 10) + '0';
					str[33] = ((error & ~(EFI_HIGH_BIT)) % 10) + '0';
					str[36] = ((FileInfoSize / 10000) % 10) + '0';
					str[37] = ((FileInfoSize / 1000) % 10) + '0';
					str[38] = ((FileInfoSize / 100) % 10) + '0';
					str[39] = ((FileInfoSize / 10) % 10) + '0';
					str[40] = (FileInfoSize % 10) + '0';
					ConOut->OutputString(ConOut, str);
					ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
				}
			} else {
				ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
				ConOut->OutputString(ConOut, u"Unable to find the shell!\r\n");
				ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
			}
		} else {
			ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
			ConOut->OutputString(ConOut, u"Unable to open the boot volume!\r\n");
			ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
		}
	} else {
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		ConOut->OutputString(ConOut, u"Unable to find the file system protocol!\r\n");
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	}
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
	ConOut->OutputString(ConOut, u"Exit...\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	while(1) {}
	return EFI_SUCCESS;
}
