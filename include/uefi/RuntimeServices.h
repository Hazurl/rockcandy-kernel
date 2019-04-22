// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_RUNTIME_SERVICES_H
#define UEFI_RUNTIME_SERVICES_H

// EFI_TABLE_HEADER(Page 163)

typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

// GetTime?

// EFI_SET_TIME(Page 327)
// EFI_TIME?
typedef EFI_STATUS SetTime(EFI_TIME *Time);

// EFI_GET_WAKEUP_TIME(Page 328)

typedef EFI_STATUS GetWakeupTime(typedef EFI_STATUS GetWakeupTime(BOOLEAN *Enabled, BOOLEAN *Pending, EFI_TIME *Time);

// EFI_SET_WAKEUP_TIME(Page 329)

typedef EFI_STATUS SetWakeupTime(BOOLEAN Enable, EFI_TIME *Time);
typedef EFI_STATUS SetWakeupTime(BOOLEAN Enable);

// SetVirtualAddressMap?

// ConvertPointer?

// GetVariable?

// GetNextVariableName?

// SetVariable?

// GetNextHighMonotonicCount?

// ResetSystem?

// UpdateCapsule?

// QueryCapsuleCapabilities?

// QueryVariableInfo?

#endif
