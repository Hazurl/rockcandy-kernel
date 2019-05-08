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
	ConOut->OutputString(ConOut, (CHAR16 *)str);
}

void setattr(u8 attr) {
	ConOut->SetAttribute(ConOut, attr);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	EFI_GUID FileInfoGUID = EFI_FILE_INFO_GUID;
	UINTN FileInfoSize = sizeof(EFI_FILE_INFO);
	EFI_FILE_PROTOCOL *FileProtocol = 0;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = 0;
	EFI_GUID FileSystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_PHYSICAL_ADDRESS ShellBuffer;
	u64 (*ShellEntry)(ROCKCANDY_LIBRARY*);
	Elf64_Ehdr *ShellHeader;
	EFI_FILE_INFO *ShellInfo = 0;
	EFI_FILE_PROTOCOL *ShellProtocol;
	ROCKCANDY_LIBRARY SystemLibrary;
	ConIn = SystemTable->ConIn;
	ConOut = SystemTable->ConOut;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	ConOut->OutputString(ConOut, u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	if(SystemTable->BootServices->LocateProtocol(&FileSystemGUID, 0, (void**)&FileSystem) == EFI_SUCCESS) {
		if(FileSystem->OpenVolume(FileSystem, &FileProtocol) == EFI_SUCCESS) {
			if(FileProtocol->Open(FileProtocol, &ShellProtocol, u"shell.elf", EFI_FILE_MODE_READ, EFI_FILE_SYSTEM) == EFI_SUCCESS) {
				if(ShellProtocol->GetInfo(ShellProtocol, &FileInfoGUID, &FileInfoSize, (VOID *)ShellInfo) == EFI_SUCCESS) {
					if(SystemTable->BootServices->AllocatePages(AllocateAddress, EfiConventionalMemory, (ShellInfo->FileSize / 4096) + 1, &ShellBuffer) == EFI_SUCCESS) {
						if(ShellProtocol->Read(ShellProtocol, &ShellInfo->FileSize, (VOID *)ShellBuffer) == EFI_SUCCESS) {
							ShellHeader = (Elf64_Ehdr *)ShellBuffer;
							if(ShellHeader->e_ident[0] == 0x7F && ShellHeader->e_ident[1] == 'E' && ShellHeader->e_ident[2] == 'L' && ShellHeader->e_ident[3] == 'F') {
								if(ShellHeader->e_ident_osabi == ELFOSABI_ROCKCANDY && ShellHeader->e_ident_class == ELFCLASS64 && ShellHeader->e_type == ET_EXEC) {
									ShellEntry = (u64 (*)(ROCKCANDY_LIBRARY*))ShellHeader->e_entry;
									SystemLibrary.clear = &clear;
									SystemLibrary.getc = &getc;
									SystemLibrary.puts = &puts;
									SystemLibrary.setattr = &setattr;
									if(!ShellEntry(&SystemLibrary)) {
										ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
										ConOut->OutputString(ConOut, u"An unexpected error occured!\r\n");
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
					ConOut->OutputString(ConOut, u"Unable to find shell metadata!\r\n");
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
	while(1) {}
	return EFI_SUCCESS;
}
