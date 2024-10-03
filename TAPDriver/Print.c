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
// Special including files.
//
// Including the files for the specifal operation system.
//
// These including files are used for the specifal operation system.
//
////////////////////////////////////////////////////////////////////////////////

//ANSI C standard.
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
//
// Defination for end of a line.
//
// Different system has different defination for end of a line.
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS
#define END_OF_LINE												"\r\n"
#endif

//For linux.
#ifdef _REDHAT_LINUX
#define END_OF_LINE												"\n"
#endif

//For machintosh
#ifdef _MACHINTOSH_MAC_OS
#define END_OF_LINE												"\r"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Print.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 Print(FILE* lpFile,_STRING lpstrFormat,...)
{
	//Size.
	_INT32 nSize = 0;
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpFile != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Print variable arguments.
	nSize = vfprintf(lpFile,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);
	//Return size.	
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
//
// Print line.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 PrintLine(FILE* lpFile,_STRING lpstrFormat,...)
{
	//Size.
	_INT32 nSize = 0;
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpFile != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Print variable arguments.
	nSize = vfprintf(lpFile,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Print end of line.
	fprintf(lpFile,END_OF_LINE);
	//Return size.
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
//
// Format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING Format(_STRING lpstrContent,_STRING lpstrFormat,...)
{
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpstrContent != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Format variable arguments.
	vsprintf(lpstrContent,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Move pointer.
	lpstrContent += strlen(lpstrContent);
	//Return pointer.
	return lpstrContent;
}

////////////////////////////////////////////////////////////////////////////////
//
// Format line.
//
////////////////////////////////////////////////////////////////////////////////

_STRING FormatLine(_STRING lpstrContent,_STRING lpstrFormat,...)
{
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpstrContent != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Format variable arguments.
	vsprintf(lpstrContent,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Format end of line.
	strcat(lpstrContent,END_OF_LINE);

	//Move pointer.
	lpstrContent += strlen(lpstrContent);
	//Return pointer.
	return lpstrContent;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is end with new line.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsEndWithNewLine(_STRING lpstrContent)
{
#ifdef _DEBUG
	assert(lpstrContent != NULL);
#endif

	lpstrContent += strlen(lpstrContent) - sizeof(END_OF_LINE);
	//Check end with new line.
	if(strncmp(lpstrContent,END_OF_LINE,sizeof(END_OF_LINE)) == 0)
	{
		return _TRUE;
	}

	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Clear end with new line.
//
////////////////////////////////////////////////////////////////////////////////

void ClearEndWithNewLine(_STRING lpstrContent)
{
	_STRING lpstrEnd;

#ifdef _DEBUG
	assert(lpstrContent != NULL);
#endif

	//Move to end.
	lpstrEnd = lpstrContent + strlen(lpstrContent);
	//Check result.
	while(lpstrEnd > lpstrContent)
	{
		//Backward.
		lpstrEnd -= strlen(END_OF_LINE);
		//Check end with new line.
		if(strncmp(lpstrEnd,END_OF_LINE,strlen(END_OF_LINE)) != 0)
		{
			//Break.
			break;
		}
		//Set end of line.
		*lpstrEnd = '\0';
	}
}
