// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/BootServices.h>
#include <uefi/EntryPoint.h>
#include <uefi/FileProtocol.h>
#include <uefi/RuntimeServices.h>
#include <uefi/SimpleFileSystemProtocol.h>
#include <uefi/SimpleTextInputProtocol.h>
#include <uefi/SimpleTextOutputProtocol.h>
#include <uefi/GraphicsOutputProtocol.h>
#include <uefi/SystemTable.h>
#include <uefi/types.h>

#ifndef UEFI_H
#define UEFI_H

// Protocol GUIDs
#define EFI_FILE_INFO_GUID {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID {0x9042a9de,0x23dc,0x4a38, {0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}}
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID {0x0964e5b22,0x6459,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

// Status Codes(Page 2286)
#if __SIZEOF_POINTER__ == 8
#define EFI_HIGH_BIT 1 << 63
#else
#error "Unable to define EFI_HIGH_BIT"
#endif

#define EFI_SUCCESS 0

#define EFI_LOAD_ERROR EFI_HIGH_BIT | 1
#define EFI_INVALID_PARAMETER EFI_HIGH_BIT | 2
#define EFI_UNSUPPORTED EFI_HIGH_BIT | 3
#define EFI_BAD_BUFFER_SIZE EFI_HIGH_BIT | 4
#define EFI_BUFFER_TOO_SMALL EFI_HIGH_BIT | 5
#define EFI_NOT_READY EFI_HIGH_BIT | 6
#define EFI_DEVICE_ERROR EFI_HIGH_BIT | 7
#define EFI_WRITE_PROTECTED EFI_HIGH_BIT | 8
#define EFI_OUT_OF_RESOURCES EFI_HIGH_BIT | 9
#define EFI_VOLUME_CORRUPTED EFI_HIGH_BIT | 10
#define EFI_VOLUME_FULL EFI_HIGH_BIT | 11
#define EFI_NO_MEDIA EFI_HIGH_BIT | 12
#define EFI_MEDIA_CHANGED EFI_HIGH_BIT | 13
#define EFI_NOT_FOUND EFI_HIGH_BIT | 14
#define EFI_ACCESS_DENIED EFI_HIGH_BIT | 15
#define EFI_NO_RESPONSE EFI_HIGH_BIT | 16
#define EFI_NO_MAPPING EFI_HIGH_BIT | 17
#define EFI_TIMEOUT EFI_HIGH_BIT | 18
#define EFI_NOT_STARTED EFI_HIGH_BIT | 19
#define EFI_ALREADY_STARTED EFI_HIGH_BIT | 20
#define EFI_ABORTED EFI_HIGH_BIT | 21
#define EFI_ICMP_ERROR EFI_HIGH_BIT | 22
#define EFI_TFTP_ERROR EFI_HIGH_BIT | 23
#define EFI_PROTOCOL_ERROR EFI_HIGH_BIT | 24
#define EFI_INCOMPATIBLE_VERSION EFI_HIGH_BIT | 25
#define EFI_SECURITY_VIOLATION EFI_HIGH_BIT | 26
#define EFI_CRC_ERROR EFI_HIGH_BIT | 27
#define EFI_END_OF_MEDIA EFI_HIGH_BIT | 28
#define EFI_END_OF_FILE EFI_HIGH_BIT | 31
#define EFI_INVALID_LANGUAGE EFI_HIGH_BIT | 32
#define EFI_COMPROMISED_DATA EFI_HIGH_BIT | 33
#define EFI_IP_ADDRESS_CONFLICT EFI_HIGH_BIT | 34
#define EFI_HTTP_ERROR EFI_HIGH_BIT | 35

#define EFI_WARN_UNKNOWN_GLYPH 1
#define EFI_WARN_DELETE_FAILURE 2
#define EFI_WARN_WRITE_FAILURE 3
#define EFI_WARN_BUFFER_TOO_SMALL 4
#define EFI_WARN_STALE_DATA 5
#define EFI_WARN_FILE_SYSTEM 6
#define EFI_WARN_RESET_REQUIRED 7

#endif
