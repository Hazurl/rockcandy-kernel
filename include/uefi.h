#include <stdint.h> // Is this safe to include?

// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

// UEFI Types(Page 93)

typedef BOOLEAN uint8_t;
typedef INTN intmax_t;
typedef UINTN uintmax_t;
typedef INT8 int8_t;
typedef UINT8 uint8_t;
typedef INT16 int16_t;
typedef UINT16 uint16_t;
typedef INT32 int32_t;
typedef UINT32 uint32_t;
typedef INT64 int64_t;
typedef UINT64 uint64_t;
typedef INT128 int64_t[2]; // Yuck
typedef UINT128 uint64_t[2]; // Is there a better way to do this?

typedef CHAR8 UINT8;
typedef CHAR16 UINT16;
typedef VOID void; // Do we even need this?
typedef EFI_GUID UINT64[2]; // Aligned on a 64-bit boundary
typedef EFI_STATUS UINTN;
typedef EFI_HANDLE VOID *;
typedef EFI_EVENT VOID *;
typedef EFI_LBA UINT64;
typedef EFI_TPL UINTN;
typedef EFI_MAC_ADDRESS UINT8[32];
typedef EFI_IPv4_ADDRESS UINT8[4];
typedef EFI_IPv6_ADDRESS UINT8[16];
typedef EFI_IP_ADDRESS UINT32[4]; // Aligned on a 4 byte boundary

// EFI_TABLE_HEADER(Page 163)

typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI_INPUT_RESET(Page 512)

typedef EFI_STATUS (VOID *EFI_INPUT_RESET) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

// EFI_INPUT_KEY

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

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL(Page 514)

// TODO

// EFI_RUNTIME_SERVICES(Page 171)

// TODO

// EFI_BOOT_SERVICES(Page 166)

// TODO

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

// EFI_IMAGE_ENTRY_POINT(Page 162)

typedef EFI_STATUS (VOID *EFI_IMAGE_ENTRY_POINT) (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
