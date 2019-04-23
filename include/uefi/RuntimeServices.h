// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_RUNTIME_SERVICES_H
#define UEFI_RUNTIME_SERVICES_H

// EFI_TIME(Page 325)

typedef struct {
	UINT16 Year;
	UINT8 Month;
	UINT8 Day;
	UINT8 Hour;
	UINT8 Minute;
	UINT8 Second;
	UINT8 Pad1;
	UINT32 Nanosecond;
	INT16 TimeZone;
	UINT8 Daylight;
	UINT8 Pad2;
} EFI_TIME;

// GetTime?

// EFI_SET_TIME(Page 327)
typedef EFI_STATUS SetTime(EFI_TIME *Time);

// EFI_GET_WAKEUP_TIME(Page 328)
typedef EFI_STATUS GetWakeupTime(typedef EFI_STATUS GetWakeupTime(BOOLEAN *Enabled, BOOLEAN *Pending, EFI_TIME *Time);

// EFI_SET_WAKEUP_TIME(Page 329)
typedef EFI_STATUS SetWakeupTime(BOOLEAN Enable, EFI_TIME *Time); // Multiple argument signatures not supported?
typedef EFI_STATUS SetWakeupTime(BOOLEAN Enable);

// SetVirtualAddressMap (Page 331)
// EFI_MEMORY_DESCRIPTOR is from BootServices
typedef EFI_STATUS SetVirtualAddressMap(UINTN MemoryMapSize, UINTN DescriptorSize, UINT32 DescriptorVersion, EFI_MEMORY_DESCRIPTOR *VirtualMap);

// ConvertPointer (Page 332)
typedef EFI_STATUS ConvertPointer(UINTN DebugDisposition, VOID **Address);

// GetVariable (Page 303)
typedef EFI_STATUS GetVariable(CHAR16 *VariableName, EFI_GUID *VenderGuide, UINT32 *Attributes /*Optional*/, UINTN *DataSize, VOID *Data /*Optional*/);

// GetNextVariableName (Page 306)
typedef EFI_STATUS GetNextVariableName(UINTN *VariableNameSize, CHAR16 *VariableName, EFI_GUID *VenderGuid);

// SetVariable (Page 308)
typedef EFI_STATUS SetVariable(CHAR16 *VariableName, EFI_GUID *VenderGuide, UINT32 Attributes, UINTN DataSize, VOID *Data);

// GetNextHighMonotonicCount (Page 336)
typedef EFI_STATUS GetNextHighMonotonicCount(UINT32 *HighCount);

// ResetSystem (Page 334)
typedef VOID (EFIAPI *EFI_RESET_SYSTEM) (EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize, VOID *ResetData);

// EFI_CAPSULE_HEADER (Page 338)
typedef struct {
	EFI_GUID CapsuleGuid;
	UINT32 HeaderSize;
	UINT32 Flags;
	UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

// UpdateCapsule (Page 337)
// EFI_PHYSICAL_ADDRESS?
typedef EFI_STATUS UpdateCapsule(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount, EFI_PHYSICAL_ADDRESS ScatterGatherList /*Optional*/);

// EFI_RESET_TYPE (Page 335)
typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

// QueryCapsuleCapabilities (Page 334)
typedef EFI_STATUS QueryCapsuleCapabilities(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount, UINT64 *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);

// QueryVariableInfo (Page 322)
typedef EFI_STATUS QueryVariableInfo(UINT32 Attributes, UINT64 *MaximumVariableStorageSize, UINT64 *RemainingVariableStorageSize, UINT64 *MaximumVariableSize);

#endif
