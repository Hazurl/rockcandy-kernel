// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>
#include <uefi/SimpleTextInput.h>
#include <uefi/SimpleTextOutput.h>
#include <uefi/RuntimeServices.h>
#include <uefi/BootServices.h>

#ifndef UEFI_SYSTEM_TABLE_H
#define UEFI_SYSTEM_TABLE_H

// EFI_RUNTIME_SERVICES (Page 171)
typedef struct {
	EFI_TABLE_HEADER Hdr;

	//EFI_GET_TIME GetTime; // Prototype missing from docs?
	//EFI_SET_TIME SetTime;
	//EFI_GET_WAKEUP_TIME GetWakeupTime;
	//EFI_SET_WAKEUP_TIME SetWakeupTime;

	//EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
	//EFI_CONVERT_POINTER ConvertPointer;

	//EFI_GET_VARIABLE GetVariable;
	//EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
	//EFI_SET_VARIABLE SetVariable;

	//EFI_GET_NECT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
	//EFI_RESET_SYSTEM ResetSystem;

	//EFI_UPDATE_CAPSULE UpdateCapsule;
	//EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

	//EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

// EFI_BOOT_SERVICES(Page 166)
typedef struct {
	EFI_TABLE_HEADER Hdr;

	EFI_RAISE_TPL RaiseTPL;
	EFI_RESTORE_TPL RestoreTPL;

	EFI_ALLOCATE_PAGES AllocatePages;
	EFI_FREE_PAGES FreePages;
	EFI_GET_MEMORY_MAP GetMemoryMap;
	//EFI_ALLOCATE_POOL AllocatePool;
	//EFI_FREE_POOL FreePool;

	//EFI_CREATE_EVENT CreateEvent;
	//EFI_SET_TIMER SetTimer;
	//EFI_WAIT_FOR_EVENT WaitForEvent;
	//EFI_SIGNAL_EVENT CloseEvent;
	//EFI_CHECK_EVENT CheckEvent;

	//EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
	//EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	//EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	//EFI_HANDLE_PROTOCOL HandleProtocol;
	VOID* Reserved;
	//EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
	//EFI_LOCATE_HANDLE LocateHandle;
	//EFI_LOCATE_DEVICE_PATH LocateDevicePath;
	//EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	//EFI_IMAGE_LOAD LoadImage;
	//EFI_IMAGE_START StartImage;
	//EFI_EXIT Exit;
	//EFI_IMAGE_UNLOAD UnloadImage;
	//EFI_EXIT_BOOT_SERVICES ExitBootServices;

	//EFI_GET_NEXT_MONATOMIC_COUNT GetNextMonatomicCount;
	//EFI_STALL Stall;
	//EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

	//EFI_CONNECT_CONTROLLER ConnectController;
	//EFI_DISCONNECT_CONTROLLER DisconnectController;

	//EFI_OPEN_PROTOCOL OpenProtocol;
	//EFI_CLOSE_PROTOCOL CloseProtocol;
	//EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

	//EFI_PROTOCOL_PER_HANDLE ProtocolsPerHandle;
	//EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
	//EFI_LOCATE_PROTOCOL LocateProtocol;
	//EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	//EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	//EFI_CALCULATE_CRC32 CalculateCrc32;

	//EFI_COPY_MEM CopyMem;
	//EFI_SET_MEM SetMem;
} EFI_BOOT_SERVICES;

// EFI_CONFIGURATION_TABLE(Page 173)
typedef struct {
	EFI_GUID VendorGuid;
	VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;

// EFI_SYSTEM_TABLE(Page 165)
typedef struct {
	EFI_TABLE_HEADER Hdr;
	CHAR16 *FirmwareVendor;
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_HANDLE StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_BOOT_SERVICES *BootServices;
	UINTN NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
