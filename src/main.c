#include <elf.h>
#include <uefi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut = SystemTable->ConOut;
	VOID *fs;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	ConOut->OutputString(ConOut, u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	if(SystemTable->BootServices->LocateProtocol((EFI_GUID*)&EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, 0, &fs) == EFI_SUCCESS) {
		//
	} else {
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		ConOut->OutputString(ConOut, u"An unexpected error occured\r\n");
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	}
	while(1) {}
	return EFI_SUCCESS;
}
