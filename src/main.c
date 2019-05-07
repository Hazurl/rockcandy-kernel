#include <elf.h>
#include <uefi.h>

extern void panic();

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

void kprint(CHAR16 *str) {
	ConOut->OutputString(ConOut, str);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	VOID *fs;
	ConOut = SystemTable->ConOut;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	kprint(u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	if(SystemTable->BootServices->LocateProtocol((EFI_GUID*)&EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, 0, &fs) == EFI_SUCCESS) {
		//
	} else {
		panic();
	}
	panic();
	while(1) {}
	return EFI_SUCCESS;
}
