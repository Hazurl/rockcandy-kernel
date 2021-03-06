// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_H
#define UEFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_H

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_;

// EFI_TEXT_RESET (Page 516)
typedef EFI_STATUS (*EFI_TEXT_RESET) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, BOOLEAN ExtendedVerification);

// EFI_TEXT_STRING (Page 517)
typedef EFI_STATUS (*EFI_TEXT_STRING) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, CHAR16 *String);

// EFI_TEXT_TEST_STRING (Page 520)
typedef EFI_STATUS (*EFI_TEXT_TEST_STRING) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, CHAR16 *String);

// EFI_TEXT_QUERY_MODE (Page 521)
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, UINTN ModeNumber, UINTN *Columns, UINTN *Rows);

// EFI_TEXT_SET_MODE (Page 522)
typedef EFI_STATUS (*EFI_TEXT_SET_MODE) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, UINTN ModeNumber);

// EFI_TEXT_SET_ATTRIBUTE (Page 522)
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, UINTN Attribute);
#define EFI_TEXT_ATTR(Foreground, Background) ((Foreground) | ((Background) << 4))

// EFI_TEXT_CLEAR_SCREEN (Page 525)
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This);

// EFI_TEXT_SET_CURSOR_POSITION (Page 525)
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, UINTN Column, UINTN Row);

// EFI_TEXT_ENABLE_CURSOR (Page 525)
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ *This, BOOLEAN visible);

// SIMPLE_TEXT_OUTPUT_MODE (Page 515)
typedef struct {
	INT32 MaxMode;
	INT32 Mode;
	INT32 Attribute;
	INT32 CursorColumn;
	INT32 CursorRow;
	BOOLEAN CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL (Page 514)
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_ {
	EFI_TEXT_RESET Reset;
	EFI_TEXT_STRING OutputString;
	EFI_TEXT_TEST_STRING TestString;
	EFI_TEXT_QUERY_MODE QueryMode;
	EFI_TEXT_SET_MODE SetMode;
	EFI_TEXT_SET_ATTRIBUTE SetAttribute;
	EFI_TEXT_CLEAR_SCREEN ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#endif
