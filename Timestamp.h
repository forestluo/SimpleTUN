#ifndef _SIMPLE_TIMESTAMP_H
#define _SIMPLE_TIMESTAMP_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void GetTimestampComment(_PASCALSTRING strTimestamp,_UINT32 nTimestamp);

extern void FormatTimestamp(_PASCALSTRING strTimestamp,_UINT32 nTimestamp);
extern void ScanTimestamp(_PASCALSTRING strTimestamp,_UINT32* lpTimestamp);

extern _UINT32 GetCurrentTimestamp();

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
