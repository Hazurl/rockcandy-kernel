// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>
#include <uefi/SystemTable.h>

#ifndef UEFI_ENTRY_POINT_H
#define UEFI_ENTRY_POINT_H

// EFI_IMAGE_ENTRY_POINT(Page 162)
typedef EFI_STATUS (VOID *EFI_IMAGE_ENTRY_POINT) (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);

#endif
