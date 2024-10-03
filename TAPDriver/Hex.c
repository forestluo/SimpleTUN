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
// Is hex characater.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsHexCharacater(_CHAR cValue)
{
	//Check value.
	if(cValue >= '0' && cValue <= '9')
	{
		//Return true.
		return _TRUE;
	}
	//Check value.
	if(cValue >= 'a' && cValue <= 'z')
	{
		//Return true.
		return _TRUE;
	}
	//Check value.
	if(cValue >= 'A' && cValue <= 'Z')
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get hex characater.
//
////////////////////////////////////////////////////////////////////////////////

_CHAR GetHexCharacater(_BYTE cValue)
{
	//Check value.
	if(cValue >= 0 && cValue <= 9)
	{
		//Add value.
		cValue += '0';
	}
	//Check value.
	else if(cValue >= 10 && cValue <= 15)
	{
		//Add value.
		cValue += 'a' - 10;
	}
	else
	{
#ifdef _DEBUG
		PrintLine(stderr,"Hex::GetHexCharacater : value is outof range !");
#endif
		return _FAILURE;
	}
	//Return value.
	return cValue;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get hex value.
//
////////////////////////////////////////////////////////////////////////////////

_BYTE GetHexValue(_CHAR cValue)
{
	//Check value.
	if(cValue >= '0' && cValue <= '9')
	{
		//Add value.
		cValue -= '0';
	}
	//Check value.
	else if(cValue >= 'a' && cValue <= 'z')
	{
		//Add value.
		cValue -= 'a' - 10;
	}
	//Check value.
	else if(cValue >= 'A' && cValue <= 'Z')
	{
		//Add value.
		cValue -= 'A' - 10;
	}
	else
	{
#ifdef _DEBUG
		PrintLine(stderr,"Hex::GetHexValue : invalid hex characater !");
#endif
		return _FAILURE;
	}
	//Return value.
	return cValue;
}

////////////////////////////////////////////////////////////////////////////////
//
// To hex value.
//
////////////////////////////////////////////////////////////////////////////////

_BYTE ToHexValue(_WIDECHAR wValue)
{
	_UINT32 i;

	_BYTE bValue = 0;
	_UINT32 nOffset = 0;
	//Do while.
	for(i = 0;i < sizeof(_WIDECHAR);i ++)
	{
		//Move left.
		bValue <<= 4;
		//Calculate offset.
		nOffset = 8 * i;
		//Get value.
		bValue |= GetHexValue((_CHAR)(wValue >> nOffset));
	}
	//Return value.
	return bValue;
}

////////////////////////////////////////////////////////////////////////////////
//
// To hex characater.
//
////////////////////////////////////////////////////////////////////////////////

_WIDECHAR ToHexCharacater(_BYTE bValue)
{
	_UINT32 i;

	_WIDECHAR wValue = 0;
	_UINT32 nOffset = 0;
	//Do while.
	for(i = 0;i < sizeof(_WIDECHAR);i ++)
	{
		//Move left.
		wValue <<= 8;
		//Calculate offset.
		nOffset = 4 * i;
		//Get value.
		wValue |= GetHexCharacater((_BYTE)((bValue >> nOffset) & 0x0F));
	}
	//Return value.
	return wValue;
}

////////////////////////////////////////////////////////////////////////////////
//
// Hex format.
//
////////////////////////////////////////////////////////////////////////////////

_WIDESTRING HexFormat(_WIDESTRING lpwstrFormat,_BYTE* lpBuffer,_UINT32 nSize)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(lpwstrFormat != NULL && lpBuffer != NULL);
#endif

	//Format bytes.
	for(i = 0;i < nSize;i ++)
	{
		//Format.
		lpwstrFormat[i] = ToHexCharacater(lpBuffer[i]);
	}

	//Add pointer.
	lpwstrFormat += nSize;
	//Return pointer.
	return lpwstrFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Hex scan.
//
////////////////////////////////////////////////////////////////////////////////

void HexScan(_WIDESTRING lpwstrFormat,_BYTE* lpBuffer,_UINT32 nSize)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(lpwstrFormat != NULL && lpBuffer != NULL);
#endif

	//Scan bytes.
	for(i = 0;i < nSize && i < strlen((_STRING)lpwstrFormat) / 2;i ++)
	{
		//Scan.
		lpBuffer[i] = ToHexValue(lpwstrFormat[i]);
	}
}

