#ifndef _SIMPLE_WATCH_H
#define _SIMPLE_WATCH_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleWatch
{
	//Start Time
	SimpleTime timeStart;
	//Stop Time
	SimpleTime timeStop;

	//Counter
	//When running loop, the counter would count the loop time.
	//It would like a heart beaten.
	//You should add the counter when finishing a loop.
	_UINT32 nCount;

	//Performance Counters
	_UINT32 nPerformanceCounters[3];

}

SimpleWatch;

////////////////////////////////////////////////////////////////////////////////
//
//	General functions
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeWatch(SimpleWatch* pWatch);

extern _BOOL StartWatch(SimpleWatch* pWatch);
extern _BOOL StopWatch(SimpleWatch* pWatch);

extern _STRING DumpWatch(_STRING lpstrFormat,SimpleWatch* pWatch);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
