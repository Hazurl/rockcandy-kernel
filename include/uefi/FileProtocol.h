// Page numbers relate to this document:
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf

#include <uefi/types.h>

#ifndef UEFI_FILE_PROTOCOL_H
#define UEFI_FILE_PROTOCOL_H

struct _EFI_FILE_PROTOCOL;

// EFI_FILE_IO_TOKEN(Page 587)
typedef struct {
  EFI_EVENT Event;
  EFI_STATUS Status;
  UINTN BufferSize;
  VOID *Buffer;
} EFI_FILE_IO_TOKEN;

// EFI_FILE_MODE(Page 582)
#define EFI_FILE_MODE_READ (1 << 0)
#define EFI_FILE_MODE_WRITE (1 << 1)
#define EFI_FILE_MODE_CREATE (1 << 63)

// EFI File Attributes(Page 582)
#define EFI_FILE_READ_ONLY (1 << 0)
#define EFI_FILE_HIDDEN (1 << 1)
#define EFI_FILE_SYSTEM (1 << 2)
#define EFI_FILE_DIRECTORY (1 << 4)
#define EFI_FILE_ARCHIVE (1 << 5)
#define EFI_FILE_VALID_ATTR 0x37 // Do we even need this?

// EFI_FILE_OPEN(Page 581)
typedef EFI_STATUS (*EFI_FILE_OPEN) (struct _EFI_FILE_PROTOCOL *This, struct _EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode, UINT64 Attributes);

// EFI_FILE_CLOSE(Page 583)
typedef EFI_STATUS (*EFI_FILE_CLOSE) (struct _EFI_FILE_PROTOCOL *This);

// EFI_FILE_DELETE(Page 584)
typedef EFI_STATUS (*EFI_FILE_DELETE) (struct _EFI_FILE_PROTOCOL *This);

// EFI_FILE_READ(Page 584)
typedef EFI_STATUS (*EFI_FILE_READ) (struct _EFI_FILE_PROTOCOL *This, UINTN *BufferSize, VOID *Buffer);

// EFI_FILE_WRITE(Page 586)
typedef EFI_STATUS (*EFI_FILE_WRITE) (struct _EFI_FILE_PROTOCOL *This, UINTN *BufferSize, VOID *Buffer);

// EFI_FILE_GET_POSITION(Page 594)
typedef EFI_STATUS (*EFI_FILE_GET_POSITION) (struct _EFI_FILE_PROTOCOL *This, UINT64 *Position);

// EFI_FILE_SET_POSITION(Page 593)
typedef EFI_STATUS (*EFI_FILE_SET_POSITION) (struct _EFI_FILE_PROTOCOL *This, UINT64 Position);

// EFI_FILE_GET_INFO(Page 595)
typedef EFI_STATUS (*EFI_FILE_GET_INFO) (struct _EFI_FILE_PROTOCOL *This, EFI_GUID *InformationType, UINTN *BufferSize, VOID *Buffer);

// EFI_FILE_SET_INFO(Page 596)
typedef EFI_STATUS (*EFI_FILE_SET_INFO) (struct _EFI_FILE_PROTOCOL *This, EFI_GUID *InformationType, UINTN BufferSize, VOID *Buffer);

// EFI_FILE_FLUSH(Page 598)
typedef EFI_STATUS (*EFI_FILE_FLUSH) (struct _EFI_FILE_PROTOCOL *This);

// EFI_FILE_OPEN_EX(Page 586)
typedef EFI_STATUS (*EFI_FILE_OPEN_EX) (struct _EFI_FILE_PROTOCOL *This, struct _EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode, UINT64 Attributes, EFI_FILE_IO_TOKEN *Token);

// EFI_FILE_READ_EX(Page 589)
typedef EFI_STATUS (*EFI_FILE_READ_EX) (struct _EFI_FILE_PROTOCOL *This, EFI_FILE_IO_TOKEN *Token);

// EFI_FILE_WRITE_EX(Page 590)
typedef EFI_STATUS (*EFI_FILE_WRITE_EX) (struct _EFI_FILE_PROTOCOL *This, EFI_FILE_IO_TOKEN *Token);

// EFI_FILE_FLUSH_EX(Page 592)
typedef EFI_STATUS (*EFI_FILE_FLUSH_EX) (struct _EFI_FILE_PROTOCOL *This, EFI_FILE_IO_TOKEN *Token);

// EFI_FILE_PROTOCOL(Page 580)
#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

typedef struct _EFI_FILE_PROTOCOL {
  UINT64 Revision;
  EFI_FILE_OPEN Open;
  EFI_FILE_CLOSE Close;
  EFI_FILE_DELETE Delete;
  EFI_FILE_READ Read;
  EFI_FILE_WRITE Write;
  EFI_FILE_GET_POSITION GetPosition;
  EFI_FILE_SET_POSITION SetPosition;
  EFI_FILE_GET_INFO GetInfo;
  EFI_FILE_SET_INFO SetInfo;
  EFI_FILE_FLUSH Flush;
  EFI_FILE_OPEN_EX OpenEx; // Rev2
  EFI_FILE_READ_EX ReadEx; // Rev2
  EFI_FILE_WRITE_EX WriteEx; // Rev2
  EFI_FILE_FLUSH_EX FlushEx; // Rev2
} EFI_FILE_PROTOCOL;

typedef struct {
	u64 Size;
	u64 FileSize;
	u64 PhysicalSize;
	EFI_TIME CreateTime;
	EFI_TIME LastAccessTime;
	EFI_TIME ModificationTime;
	u64 Attribute;
	CHAR16 FileName[];
} EFI_FILE_INFO;

#endif
