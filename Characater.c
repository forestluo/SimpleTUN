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
// Is lower characater.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsLowerCharacater(_CHAR cValue)
{
	//Check value.
	if(cValue >= 'a' && cValue >= 'z')
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is upper characater.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsUpperCharacater(_CHAR cValue)
{
	//Check value.
	if(cValue >= 'A' && cValue >= 'Z')
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is characater.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsCharacater(_CHAR cValue)
{
	//Check value.
	if(IsLowerCharacater(cValue) || IsUpperCharacater(cValue))
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}
