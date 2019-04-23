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
typedef EFI_STATUS (*EFI_SET_TIME)(EFI_TIME *Time);

// EFI_GET_WAKEUP_TIME(Page 328)
typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(BOOLEAN *Enabled, BOOLEAN *Pending, EFI_TIME *Time);

// EFI_SET_WAKEUP_TIME(Page 329)
typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(BOOLEAN Enable, EFI_TIME *Time); // Is this correct?
// typedef EFI_STATUS EnableWakeupTime(BOOLEAN Enable);

// SetVirtualAddressMap (Page 331)
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(UINTN MemoryMapSize, UINTN DescriptorSize, UINT32 DescriptorVersion, EFI_MEMORY_DESCRIPTOR *VirtualMap);

// ConvertPointer (Page 332)
typedef EFI_STATUS (*EFI_CONVERT_POINTER)(UINTN DebugDisposition, VOID **Address);

// GetVariable (Page 303)
typedef EFI_STATUS (*EFI_GET_VARIABLE)(CHAR16 *VariableName, EFI_GUID *VenderGuide, UINT32 *Attributes /*Optional*/, UINTN *DataSize, VOID *Data /*Optional*/);

// GetNextVariableName (Page 306)
typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(UINTN *VariableNameSize, CHAR16 *VariableName, EFI_GUID *VenderGuid);

// SetVariable (Page 308)
typedef EFI_STATUS (*EFI_SET_VARIABLE)(CHAR16 *VariableName, EFI_GUID *VenderGuide, UINT32 Attributes, UINTN DataSize, VOID *Data);

// GetNextHighMonotonicCount (Page 336)
typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONOTONIC_COUNT)(UINT32 *HighCount);

// EFI_RESET_TYPE (Page 335)
typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

// ResetSystem (Page 334)
typedef VOID (*EFI_RESET_SYSTEM)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize, VOID *ResetData);

// EFI_CAPSULE_HEADER (Page 338)
typedef struct {
	EFI_GUID CapsuleGuid;
	UINT32 HeaderSize;
	UINT32 Flags;
	UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

// UpdateCapsule (Page 337)
typedef EFI_STATUS (*EFI_UPDATE_CAPSULE)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount, EFI_PHYSICAL_ADDRESS ScatterGatherList /*Optional*/);

// QueryCapsuleCapabilities (Page 334)
typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount, UINT64 *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);

// QueryVariableInfo (Page 322)
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(UINT32 Attributes, UINT64 *MaximumVariableStorageSize, UINT64 *RemainingVariableStorageSize, UINT64 *MaximumVariableSize);

// EFI_RUNTIME_SERVICES (Page 171)
typedef struct {
	EFI_TABLE_HEADER Hdr;

	EFI_GET_TIME GetTime; // Prototype missing from docs?
	EFI_SET_TIME SetTime;
	EFI_GET_WAKEUP_TIME GetWakeupTime;
	EFI_SET_WAKEUP_TIME SetWakeupTime;

	EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
	EFI_CONVERT_POINTER ConvertPointer;

	EFI_GET_VARIABLE GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
	EFI_SET_VARIABLE SetVariable;

	EFI_GET_NEXT_HIGH_MONOTONIC_COUNT GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM ResetSystem;

	EFI_UPDATE_CAPSULE UpdateCapsule;
	EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

	EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

#endif
