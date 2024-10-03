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
// Initialize timeout.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeTimeout(SimpleTimeout* pTimeout)
{
#ifdef _DEBUG
	assert(pTimeout != NULL);
#endif

	//Clear timeout.
	memset(pTimeout,0,sizeof(SimpleTimeout));

	//Initialize open time.
	assert(InitializeTime(&pTimeout->timeOpen));

	//Set last time.
	pTimeout->timeLast = GetMilliseconds();
	//Set consumed time.
	pTimeout->timeConsumed = NEVER_TIMEOUT;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is timeout.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsTimeout(SimpleTimeout* pTimeout)
{
#ifdef _DEBUG
	assert(pTimeout != NULL);
#endif

	//Check consumed time.
	if(pTimeout->timeConsumed != NEVER_TIMEOUT)
	{
		//Check timeout.
		if(GetMilliseconds() >= (pTimeout->timeLast + pTimeout->timeConsumed))
		{
			return _TRUE;
		}
	}

	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Reset timeout.
//
////////////////////////////////////////////////////////////////////////////////

void ResetTimeout(SimpleTimeout* pTimeout)
{
#ifdef _DEBUG
	assert(pTimeout != NULL);
#endif

	//Set last time.
	pTimeout->timeLast = GetMilliseconds();
}
