#include <elf.h>
#include <uefi.h>

void test_blt(EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL red = { 0, 0, 255 , 0 };
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL pixels[100];

	for (int idx = 0; idx < 100 * 100; idx++)
		pixels[0] = red;
	graphics->Blt(graphics, pixels, EfiBltVideoFill, 0, 0, 0, 0, 10, 10, 0);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut = SystemTable->ConOut;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* file_system = 0;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* graphics = 0;
	EFI_FILE_PROTOCOL* file_protocol = 0;
	EFI_GUID file_system_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_GUID graphics_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	ConOut->OutputString(ConOut, u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));



	if(SystemTable->BootServices->LocateProtocol(&graphics_guid, 0, (void**)&graphics) == EFI_SUCCESS) {
		ConOut->OutputString(ConOut, u"Got EFI_GRAPHICS_OUTPUT_PROTOCOL!\r\n");
	} else {
		kprint(u"Nothin' worked\r\n");
	}

	test_blt(graphics);

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
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(12, 0));
		ConOut->OutputString(ConOut, u"An unexpected error occured\r\n");
		ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	}
	while(1) {}
	return EFI_SUCCESS;
}
