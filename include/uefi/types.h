// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#ifndef UEFI_TYPES_H
#define UEFI_TYPES_H

// UEFI Types(Page 93)
typedef signed char INT8;
typedef unsigned char UINT8;

#if __SIZEOF_SHORT__ == 2
typedef signed short INT16;
typedef unsigned short UINT16;
#else
#error "Unable to define INT16"
#endif

#if __SIZEOF_INT__ == 4
typedef signed int INT32;
typedef unsigned int UINT32;
#else
#error "Unable to define INT32"
#endif

#if __SIZEOF_LONG__ == 8
typedef signed long INT64;
typedef unsigned long UINT64;
#else
#error "Unable to define INT64"
#endif

typedef struct { INT64 x[2]; } INT128; // Yuck
typedef struct { UINT64 x[2]; } UINT128; // Is there a better way to do this?

#if __SIZEOF_POINTER__ == 4
typedef INT32 INTN;
typedef UINT32 UINTN;
#elif __SIZEOF_POINTER__ == 8
typedef INT64 INTN;
typedef UINT64 UINTN;
#elif __SIZEOF_POINTER__ == 16
typedef INT128 INTN;
typedef UINT128 UINTN;
#else
#error "Unable to define INTN"
#endif

typedef UINT8 BOOLEAN;

typedef UINT8 CHAR8;
typedef UINT16 CHAR16;
typedef void VOID; // Do we even need this?
typedef struct { UINT64 x[2]; } EFI_GUID; // Aligned on a 64-bit boundary
typedef UINTN EFI_STATUS;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;
typedef struct { UINT8 x[32]; } EFI_MAC_ADDRESS;
typedef struct { UINT8 x[4]; } EFI_IPv4_ADDRESS;
typedef struct { UINT8 x[16]; } EFI_IPv6_ADDRESS;
typedef struct { UINT32 x[4]; } EFI_IP_ADDRESS; // Aligned on a 4 byte boundary

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

// EFI_EVENT(Page 218)
typedef VOID *EFI_EVENT;

// EFI_HANDLE(Page 249)
typedef VOID *EFI_HANDLE;

#endif
