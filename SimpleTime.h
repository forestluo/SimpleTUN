#ifndef _SIMPLE_TIME_H
#define _SIMPLE_TIME_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleTime
{
	//Values
	//Date Values
	//Year(0) = 0000 ~ 9999
	//Month(1) = 01 ~ 12
	//Date(2) = 01 ~ 31
	_UINT32 nDateValues[3];
	//Time Values
	//Hour(0) = 00 ~ 23
	//Minute(1) = 00 ~ 60
	//Second(2) = 00 ~ 60
	_UINT32 nTimeValues[3];

	//Millisecond
	_UINT32 nMilliseconds;

	//Performance Counter
	_UINT32 nPerformanceCounters[2];
	//Format
	_PASCALSTRING strFormat;

}

SimpleTime;

////////////////////////////////////////////////////////////////////////////////
//
// Time constant and function definitions.
//
////////////////////////////////////////////////////////////////////////////////

#define MILLISECOND												1
#define SECOND													1000 * MILLISECOND
#define MINUTE													60 * SECOND
#define HOUR													60 * MINUTE
#define DAY														24 * HOUR
#define MONTH													30 * DAY
#define YEAR													365 * DAY

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _UINT32 GetMilliseconds();
extern _BOOL GetPerformanceCounters(_UINT32* lpPerformanceCounter);

extern _BOOL InitializeTime(SimpleTime* pTime);

extern _STRING FormatDate(SimpleTime* pTime,_STRING lpstrSplitter);
extern _STRING FormatTime(SimpleTime* pTime,_STRING lpstrSplitter);

extern _STRING GetCompactFormat(SimpleTime* pTime);
extern _STRING GetStandardFormat(SimpleTime* pTime);
extern _STRING GetRecorderFormat(SimpleTime* pTime);

extern _BOOL GetSMPPValidityPeriod(_INT32 nSecond,_STRING lpstrValidityPeriod);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
