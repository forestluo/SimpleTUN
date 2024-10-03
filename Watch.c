////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include "Global.h"

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

#define MAX_VALUE											0xFFFFFFFF

////////////////////////////////////////////////////////////////////////////////
//
// Initialize watch.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeWatch(SimpleWatch* pWatch)
{
#ifdef _DEBUG
	assert(pWatch != NULL);
#endif

	//CLear watch.
	memset(pWatch,0,sizeof(SimpleWatch));

	//Initialize start time.
	assert(InitializeTime(&pWatch->timeStart));
	//Initialize stop time.
	assert(InitializeTime(&pWatch->timeStop));

	//Set count.
	pWatch->nCount = 0;

	//Set performance counters.
	//Minimum
	pWatch->nPerformanceCounters[0] = MAX_VALUE;
	//Current
	pWatch->nPerformanceCounters[1] = MAX_VALUE;
	//Maximum
	pWatch->nPerformanceCounters[2] = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Start watch.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL StartWatch(SimpleWatch* pWatch)
{
#ifdef _DEBUG
	assert(pWatch != NULL);
#endif

	//Initialize start time.
	if(!InitializeTime(&pWatch->timeStart))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Watch::StartWatch : fail to initialize time !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Stop watch.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL StopWatch(SimpleWatch* pWatch)
{
#ifdef _DEBUG
	assert(pWatch != NULL);
#endif

	//Get current performance counter.
	pWatch->nPerformanceCounters[1] = pWatch->timeStop.nPerformanceCounters[1] -
		pWatch->timeStart.nPerformanceCounters[1];
	//Set minimum consumed.
	if(pWatch->nPerformanceCounters[1] < pWatch->nPerformanceCounters[0])
	{
		pWatch->nPerformanceCounters[0] = pWatch->nPerformanceCounters[1];
	}
	//Set maximum consumed.
	if(pWatch->nPerformanceCounters[1] > pWatch->nPerformanceCounters[2])
	{
		pWatch->nPerformanceCounters[2] = pWatch->nPerformanceCounters[1];
	}
	//Add count.
	pWatch->nCount ++;

	//Initialize stop time.
	if(!InitializeTime(&pWatch->timeStop))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Watch::StopWatch : fail to initialize time !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump watch.
//
////////////////////////////////////////////////////////////////////////////////

_STRING DumpWatch(_STRING lpstrFormat,SimpleWatch* pWatch)
{
#ifdef _DEBUG
	assert(lpstrFormat != NULL && pWatch != NULL);
#endif

	//Beging format.
	lpstrFormat = FormatLine(lpstrFormat,"Watch::DumpWatch : show data !");
	//Dump start time.
	lpstrFormat = FormatLine(lpstrFormat,"\ttimeStart = %u [%s]",
		pWatch->timeStart.nMilliseconds,GetStandardFormat(&pWatch->timeStart));
	//Dump stop time.
	lpstrFormat = FormatLine(lpstrFormat,"\ttimeStop = %u [%s]",
		pWatch->timeStart.nMilliseconds,GetStandardFormat(&pWatch->timeStop));
	//Dump count.
	lpstrFormat = FormatLine(lpstrFormat,"\tnCount = %u",
		pWatch->nCount);
	//Dump performance counter.
	lpstrFormat = FormatLine(lpstrFormat,"\tnPerformanceCounters[minimum,current,maximum] = %u,%u,%u",
		pWatch->nPerformanceCounters[0],pWatch->nPerformanceCounters[1],pWatch->nPerformanceCounters[2]);
	//Return format.
	return lpstrFormat;
}
