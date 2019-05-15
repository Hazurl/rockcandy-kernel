#include <elf.h>
#include <fixed.h>
#include <uefi.h>
#include <kernel.h>

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

void libputs(u16 *str) {
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

EFI_STATUS kernel_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);

#define EFI_CHECK_ALL

EFI_STATUS EFI_CHECK_LOG(u16* msg, EFI_STATUS status) {
	if (EFI_ERROR(status)) {
		
		u16* message = EFI_GET_STATUS_MESSAGE(status);
		WITH_STD_OUT {
			puts(msg);
			puts(u"[E#");
			putul(status & ~EFI_HIGH_BIT);
			puts(u"] ");
			puts(message);
			puts(u"\r\n");
		}

	}
#ifdef EFI_CHECK_ALL
	else {
		u16* message = EFI_GET_STATUS_MESSAGE(status);
		WITH_STD_OUT {
			puts(msg);
			puts(status ? u"[W#" : u"[#");
			putul(status);
			puts(u"] ");
			puts(message);
			puts(u"\r\n");
		}
	}
#endif

	return status;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	ConIn = SystemTable->ConIn;
	ConOut = SystemTable->ConOut;

	initStdOut(ConOut);

	WITH_STD_OUT {
		ConOut->ClearScreen(ConOut);
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
		puts(u"Welcome to Rockcandy!\r\n");
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	}

	EFI_STATUS ret = kernel_main(ImageHandle, SystemTable);

	(void)ret;

	WITH_STD_OUT {
		puts(u"\r\n");
	}

	EFI_CHECK_LOG(u"Exit with ", ret);

	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
	ConOut->OutputString(ConOut, u"Exit...\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));

	while(1);
}

EFI_STATUS EFI_CHECK(EFI_STATUS status) {
	return EFI_CHECK_LOG(u"", status);
}

EFI_STATUS get_filesystem_protocol(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL **FileProtocol) {
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = 0;
	EFI_GUID FileSystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	EFI_STATUS status = EFI_SUCCESS;

	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Locate filesystem protocol: ", SystemTable->BootServices->LocateProtocol(&FileSystemGUID, 0, (void**)&FileSystem) ))) {
		return status;
	}

	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Open filesystem volume: ", FileSystem->OpenVolume(FileSystem, FileProtocol) ))) {
		return status;
	}

	return status;
}

EFI_STATUS read_file(EFI_SYSTEM_TABLE *SystemTable, EFI_FILE_PROTOCOL *FileProtocol, EFI_PHYSICAL_ADDRESS* Buffer) {
	EFI_FILE_PROTOCOL *File;
	EFI_GUID FileInfoGUID = EFI_FILE_INFO_GUID;
	EFI_FILE_INFO* Informations = 0;

	UINTN FileInfoSize = 0;

	EFI_STATUS status = EFI_SUCCESS;

	// Open file protocol in read mode
	// File is being written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Open shell.elf: ", FileProtocol->Open(FileProtocol, &File, u"shell.elf", EFI_FILE_MODE_READ, 0) ))) {
		return status;
	}

	// Get file informations count
	// FileInfoSize is being written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Get files information count: ", File->GetInfo(File, &FileInfoGUID, &FileInfoSize, 0) ))) {
		if (status == EFI_BUFFER_TOO_SMALL) {
			status = EFI_SUCCESS;
		}
		else {
			return status;
		}
	}

	WITH_STD_OUT {
		puts(u"FileInfoSize: ");
		putul(FileInfoSize);
		puts(u", FileInfo count: ");
		putul(FileInfoSize / sizeof(EFI_FILE_INFO));
		puts(u"\r\n");
	}


	// Allocate enough memory to holds the file's informations
	// Informations is beging written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Allocate pages for file's informations: ", SystemTable->BootServices->AllocatePages(AllocateAnyPages, EfiLoaderData, 1 + (FileInfoSize / 4096ull), (EFI_PHYSICAL_ADDRESS*)&Informations) ))) {
		return status;
	}

	WITH_STD_OUT {
		puts(u"FileInfoSize: ");
		putul(FileInfoSize);
		puts(u"\r\n");
	}

	// Request file's informations
	// Informations is being written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Get file's informations: ", File->GetInfo(File, &FileInfoGUID, &FileInfoSize, Informations) ))) {
		return status;
	}

	// Allocate enough memory to holds file's content
	// Buffer is being written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Allocates pages for file's content: ", SystemTable->BootServices->AllocatePages(AllocateAnyPages, EfiLoaderData, (Informations[0].FileSize / 4096) + 1, Buffer) ))) {
		return status;
	}

	// Read file's content
	// Buffer is being written to
	if (EFI_ERROR(status = EFI_CHECK_LOG(u"Read file: ", File->Read(File, &Informations[0].FileSize, (VOID *)*Buffer) ))) {
		return status;
	}
	
	return status;
}

EFI_STATUS kernel_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	(void)SystemTable;

	u64 (*ShellEntry)(ROCKCANDY_LIBRARY*);
	Elf64_Ehdr *ShellHeader;
	ROCKCANDY_LIBRARY SystemLibrary;


	EFI_FILE_PROTOCOL *FileProtocol;

	if (EFI_ERROR(EFI_CHECK_LOG(u"Get filesystem protocol: ", get_filesystem_protocol(SystemTable, &FileProtocol) ))) {
		return EFI_HIGH_BIT;
	}

	EFI_PHYSICAL_ADDRESS ShellBuffer;

	if (EFI_ERROR(EFI_CHECK_LOG(u"Read shell.elf: ", read_file(SystemTable, FileProtocol, &ShellBuffer) ))) {
		return EFI_HIGH_BIT;
	}

	ShellHeader = (Elf64_Ehdr *)ShellBuffer;
	if(ShellHeader->e_ident[0] != 0x7F || ShellHeader->e_ident[1] != 'E' || ShellHeader->e_ident[2] != 'L' || ShellHeader->e_ident[3] != 'F') {
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		WITH_STD_OUT {
			puts(u"Unable to find the ELF signature!\r\n");
		}
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
		return EFI_HIGH_BIT;
	}

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

	if(ShellHeader->e_ident_osabi != ELFOSABI_ROCKCANDY || ShellHeader->e_ident_class != ELFCLASS64 || ShellHeader->e_type != ET_EXEC) {
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		ConOut->OutputString(ConOut, u"Invalid ELF binary!\r\n");
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
		return EFI_HIGH_BIT;
	}

	Elf64_Phdr* ProgramHeaderTable = (Elf64_Phdr*)(ShellBuffer + ShellHeader->e_phoff);

	ShellEntry = (u64 (*)(ROCKCANDY_LIBRARY*))(ShellHeader->e_entry + ShellBuffer + ProgramHeaderTable->p_vaddr);
	SystemLibrary.clear = &clear;
	SystemLibrary.getc = &getc;
	SystemLibrary.puts = &libputs;
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

	return EFI_SUCCESS;
}
