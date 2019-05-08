#include <elf.h>
#include <uefi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	(void)ImageHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut = SystemTable->ConOut;
	EFI_GUID FileInfoGUID = EFI_FILE_INFO_GUID;
	UINTN FileInfoSize = sizeof(EFI_FILE_INFO);
	EFI_FILE_PROTOCOL *FileProtocol = 0;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = 0;
	EFI_GUID FileSystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_PHYSICAL_ADDRESS ShellBuffer;
	EFI_FILE_INFO *ShellInfo;
	EFI_FILE_PROTOCOL *ShellProtocol;
	ConOut->ClearScreen(ConOut);
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(13, 0));
	ConOut->OutputString(ConOut, u"Welcome to Rockcandy!\r\n");
	ConOut->SetAttribute(ConOut, EFI_TEXT_ATTR(15, 0));
	if(SystemTable->BootServices->LocateProtocol(&FileSystemGUID, 0, (void**)&FileSystem) == EFI_SUCCESS) {
		if(FileSystem->OpenVolume(FileSystem, &FileProtocol) == EFI_SUCCESS) {
			if(FileProtocol->Open(FileProtocol, &ShellHandle, u"shell.elf", EFI_FILE_MODE_READ, EFI_FILE_SYSTEM) == EFI_SUCCESS) {
				if(ShellProtocol->GetInfo(ShellProtocol, &FileInfoGUID, &FileInfoSize, ShellInfo) == EFI_SUCCESS) {
					if(SystemTable->BootServices->AllocatePages(AllocateAddress, EfiConventionalMemory, (ShellInfo->FileSize / 4096) + 1, &ShellBuffer) == EFI_SUCCESS) {
						if(ShellProtocol->Read(ShellProtocol, &ShellInfo->FileSize, ShellBuffer) == EFI_SUCCESS) {
							// TODO: Launch the shell
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
