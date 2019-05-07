#include <elf.h>
#include <uefi.h>

extern void panic();

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

void kprint(CHAR16 *str) {
	ConOut->OutputString(ConOut, str);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* file_system = 0;
	EFI_FILE_PROTOCOL* file_protocol = 0;
	EFI_GUID file_system_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	ConOut = SystemTable->ConOut;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	kprint(u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	
	if(SystemTable->BootServices->LocateProtocol(&file_system_guid, 0, (void**)&file_system) == EFI_SUCCESS) {
		ConOut->OutputString(ConOut, u"Got EFI_SIMPLE_FILE_SYSTEM_PROTOCOL!\r\n");
		if (file_system->OpenVolume(file_system, &file_protocol) == EFI_SUCCESS) {
			ConOut->OutputString(ConOut, u"Got EFI_FILE_PROTOCOL!\r\n");
		} else {
			ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
			ConOut->OutputString(ConOut, u"An unexpected error occured\r\n");
			ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
		}

	} else {
		panic();
	}
	while(1) {}
	return EFI_SUCCESS;
}
