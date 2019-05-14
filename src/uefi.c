#include <uefi.h>

u16* EFI_GET_STATUS_MESSAGE(EFI_STATUS status) {
    static u16* statusMessages[] = {
        /*                           */ u"Unknown status",

        /* EFI_SUCCESS               */ u"The operation completed successfully",

        /* EFI_WARN_UNKNOWN_GLYPH    */ u"The string contained one or more characters that the device could not render and were skipped",
        /* EFI_WARN_DELETE_FAILURE   */ u"The handle was closed, but the file was not deleted",
        /* EFI_WARN_WRITE_FAILURE    */ u"The handle was closed, but the data to the file was not flushed properly",
        /* EFI_WARN_BUFFER_TOO_SMALL */ u"The resulting buffer was too small, and the data was truncated to the buffer size", 
        /* EFI_WARN_STALE_DATA       */ u"The data has not been updated within the timeframe set by local policy for this type of data",
        /* EFI_WARN_FILE_SYSTEM      */ u"The resulting buffer contains UEFI-compliant file system", 
        /* EFI_WARN_RESET_REQUIRED   */ u"The operation will be processed across a system reset",
    };

    static u16* errorStatusMessages[] = {
        /*                           */ u"Unknown error status",

        /* EFI_LOAD_ERROR            */ u"The image failed to load",
        /* EFI_INVALID_PARAMETER     */ u"A parameter was incorrect",
        /* EFI_UNSUPPORTED           */ u"The operation is not supported",
        /* EFI_BAD_BUFFER_SIZE       */ u"The buffer was not the proper size for the request",
        /* EFI_BUFFER_TOO_SMALL      */ u"The buffer is not large enough to hold the requested data. The required buffer size is returned in the appropriate parameter when this error occurs",
        /* EFI_NOT_READY             */ u"There is no data pending upon return",
        /* EFI_DEVICE_ERROR          */ u"The physical device reported an error while attempting the operation",
        /* EFI_WRITE_PROTECTED       */ u"The device cannot be written to",
        /* EFI_OUT_OF_RESOURCES      */ u"A resource has run out",
        /* EFI_VOLUME_CORRUPTED      */ u"An inconstancy was detected on the file system causing the operating to fail",
        /* EFI_VOLUME_FULL           */ u"There is no more space on the file system",
        /* EFI_NO_MEDIA              */ u"The device does not contain any medium to perform the operation",
        /* EFI_MEDIA_CHANGED         */ u"The medium in the device has changed since the last access",
        /* EFI_NOT_FOUND             */ u"The item was not found",
        /* EFI_ACCESS_DENIED         */ u"Access was denied",
        /* EFI_NO_RESPONSE           */ u"The server was not found or did not respond to the request",
        /* EFI_NO_MAPPING            */ u"A mapping to a device does not exist",
        /* EFI_TIMEOUT               */ u"The timeout time expired",
        /* EFI_NOT_STARTED           */ u"The protocol has not been started",
        /* EFI_ALREADY_STARTED       */ u"The protocol has already been started",
        /* EFI_ABORTED               */ u"The operation was aborted",
        /* EFI_ICMP_ERROR            */ u"An ICMP error occurred during the network operation",
        /* EFI_TFTP_ERROR            */ u"A TFTP error occurred during the network operation",
        /* EFI_PROTOCOL_ERROR        */ u"A protocol error occurred during the network operation",
        /* EFI_INCOMPATIBLE_VERSION  */ u"The function encountered an internal version that was incompatible with a version requested by the caller",
        /* EFI_SECURITY_VIOLATION    */ u"The function was not performed due to a security violation",
        /* EFI_CRC_ERROR             */ u"A CRC error was detected",
        /* EFI_END_OF_MEDIA          */ u"Beginning or end of media was reached",
        /*                           */ u"Unknown error status",
        /*                           */ u"Unknown error status",
        /* EFI_END_OF_FILE           */ u"The end of the file was reached",
        /* EFI_INVALID_LANGUAGE      */ u"The language specified was invalid",
        /* EFI_COMPROMISED_DATA      */ u"The security status of the data is unknown or compromised and the data must be updated or replaced to restore a valid security status",
        /* EFI_IP_ADDRESS_CONFLICT   */ u"There is an address conflict address allocation",
        /* EFI_HTTP_ERROR            */ u"A HTTP error occurred during the network operation",

    };

    if (EFI_ERROR(status)) {
        status = status & ~(EFI_HIGH_BIT);
        if (status >= sizeof(errorStatusMessages) / sizeof(errorStatusMessages[0])) {
            return errorStatusMessages[0];
        }

        return errorStatusMessages[status];
    }
    else {
        status += 1;

        if (status >= sizeof(statusMessages) / sizeof(statusMessages[0])) {
            return statusMessages[0];
        }

        return statusMessages[status];
    }
}
