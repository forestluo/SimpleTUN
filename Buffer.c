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
// Internal requirements.
//
////////////////////////////////////////////////////////////////////////////////

//Byte Order
//PC Host Byte Order
#define _NETWORK_BYTE_ORDER_								1
//Network Byte Order
#define _PC_HOST_BYTE_ORDER_								2

//Current Byte Order
#define _CURRENT_BYTE_ORDER_								_NETWORK_BYTE_ORDER_

////////////////////////////////////////////////////////////////////////////////
//
// Initialize buffer.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeBuffer(SimpleBuffer* pBuffer)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Clear buffer.
	memset(pBuffer,0,sizeof(SimpleBuffer));

	//Set trace id.
	pBuffer->nTraceID = 0;

	//Set count.
	pBuffer->nCount = 0;
	//Set offset.
	pBuffer->nOffset = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is at the end of the buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsEndOfBuffer(SimpleBuffer* pBuffer)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check offset.
	if(pBuffer->nOffset >= pBuffer->nCount)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set offset of a buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetBufferOffset(SimpleBuffer* pBuffer,_INT32 nOffset,_BOOL bAbsolute)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check offset mode.
	if(bAbsolute)
	{
		//Check offset.
		if(nOffset < 0 || (unsigned)nOffset > pBuffer->nCount)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Buffer::SetBufferOffset : not proper absolute offset !");
#endif
			return _FALSE;
		}

		//Set offset of the buffer.
		pBuffer->nOffset = nOffset;
	}
	else
	{
		//Check offset.
		if((pBuffer->nOffset + nOffset) < 0 || (pBuffer->nOffset + nOffset) > pBuffer->nCount)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Buffer::SetBufferOffset : not proper relative offset !");
#endif
			return _FALSE;
		}

		//Add offset of the buffer.
		pBuffer->nOffset += nOffset;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get INT8 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8* lpValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL && lpValue != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT8) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::GetINT8 : not proper offset !");
#endif
		return _FALSE;
	}

	//Get value.
	*lpValue = (_INT8)pBuffer->block[nOffset];
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get byte.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetByte(SimpleBuffer* pBuffer,_BYTE* lpByte)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Get value.
	bResult = GetINT8(pBuffer,pBuffer->nOffset,lpByte);
	//Move offset.
	pBuffer->nOffset += sizeof(_BYTE);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set INT8 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8 nValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT8) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetINT8 : not proper offset !");
#endif
		return _FALSE;
	}

	//Set value.
	pBuffer->block[nOffset] = (_UINT8)nValue;
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set byte.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetByte(SimpleBuffer* pBuffer,_BYTE bValue)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	if(pBuffer->nCount + sizeof(_UINT8) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetByte : not proper offset !");
#endif
		return _FALSE;
	}

	//Add count.
	pBuffer->nCount += sizeof(_INT8);
	//Set value.
	bResult = SetINT8(pBuffer,pBuffer->nOffset,bValue);
	//Move offset.
	pBuffer->nOffset += sizeof(_INT8);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert INT8 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8 nValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check count.
	if(pBuffer->nCount + sizeof(_INT8) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::InsertINT8 : buffer owerflowed !");
#endif
		return _FALSE;
	}

	//Copy array.
	memmove(pBuffer->block + nOffset + sizeof(_INT8),pBuffer->block + nOffset,pBuffer->nCount - nOffset);
	//Set count.
	pBuffer->nCount += sizeof(_INT8);

	//Set value.
	return SetINT8(pBuffer,nOffset,nValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert byte.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertByte(SimpleBuffer* pBuffer,_BYTE bValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	return InsertINT8(pBuffer,pBuffer->nOffset,bValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get INT16 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16* lpValue)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpValue != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT16) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::GetINT16 : not proper offset !");
#endif
		return _FALSE;
	}

	//Set default value.
	*lpValue = 0;
	//Get value from buffer.
	for(i = 0;i < sizeof(_INT16);i ++)
	{

//Network byte order.
#if _CURRENT_BYTE_ORDER_ == _NETWORK_BYTE_ORDER_

		*lpValue |= ((_INT16)pBuffer->block[nOffset + i] & 0xFF) << ((sizeof(_UINT16) - i - 1) * 8);

#endif

//PC host byte order.
#if _CURRENT_BYTE_ORDER_ == _PC_HOST_BYTE_ORDER_

		*lpValue = ((_INT16)pBuffer->block[nOffset + i] & 0xFF) | (*lpValue << 8);

#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get short.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetShort(SimpleBuffer* pBuffer,_SHORT* lpShort)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Get value.
	bResult = GetINT16(pBuffer,pBuffer->nOffset,lpShort);
	//Move offset.
	pBuffer->nOffset += sizeof(_INT16);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set INT16 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16 nValue)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT16) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetINT16 : not proper offset !");
#endif
		return _FALSE;
	}

	for(i = 0;i < sizeof(_INT16);i ++)
	{

//Network byte order.
#if _CURRENT_BYTE_ORDER_ == _NETWORK_BYTE_ORDER_

		pBuffer->block[nOffset + i] = (_UINT8)((nValue >> ((sizeof(_UINT16) - i - 1) * 8)) & 0xFF);

#endif

//Current byte order.
#if _CURRENT_BYTE_ORDER_ == _PC_HOST_BYTE_ORDER_

		pBuffer->block[nOffset + sizeof(_INT16) - i - 1] = (_UINT8)((nValue >> (i * 8)) & 0xFF);

#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set short.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetShort(SimpleBuffer* pBuffer,_SHORT sValue)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	if(pBuffer->nCount + sizeof(_UINT16) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetShort : not proper offset !");
#endif
		return _FALSE;
	}

	//Add count.
	pBuffer->nCount += sizeof(_INT16);
	//Set value.
	bResult = SetINT16(pBuffer,pBuffer->nOffset,sValue);
	//Move offset.
	pBuffer->nOffset += sizeof(_INT16);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert INT16 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16 nValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check count.
	if(pBuffer->nCount + sizeof(_INT16) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::InsertINT16 : buffer owerflowed !");
#endif
		return _FALSE;
	}

	//Copy array.
	memmove(pBuffer->block + nOffset + sizeof(_INT16),pBuffer->block + nOffset,pBuffer->nCount - nOffset);
	//Set count.
	pBuffer->nCount += sizeof(_INT16);

	//Set value.
	return SetINT16(pBuffer,nOffset,nValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert short.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertShort(SimpleBuffer* pBuffer,_SHORT sValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	return InsertINT16(pBuffer,pBuffer->nOffset,sValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get INT32 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32* lpValue)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpValue != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT32) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::GetINT32 : not proper offset !");
#endif
		return _FALSE;
	}

	//Set default value.
	*lpValue = 0;
	//Get value from buffer.
	for(i = 0;i < sizeof(_INT32);i ++)
	{

//Network byte order.
#if _CURRENT_BYTE_ORDER_ == _NETWORK_BYTE_ORDER_

		*lpValue |= ((_INT32)pBuffer->block[nOffset + i] & 0xFF) << ((sizeof(_INT32) - i - 1) * 8);

#endif

//PC hose byte order.
#if _CURRENT_BYTE_ORDER_ == _PC_HOST_BYTE_ORDER_

		*lpValue = ((_INT32)pBuffer->block[nOffset + i] & 0xFF) | (*lpValue << 8);

#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get integer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetInteger(SimpleBuffer* pBuffer,_INTEGER* lpInteger)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Get value.
	bResult = GetINT32(pBuffer,pBuffer->nOffset,lpInteger);
	//Move offset.
	pBuffer->nOffset += sizeof(_INT32);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set INT32 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32 nValue)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check offset.
	if(nOffset + sizeof(_INT32) > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetINT32 : not proper offset !");
#endif
		return _FALSE;
	}

	for(i = 0;i < sizeof(_INT32);i ++)
	{

//Network byte order.
#if _CURRENT_BYTE_ORDER_ == _NETWORK_BYTE_ORDER_

		pBuffer->block[nOffset + i] = (_UINT8)((nValue >> ((sizeof(_INT32) - i - 1) * 8)) & 0xFF);

#endif

//PC host byte order.
#if _CURRENT_BYTE_ORDER_ == _PC_HOST_BYTE_ORDER_

		pBuffer->block[nOffset + sizeof(_INT32) - i - 1] = (_UINT8)((nValue >> (i * 8)) & 0xFF);

#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set integer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetInteger(SimpleBuffer* pBuffer,_INTEGER nValue)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	if(pBuffer->nCount + sizeof(_UINT32) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetInteger : not proper offset !");
#endif
		return _FALSE;
	}

	//Add count.
	pBuffer->nCount += sizeof(_INT32);
	//Set value.
	bResult = SetINT32(pBuffer,pBuffer->nOffset,nValue);
	//Move offset.
	pBuffer->nOffset += sizeof(_INT32);
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert INT32 value.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32 nValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif

	//Check size.
	if(pBuffer->nCount + sizeof(_INT32) > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::InsertINT32 : buffer owerflowed !");
#endif
		return _FALSE;
	}

	//Copy array.
	memmove(pBuffer->block + nOffset + sizeof(_INT32),pBuffer->block + nOffset,pBuffer->nCount - nOffset);
	//Set count.
	pBuffer->nCount += sizeof(_INT32);

	//Set value.
	return SetINT32(pBuffer,nOffset,nValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert integer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertInteger(SimpleBuffer* pBuffer,_INTEGER nValue)
{
#ifdef _DEBUG
	assert(pBuffer != NULL);
#endif
	//Return result.
	return InsertINT32(pBuffer,pBuffer->nOffset,nValue);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get UINT8 buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetUINT8Buffer(SimpleBuffer* pBuffer,_UINT32 nOffset,_UINT8* block,_UINT32 nSize)
{
#ifdef _DEBUG
	assert(pBuffer != NULL && block != NULL);
#endif

	//Check offset.
	if(nOffset + nSize > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::GetUINT8Buffer : not proper offset !");
#endif
		return _FALSE;
	}

	//Copy array.
	memcpy((void *)block,(const void *)&pBuffer->block[nOffset],nSize);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get bytes.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nSize)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpBytes != NULL);
#endif

	//Get value.
	bResult = GetUINT8Buffer(pBuffer,pBuffer->nOffset,lpBytes,nSize);
	//Move offset.
	pBuffer->nOffset += nSize;
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get bytes with specified end byte.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetEndableBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nMaxSize,_BYTE bEnd)
{
	_UINT32 i;
	_UINT32 nSize = 0;
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpBytes != NULL);
#endif

	//Clear bytes.
	memset(lpBytes,0,nMaxSize);

	//Check end.
	for(i = pBuffer->nOffset;i < pBuffer->nCount && nSize < nMaxSize;i ++)
	{
		//Check end byte.
		if(pBuffer->block[i] == bEnd)
		{
			//Get bytes from pBuffer.
			bResult = GetBytes(pBuffer,lpBytes,nSize);
			//Move offset.
			//Add the size of the end byte.
			pBuffer->nOffset += 1;

			return bResult;
		}

		nSize ++;
	}

#ifdef _DEBUG
	PrintLine(stderr,"Buffer::GetEndableBytes : end not found !");
#endif
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set UINT8 buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetUINT8Buffer(SimpleBuffer* pBuffer,_UINT32 nOffset,_UINT8* block,_UINT32 nSize)
{
#ifdef _DEBUG
	assert(pBuffer != NULL && block != NULL);
#endif

	//Check offset.
	if(nOffset + nSize > pBuffer->nCount)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetUINT8Buffer : not proper offset !");
#endif
		return _FALSE;
	}

	//Copy array.
	memcpy((void *)&pBuffer->block[nOffset],(const void *)block,nSize);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set bytes.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nSize)
{
	_BOOL bResult;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpBytes != NULL);
#endif

	if(pBuffer->nCount + nSize > BLOCK_SIZE)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetBytes : not proper offset !");
#endif
		return _FALSE;
	}

	//Add count.
	pBuffer->nCount += nSize;
	//Get value.
	bResult = SetUINT8Buffer(pBuffer,pBuffer->nOffset,lpBytes,nSize);
	//Move offset.
	pBuffer->nOffset += nSize;
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set string.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetString(SimpleBuffer* pBuffer,_STRING lpstrContent)
{
#ifdef _DEBUG
	assert(pBuffer != NULL && lpstrContent != NULL);
#endif

	//Set string.
	return SetBytes(pBuffer,(_UINT8 *)lpstrContent,(_UINT32)strlen(lpstrContent));
}

////////////////////////////////////////////////////////////////////////////////
//
// Set endable string.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetEndableString(SimpleBuffer* pBuffer,_STRING lpstrContent,_BYTE bEndByte)
{
#ifdef _DEBUG
	assert(pBuffer != NULL && lpstrContent != NULL);
#endif

	//Set content and end byte.
	if(SetString(pBuffer,lpstrContent) && SetByte(pBuffer,bEndByte))
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set fix size string and padding bytes.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetFixString(SimpleBuffer* pBuffer,_STRING lpstrContent,_UINT32 nSize,_BOOL bPaddingMode)
{
	_UINT32 i;

#ifdef _DEBUG
	assert(pBuffer != NULL && lpstrContent != NULL);
#endif

	//Check size.
	if(strlen(lpstrContent) > nSize)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Buffer::SetFixString : string is too long !");
#endif
		return _FALSE;
	}

	//Padding '0' on the left.
	for(i = 0;bPaddingMode && i < nSize - strlen(lpstrContent);i ++)
	{
		if(!SetByte(pBuffer,(_BYTE)'0'))
		{
			//Return false.
			return _FALSE;
		}
	}

	//Set string.
	if(!SetString(pBuffer,lpstrContent))
	{
		//Return false.
		return _FALSE;
	}

	//Padding '\0' on the right.
	for(i = 0;!bPaddingMode && i < nSize - (int)strlen(lpstrContent);i ++)
	{
		if(!SetByte(pBuffer,(_BYTE)'\0'))
		{
			//Return false.
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump buffer.
//
////////////////////////////////////////////////////////////////////////////////

_STRING DumpBuffer(_STRING lpstrFormat,SimpleBuffer* pBuffer)
{
#ifdef _DEBUG
	assert(lpstrFormat != NULL && pBuffer != NULL);
#endif

	lpstrFormat = FormatLine(lpstrFormat,"Buffer::Dump : show data !");
	//Dump trace id.
	lpstrFormat = FormatLine(lpstrFormat,"\tnTraceID = 0x%08x",
		pBuffer->nTraceID);
	//Dump count.
	lpstrFormat = FormatLine(lpstrFormat,"\tnCount = %u",
		pBuffer->nCount);
	//Dump offset.
	lpstrFormat = FormatLine(lpstrFormat,"\tnOffset = %u",
		pBuffer->nOffset);
	//Check count.
	if(pBuffer->nCount > 0)
	{
		//Dump buffer.
		lpstrFormat = Format(lpstrFormat,"\tblock = 0x");
		//Hex format.
		lpstrFormat = (_STRING)HexFormat((_WIDESTRING)lpstrFormat,pBuffer->block,pBuffer->nCount);
		//Format line.
		lpstrFormat = FormatLine(lpstrFormat,"");
	}
	//Return format.
	return lpstrFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Log buffer.
//
////////////////////////////////////////////////////////////////////////////////

void LogBuffer(SimpleBuffer* lpBuffer)
{
	//Format Block
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpBuffer != NULL);
#endif

	//Clear.
	memset(blockFormated,0,BLOCK_SIZE);
	//Dump buffer.
	DumpBuffer((_STRING)blockFormated,lpBuffer);
	//Log requested event.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_BUFFER | LOG_INFORMATION);
}
