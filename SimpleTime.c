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

#include <time.h>

////////////////////////////////////////////////////////////////////////////////
//
// Special including files
//
// Including the files for the specifal operation system.
//
// These including files are used for the specifal operation system.
// They are mainly concert about the management of thread, synchronization, socket etc.
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS
#include <windows.h>
#endif

//For linux
#ifdef _REDHAT_LINUX
#include <sys/time.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Retrieves the number of milliseconds.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetMilliseconds()
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Get tick count.
	return GetTickCount();

#endif

//For linux.
#ifdef _REDHAT_LINUX

	struct timeval current;
	struct timezone zone;

	//Get current.
	gettimeofday(&current,&zone);
	//Calculate millionsecond.
	return current.tv_sec * 1000 + current.tv_usec / 1000;

#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// Get performance counters.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetPerformanceCounters(_UINT32* lpPerformanceCounters)
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Large integer.
	LARGE_INTEGER largeCurrent;

#ifdef _DEBUG
	assert(lpPerformanceCounters != NULL);
#endif

	//Get current counter.
	if(QueryPerformanceCounter(&largeCurrent))
	{
		//Get high part.
		lpPerformanceCounters[0] = largeCurrent.HighPart;
		//Get lower part.
		lpPerformanceCounters[1] = largeCurrent.LowPart;
		//Return true.
		return _TRUE;
	}

#endif

//For linux.
#ifdef _REDHAT_LINUX

	struct timeval current;
	struct timezone zone;

	//Get current time.
	if(gettimeofday(&current,&zone) == _SUCCESS)
	{
		//Set high part.
		lpPerformanceCounters[0] = current.tv_sec;
		//Set lower part.
		lpPerformanceCounters[1] = current.tv_usec;
		//Return true.
		return _TRUE;
	}

#endif

#ifdef _DEBUG
	PrintLine(stderr,"Time::GetPerformanceCounters : fail to get performance counters !");
#endif
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize time.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeTime(SimpleTime* pTime)
{
	struct tm* pToday = NULL;
	time_t timenow = 0;

#ifdef _DEBUG
	assert(pTime != NULL);
#endif

	//Clear time.
	memset(pTime,0,sizeof(SimpleTime));

	//Get timenow.
	time(&timenow);
	//Get localtime.
	pToday = localtime(&timenow);
	//Check result.
	if(pToday == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Time::InitializeTime : fail to get local time !");
#endif
		return _FALSE;
	}

	//Get date values.
	pTime->nDateValues[0] = pToday->tm_year + 1900;
	pTime->nDateValues[1] = pToday->tm_mon + 1;
	pTime->nDateValues[2] = pToday->tm_mday;
	//Get time values.
	pTime->nTimeValues[0] = pToday->tm_hour;
	pTime->nTimeValues[1] = pToday->tm_min;
	pTime->nTimeValues[2] = pToday->tm_sec;

	//Get milliseconds.
	pTime->nMilliseconds = GetMilliseconds();

	//Get performance counters.
	if(!GetPerformanceCounters(pTime->nPerformanceCounters))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Time::InitializeTime : fail to get performance count !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get date format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING FormatDate(SimpleTime* pTime,_STRING lpstrSplitter)
{
#ifdef _DEBUG
	assert(pTime != NULL && lpstrSplitter != NULL);
#endif

	sprintf(pTime->strFormat,"%04d%s%02d%s%02d",
		pTime->nDateValues[0],lpstrSplitter,pTime->nDateValues[1],lpstrSplitter,pTime->nDateValues[2]);
	//Return format.
	return pTime->strFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get time format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING FormatTime(SimpleTime* pTime,_STRING lpstrSplitter)
{
#ifdef _DEBUG
	assert(pTime != NULL && lpstrSplitter != NULL);
#endif

	sprintf(pTime->strFormat,"%02d%s%02d%s%02d",
		pTime->nTimeValues[0],lpstrSplitter,pTime->nTimeValues[1],lpstrSplitter,pTime->nTimeValues[2]);
	//Return format.
	return pTime->strFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get compact format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetCompactFormat(SimpleTime* pTime)
{
#ifdef _DEBUG
	assert(pTime != NULL);
#endif

	sprintf(pTime->strFormat,"%04d%02d%02d%02d%02d%02d",
		pTime->nDateValues[0],pTime->nDateValues[1],pTime->nDateValues[2],
		pTime->nTimeValues[0],pTime->nTimeValues[1],pTime->nTimeValues[2]);
	//Return format.
	return pTime->strFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get standard format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetStandardFormat(SimpleTime* pTime)
{
#ifdef _DEBUG
	assert(pTime != NULL);
#endif

	sprintf(pTime->strFormat,"%04d-%02d-%02d %02d:%02d:%02d",
		pTime->nDateValues[0],pTime->nDateValues[1],pTime->nDateValues[2],
		pTime->nTimeValues[0],pTime->nTimeValues[1],pTime->nTimeValues[2]);
	//Return format.
	return pTime->strFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get Recorder format.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetRecorderFormat(SimpleTime* pTime)
{
#ifdef _DEBUG
	assert(pTime != NULL);
#endif

	sprintf(pTime->strFormat,"#%04d-%02d-%02d %02d:%02d:%02d>%08x:%08x>%u",
		pTime->nDateValues[0],pTime->nDateValues[1],pTime->nDateValues[2],
		pTime->nTimeValues[0],pTime->nTimeValues[1],pTime->nTimeValues[2],
		pTime->nPerformanceCounters[0],pTime->nPerformanceCounters[1],
		pTime->nMilliseconds);
	//Return format.
	return pTime->strFormat;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get SMPP validity period.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetSMPPValidityPeriod(_INT32 nSecond,_STRING lpstrValidityPeriod)
{
	SimpleTime future;

	struct tm* pToday = NULL;
	time_t timenow = 0;

#ifdef _DEBUG
	assert(lpstrValidityPeriod != NULL);
#endif

	//Clear time.
	memset(&future,0,sizeof(SimpleTime));

	//Get timenow.
	time(&timenow);
	//Add time.
	timenow += nSecond;

	//Get localtime.
	pToday = localtime(&timenow);
	//Check result.
	if(pToday == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Time::GetSMPPValidityPeriod : fail to get local time !");
#endif
		return _FALSE;
	}

	//Get date values.
	future.nDateValues[0] = (pToday->tm_year + 1900) % 100;
	future.nDateValues[1] = pToday->tm_mon + 1;
	future.nDateValues[2] = pToday->tm_mday;
	//Get time values.
	future.nTimeValues[0] = pToday->tm_hour;
	future.nTimeValues[1] = pToday->tm_min;
	future.nTimeValues[2] = pToday->tm_sec;

	//Format time.
	sprintf(lpstrValidityPeriod,"%02d%02d%02d%02d%02d%02d",
		future.nDateValues[0],future.nDateValues[1],future.nDateValues[2],
		future.nTimeValues[0],future.nTimeValues[1],future.nTimeValues[2]);
	//Return true.
	return _TRUE;
}
