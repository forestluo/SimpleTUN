#ifndef _SIMPLE_HEX_H
#define _SIMPLE_HEX_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL IsHexCharacater(_CHAR cValue);

extern _CHAR GetHexCharacater(_BYTE cValue);
extern _BYTE GetHexValue(_CHAR cValue);

extern _BYTE ToHexValue(_WIDECHAR cValue);
extern _WIDECHAR ToHexCharacater(_BYTE bValue);

extern _WIDESTRING HexFormat(_WIDESTRING lpwstrFormat,_BYTE* lpBuffer,_UINT32 nSize);
extern void HexScan(_WIDESTRING lpwstrFormat,_BYTE* lpBuffer,_UINT32 nSize);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
