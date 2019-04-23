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
typedef EFI_TPL (VOID *EFI_RAISE_TPL) (EFI_TPL NewTpl);

// RestoreTPL(Page 230)
typedef VOID (VOID *EFI_RESTORE_TPL) (EFI_TPL OldTpl);

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
typedef EFI_STATUS (VOID *EFI_ALLOCATE_PAGES) (EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);

// FreePages(Page 236)
typedef EFI_STATUS (VOID *EFI_FREE_PAGES) (EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);

// EFI_MEMORY_DESCRIPTOR(Page 238)
typedef struct {
  UINT32 Type;
  EFI_PHYSICAL_ADDRESS PhysicalStart;
  EFI_VIRTUAL_ADDRESS VirtualStart;
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
typedef EFI_STATUS (VOID *EFI_GET_MEMORY_MAP) (UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, UINT32 DescriptorVersion);

// AllocatePool?

// FreePool?

// CreateEvent?

// SetTimer?

// WaitForEvent?

// CloseEvent?

// CheckEvent?

// InstallProtocolInterface?

// ReinstallProtocolInterface?

// UninstallProtocolInterface?

// HandleProtocol?

// RegisterProtocolNotify?

// LocateHandle?

// LocateDevicePath?

// InstallConfigurationTable?

// LoadImage?

// StartImage?

// Exit?

// UnloadImage?

// ExitBootServices?

// GetNextMonatomicCount?

// Stall?

// SetWatchdogTimer?

// ConnectController?

// DisconnectController?

// OpenProtocol?

// CloseProtocol?

// OpenProtocolInformation?

// ProtocolsPerHandle?

// LocateHandleBuffer?

// LocateProtocol?

// InstallMultipleProtocolInterfaces?

// UninstallMultipleProtocolInterfaces?

// CalculateCrc32?

// CopyMem?

// SetMem?

#endif
