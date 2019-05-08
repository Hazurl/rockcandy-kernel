#include <uefi/types.h>

/* 12.9 Graphics Output Protocol (page 549) */
#ifndef GRAPHICS_OUTPUT_PROTOCOL_H
#define GRAPHICS_OUTPUT_PROTOCOL_H

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_;

typedef struct {
    UINT8  Blue;
    UINT8  Green;
    UINT8  Red;
    UINT8  Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL; // Page 558

typedef enum {
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMa
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION; // Page 558

typedef enum {
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT; // Page 552

typedef struct {
    UINT32   RedMask;
    UINT32   GreenMask;
    UINT32   BlueMask;
    UINT32   ReservedMask;
} EFI_PIXEL_BITMASK; // Page 551

typedef struct {
    UINT32                      Version;
    UINT32                      HorizontalResolution;
    UINT32                      VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT   PixelFormat;
    EFI_PIXEL_BITMASK           PixelInformation;
    UINT32                      PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION; // Page 552

typedef struct {
    UINT32                                MaxMode;
    UINT32                                Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
    UINTN                                 SizeOfInfo;
    EFI_PHYSICAL_ADDRESS                  FrameBufferBase;
    UINTN                                 FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE; // Page 555

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL_ *This, UINT32 ModeNumber, UINTN *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL_ *This, UINT32 ModeNumber);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (struct EFI_GRAPHICS_OUTPUT_PROTOCOL_ *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *BltBuffer /*Optional*/, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX, UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta );

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL_ {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode; 
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE   SetMode; 
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT        Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE       *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL; // Page 551


#endif