// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#ifndef UEFI_TYPES_H
#define UEFI_TYPES_H

// UEFI Types(Page 93)
#if sizeof(char) == 1
typedef signed char INT8;
typedef unsigned char UINT8;
#else
#error "Unable to define INT8"
#endif

#if sizeof(short) == 2
typedef signed short INT16;
typedef unsigned short UINT16;
#else
#error "Unable to define INT16"
#endif

#if sizeof(int) == 4
typedef signed int INT32;
typedef unsigned int UINT32;
#else
#error "Unable to define INT32"
#endif

#if sizeof(long) == 8
typedef signed long INT64;
typedef unsigned long UINT64;
#else
#error "Unable to define INT64"
#endif

typedef INT64[2] INT128; // Yuck
typedef UINT64[2] UINT128; // Is there a better way to do this?

#if sizeof(void *) == 4
typedef INT32 INTN;
typedef UINT32 UINTN;
#elif sizeof(void *) == 8
typedef INT64 INTN;
typedef UINT64 UINTN;
#elif sizeof(void *) == 16
typedef INT128 INTN;
typedef UINT128 UINTN;
#else
#error "Unable to define INTN"
#endif

typedef UINT8 BOOLEAN;

typedef UINT8 CHAR8;
typedef UINT16 CHAR16;
typedef void VOID; // Do we even need this?
typedef UINT64[2] EFI_GUID; // Aligned on a 64-bit boundary
typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;
typedef UINT8[32] EFI_MAC_ADDRESS;
typedef UINT8[4] EFI_IPv4_ADDRESS;
typedef UINT8[16] EFI_IPv6_ADDRESS;
typedef UINT32[4] EFI_IP_ADDRESS; // Aligned on a 4 byte boundary

// EFI_TABLE_HEADER(Page 163)
typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI_PHYSICAL_ADDRESS(Page 235)
typedef UINT64 EFI_PHYSICAL_ADDRESS;

#endif
