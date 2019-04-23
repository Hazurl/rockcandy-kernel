#include <uefi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut = SystemTable->ConOut;
	ConOut->OutputString(ConOut, U"Welcome to Rockcandy!");
}
