// Page numbers relate to this document:
// http://www.osta.org/specs/pdf/udf260.pdf

#include <fixed.h>

#ifndef UDF_H
#define UDF_H

// Descriptor Tag(Page 26)
typedef struct {
	u16 TagIdentifier;
	u16 DescriptorVersion;
	u8 TagChecksum;
	u8 Reserved;
	u16 TagSerialNumber;
	u16 DescriptorCRC;
	u16 DescriptorCRCLength;
	u32 TagLocation;
} UDF_tag;

// Primary Volume Descriptor(Page 27)
typedef struct {
	UDF_tag DescriptorTag;
	u32 VolumeDescriptorSequenceNumber;
	u32 PrimaryVolumeDescriptorNumber;
	// dstring VolumeIdentifier[32];
	u16 VolumeSequenceNumber;
	u16 MaximumVolumeSequenceNumber;
	u16 InterchangeLevel;
	u16 MaximumInterchangeLevel;
	u32 CharacterSetList;
	u32 MaximumCharacterSetList;
	// dstring VolumeSetIdentifier[128];
	// I'm just going to stop here because we have so many new types to define
} UDF_PrimaryVolumeDescriptor;

#endif
