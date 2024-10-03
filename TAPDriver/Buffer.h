#ifndef _SIMPLE_BUFFER_H
#define _SIMPLE_BUFFER_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleBuffer
{
	//Trace ID.
	_INT32 nTraceID;

	//Block
	_BLOCK block;

	//Offset
	_UINT32 nOffset;
	//Count
	//Real count of the bytes.
	_UINT32 nCount;

}

SimpleBuffer;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeBuffer(SimpleBuffer* pBuffer);

extern _BOOL IsEndOfBuffer(SimpleBuffer* pBuffer);
extern _BOOL SetBufferOffset(SimpleBuffer* pBuffer,_INT32 nOffset,_BOOL bAbsolute);

////////////////////////////////////////////////////////////////////////////////
//
// General INT8 functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL GetINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8* lpValue);
extern _BOOL GetByte(SimpleBuffer* pBuffer,_BYTE* lpByte);

extern _BOOL SetINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8 nValue);
extern _BOOL SetByte(SimpleBuffer* pBuffer,_BYTE bValue);

extern _BOOL InsertINT8(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT8 nValue);
extern _BOOL InsertByte(SimpleBuffer* pBuffer,_BYTE bValue);

////////////////////////////////////////////////////////////////////////////////
//
// General INT16 functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL GetINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16* lpValue);
extern _BOOL GetShort(SimpleBuffer* pBuffer,_SHORT* lpShort);

extern _BOOL SetINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16 nValue);
extern _BOOL SetShort(SimpleBuffer* pBuffer,_SHORT sValue);

extern _BOOL InsertINT16(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT16 nValue);
extern _BOOL InsertShort(SimpleBuffer* pBuffer,_SHORT sValue);

////////////////////////////////////////////////////////////////////////////////
//
// General INT32 functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL GetINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32* lpValue);
extern _BOOL GetInteger(SimpleBuffer* pBuffer,_INTEGER* lpInteger);

extern _BOOL SetINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32 nValue);
extern _BOOL SetInteger(SimpleBuffer* pBuffer,_INTEGER nValue);

extern _BOOL InsertINT32(SimpleBuffer* pBuffer,_UINT32 nOffset,_INT32 nValue);
extern _BOOL InsertInteger(SimpleBuffer* pBuffer,_INTEGER nValue);

////////////////////////////////////////////////////////////////////////////////
//
// General array functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL GetUINT8Buffer(SimpleBuffer* pBuffer,_UINT32 nOffset,_UINT8* lpBuffer,_UINT32 nSize);
extern _BOOL GetBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nSize);

extern _BOOL GetEndableBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nMaxSize,_BYTE bEnd);

extern _BOOL SetUINT8Buffer(SimpleBuffer* pBuffer,_UINT32 nOffset,_UINT8* lpBuffer,_UINT32 nSize);
extern _BOOL SetBytes(SimpleBuffer* pBuffer,_BYTE* lpBytes,_UINT32 nSize);

////////////////////////////////////////////////////////////////////////////////
//
// General string functions.
//
////////////////////////////////////////////////////////////////////////////////

#define GetString(pBuffer,lpstrContent,nSize) \
	GetBytes(pBuffer,lpstrContent,nSize)
#define GetEndableString(pBuffer,lpstrContent,nMaxSize,bEnd) \
	GetEndableBytes(pBuffer,lpstrContent,nMaxSize,bEnd)
#define GetCString(pBuffer,lpstrContent) \
	GetEndableString(pBuffer,lpstrContent,PASCAL_STRING_LENGTH,'\0')

extern _BOOL SetString(SimpleBuffer* pBuffer,_STRING lpstrContent);
extern _BOOL SetEndableString(SimpleBuffer* pBuffer,_STRING lpstrContent,_BYTE bEndByte);
extern _BOOL SetFixString(SimpleBuffer* pBuffer,_STRING lpstrContent,_UINT32 nSize,_BOOL bPaddingMode);

#define SetCString(pBuffer,lpstrContent) \
	SetEndableString(pBuffer,lpstrContent,'\0')

////////////////////////////////////////////////////////////////////////////////
//
// General dump functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _STRING DumpBuffer(_STRING lpstrFormat,SimpleBuffer* pBuffer);
extern void LogBuffer(SimpleBuffer* lpBuffer);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
