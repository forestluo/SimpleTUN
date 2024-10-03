////////////////////////////////////////////////////////////////////////////////
//
// Global including files.
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include "Global.h"

////////////////////////////////////////////////////////////////////////////////
//
// Get checksum16.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetChecksum16(_BYTE* lpBytes,_INT32 nSize)
{
	//Checksum.
	_UINT32 nChecksum;

	//Byte
	_UINT8 bValue;
	//Short.
	_UINT16* lpShorts = (_UINT16 *)lpBytes;

#ifdef _DEBUG
	assert(lpBytes != NULL && nSize > 0);
#endif

	//Set checksum.
	nChecksum = 0;
	//Do while.
	while(nSize > 1)
	{
		//Add byte.
		nChecksum += *lpShorts;

		//Add pointer.
		lpShorts ++;
		//Sub
		nSize -= sizeof(_UINT16);
	}
	//Check size.
	if(nSize != 0)
	{
		//Add it.
		nChecksum += *((_UINT8 *)lpShorts);
	}

	//Adjust.
	nChecksum = (nChecksum & 0xFFFF) + (nChecksum >> 16);
	//Adjust.
	nChecksum += nChecksum >> 16;
	//Adjust.
	nChecksum = ~nChecksum;

	//Get low byte.
	bValue = (_UINT8)nChecksum;
	//Shift right.
	nChecksum = (nChecksum >> 8) & 0xFF;
	//Add higher part.
	nChecksum |= bValue << 8;
	//Return result.
	return nChecksum;
}
