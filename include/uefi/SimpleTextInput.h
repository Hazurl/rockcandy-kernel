// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_SIMPLE_TEXT_INPUT_H
#define UEFI_SIMPLE_TEXT_INPUT_H

// EFI_INPUT_RESET(Page 512)
typedef EFI_STATUS (VOID *EFI_INPUT_RESET) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

// EFI_INPUT_KEY(Page 513)
typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

// EFI_INPUT_READ_KEY(Page 513)
typedef EFI_STATUS (VOID *EFI_INPUT_READ_KEY) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);

// EFI_SIMPLE_TEXT_INPUT_PROTOCOL(Page 511)
typedef struct {
	EFI_INPUT_RESET Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

#endif
