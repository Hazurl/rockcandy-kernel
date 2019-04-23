// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_BOOT_SERVICES_H
#define UEFI_BOOT_SERVICES_H

// EFI_TPL(Page 230)
typedef UINTN EFI_TPL;
#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

// RaiseTPL(Page 229)
typedef EFI_TPL (*EFI_RAISE_TPL) (EFI_TPL NewTpl);

// RestoreTPL(Page 230)
typedef VOID (*EFI_RESTORE_TPL) (EFI_TPL OldTpl);

// EFI_ALLOCATE_TYPE(Page 234)
typedef enum {
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress,
  MaxAllocateType
} EFI_ALLOCATE_TYPE;

// EFI_MEMORY_TYPE(Page 235)
typedef enum {
  EfiReservedMemoryType,
  EfiLoaderCode,
  EfiLoaderData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiConventionalMemory,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiPersistentMemory,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;

// AllocatePages(Page 234)
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES) (EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);

// FreePages(Page 236)
typedef EFI_STATUS (*EFI_FREE_PAGES) (EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);

// EFI_MEMORY_DESCRIPTOR(Page 238)
typedef struct {
  UINT32 Type;
  EFI_PHYSICAL_ADDRESS PhysicalStart;
  //EFI_VIRTUAL_ADDRESS VirtualStart;
  UINT64 NumberOfPages;
  UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;
#define EFI_MEMORY_UC 1 << 0
#define EFI_MEMORY_WC 1 << 1
#define EFI_MEMORY_WT 1 << 2
#define EFI_MEMORY_WB 1 << 3
#define EFI_MEMORY_UCE 1 << 4
#define EFI_MEMORY_WP 1 << 12
#define EFI_MEMORY_RP 1 << 13
#define EFI_MEMORY_XP 1 << 14
#define EFI_MEMORY_NV 1 << 15
#define EFI_MEMORY_MORE_RELIABLE 1 << 16
#define EFI_MEMORY_RO 1 << 17
#define EFI_MEMORY_SP 1 << 18
#define EFI_MEMORY_CPU_CRYPTO 1 << 19
#define EFI_MEMORY_RUNTIME 1 << 63

// GetMemoryMap(Page 237)
typedef EFI_STATUS (*EFI_GET_MEMORY_MAP) (UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, UINT32 DescriptorVersion);

// AllocatePool(Page 241)
typedef EFI_STATUS (*EFI_ALLOCATE_POOL) (EFI_MEMORY_TYPE PoolType, UINTN Size, VOID **Buffer);

// FreePool(Page 242)
typedef EFI_STATUS (*EFI_FREE_POOL) (VOID *Buffer);

// EFI_EVENT_NOTIFY(Page 219)
typedef VOID (*EFI_EVENT_NOTIFY) (EFI_EVENT Event, VOID *Context);

// CreateEvent(Page 217)
typedef EFI_STATUS (*EFI_CREATE_EVENT) (UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction /*Optional*/, VOID *NotifyContext /*Optional*/);

// EFI_TIMER_DELAY(Page 229)
typedef enum {
  TimerCancel,
  TimerPeriodic,
  TimerRelative
} EFI_TIMER_DELAY;

// SetTimer(Page 227)
typedef EFI_STATUS (*EFI_SET_TIMER) (EFI_EVENT Event, EFI_TIMER_DELAY Type, UINT64 TriggerTime);

// WaitForEvent(Page 225)
typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT) (UINTN NumberOfEvents, EFI_EVENT *Event, UINTN* Index);

// EFI_SIGNAL_EVENT
typedef EFI_STATUS (*EFI_SIGNAL_EVENT) (EFI_EVENT Event);

// CloseEvent(Page 224)
typedef EFI_STATUS (*EFI_CLOSE_EVENT) (EFI_EVENT Event);

// CheckEvent(Page 227)
typedef EFI_STATUS (*EFI_CHECK_EVENT) (EFI_EVENT Event);

// EFI_INTERFACE_TYPE(Page 249)
typedef enum {
	EFI_NATIVE_INTERFACE // Just this? Okay then.
} EFI_INTERFACE_TYPE;

// InstallProtocolInterface(Page 247)
typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE *Handle, EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType, VOID *Interface);

// ReinstallProtocolInterface(Page 251)
typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, EFI_GUID *Protocol, VOID *OldInterface, VOID *NewInterface);

// UninstallProtocolInterface(Page 250)
typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE) (EFI_HANDLE Handle, EFI_GUID *Protocol, VOID *Interface);

// HandleProtocol(Page 256)
typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protocol, VOID **Interface);

// RegisterProtocolNotify(Page 253)
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY) (EFI_GUID *Protocol, EFI_EVENT Event, VOID **Registration);

// EFI_LOCATE_SEARCH_TYPE(Page 255)
typedef enum {
  AllHandles,
  ByRegistryNotify,
  ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

// LocateHandle(Page 254)
typedef EFI_STATUS (*EFI_LOCATE_HANDLE) (EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol /*Optional*/, VOID *SearchKey /*Optional*/, UINTN *BufferSize, EFI_HANDLE *Buffer);

// EFI_DEVICE_PATH_PROTOCOL(Page 357)
typedef struct _EFI_DEVICE_PATH_PROTOCOL {
  UINT8 Type;
  UINT8 SubType;
  UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

// LocateDevicePath(Page 258)
typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH) (EFI_GUID *Protocol, EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);

// InstallConfigurationTable(Page 296)
typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE) (EFI_GUID *Guid, VOID *Table);

// LoadImage(Page 284)
typedef EFI_STATUS (*EFI_IMAGE_LOAD) (BOOLEAN BootPolicy, EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *SourceBuffer /*Optiaonal*/, UINTN SourceSize, EFI_HANDLE *ImageHandle);

// StartImage(Page 286)
typedef EFI_STATUS (*EFI_IMAGE_START) (EFI_HANDLE ImageHandle, UINTN *ExitDataSize, CHAR16 **ExitData /*Optional*/);

// Exit(Page 289)
typedef EFI_STATUS (*EFI_EXIT) (EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize, CHAR16 *ExitData /*Optional*/);

// UnloadImage(Page 287)
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD) (EFI_HANDLE ImageHandle);

// ExitBootServices(Page 291)
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES) (EFI_HANDLE ImageHandle, UINTN MapKey);

// GetNextMonatomicCount(Page 296)
typedef EFI_STATUS (*EFI_GET_NEXT_MONATOMIC_COUNT) (UINT64 *Count);

// Stall(Page 294)
typedef EFI_STATUS (*EFI_STALL) (UINTN Microseconds);

// SetWatchdogTimer(Page 293)
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER) (UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData /*Optional*/);

// ConnectController(Page 269)
typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle /*Optional*/, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath /*Optional*/, BOOLEAN Recursive);

// DisconnectController(Page 273)
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER) (EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle /*Optional*/, EFI_HANDLE ChildHandle /*Optional*/);

// OpenProtocol(Page 259)
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protcol, VOID **Interface /*Optional*/, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);

// CloseProtocol(Page 265)
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL) (EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);

// EFI_OPEN_PROTOCOL_INFORMATION_ENTRY(Page 268)
typedef struct {
  EFI_HANDLE AgentHandle;
  EFI_HANDLE ControllerHandle;
  UINT32 Attributes;
  UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

// OpenProtocolInformation(Page 267)
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION) (EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, UINTN *EntryCount);

// ProtocolsPerHandle(Page 275)
typedef EFI_STATUS (*EFI_PROTOCOL_PER_HANDLE) (EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtoclBufferCount);

// LocateHandleBuffer(Page 276)
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER) (EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol /*Optional*/, VOID *SearchKey /*Optional*/, UINTN *NoHandles, EFI_HANDLE **Buffer);

// LocateProtocol(Page 279)
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL) (EFI_GUID *Protcol, VOID *Registration /*Optional*/, VOID **Interface);

// InstallMultipleProtocolInterfaces(Page 280)
typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (EFI_HANDLE *Handle, ...);

// UninstallMultipleProtocolInterfaces(Page 281)
typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (EFI_HANDLE *Handle, ...);

// CalculateCrc32(Page 297)
typedef EFI_STATUS (*EFI_CALCULATE_CRC32) (VOID *Data, UINTN DataSize, UINT32 *Crc32);

// CopyMem(Page 294)
typedef EFI_STATUS (*EFI_COPY_MEM) (VOID *Destination, VOID *Source, UINTN Length);

// SetMem(Page 295)
typedef EFI_STATUS (*EFI_SET_MEM) (VOID *Buffer, UINTN Size, UINT8 Value);

// EFI_BOOT_SERVICES(Page 166)
typedef struct {
	EFI_TABLE_HEADER Hdr;

	EFI_RAISE_TPL RaiseTPL;
	EFI_RESTORE_TPL RestoreTPL;

	EFI_ALLOCATE_PAGES AllocatePages;
	EFI_FREE_PAGES FreePages;
	EFI_GET_MEMORY_MAP GetMemoryMap;
	EFI_ALLOCATE_POOL AllocatePool;
	EFI_FREE_POOL FreePool;

	EFI_CREATE_EVENT CreateEvent;
	EFI_SET_TIMER SetTimer;
	EFI_WAIT_FOR_EVENT WaitForEvent;
	EFI_SIGNAL_EVENT CloseEvent;
	EFI_CHECK_EVENT CheckEvent;

	EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL HandleProtocol;
	VOID* Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
	EFI_LOCATE_HANDLE LocateHandle;
	EFI_LOCATE_DEVICE_PATH LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	EFI_IMAGE_LOAD LoadImage;
	EFI_IMAGE_START StartImage;
	EFI_EXIT Exit;
	EFI_IMAGE_UNLOAD UnloadImage;
	EFI_EXIT_BOOT_SERVICES ExitBootServices;

	EFI_GET_NEXT_MONATOMIC_COUNT GetNextMonatomicCount;
	EFI_STALL Stall;
	EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

	EFI_CONNECT_CONTROLLER ConnectController;
	EFI_DISCONNECT_CONTROLLER DisconnectController;

	EFI_OPEN_PROTOCOL OpenProtocol;
	EFI_CLOSE_PROTOCOL CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

	EFI_PROTOCOL_PER_HANDLE ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	EFI_CALCULATE_CRC32 CalculateCrc32;

	EFI_COPY_MEM CopyMem;
	EFI_SET_MEM SetMem;
} EFI_BOOT_SERVICES;

#endif
