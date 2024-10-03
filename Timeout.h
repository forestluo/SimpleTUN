#ifndef _SIMPLE_TIMEOUT_H
#define _SIMPLE_TIMEOUT_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Never Timeout
#define NEVER_TIMEOUT											0xFFFFFFFF

typedef struct tagSimpleTimeout
{
	//Open Time
	SimpleTime timeOpen;

	//Last (Millisecond)
	_UINT32 timeLast;
	//Consumed (Millisecond)
	_UINT32 timeConsumed;

}

SimpleTimeout;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeTimeout(SimpleTimeout* pTimeout);

extern _BOOL IsTimeout(SimpleTimeout* pTimeout);
extern void ResetTimeout(SimpleTimeout* pTimeout);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
