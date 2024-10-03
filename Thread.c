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
// They are mainly concert about the management of pThread, synchronization, socket etc.
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS
#include <windows.h>
#include <process.h>
#endif

//For linux.
#ifdef _REDHAT_LINUX
#include <pthread.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//Default Wait Time
#define DEFAULT_WAIT_TIME									60000

////////////////////////////////////////////////////////////////////////////////
//
// Default process.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL DefaultProcess(_OBJECT lpObject)
{
#ifdef _DEBUG
	assert(lpObject != NULL);
#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Standard processing.
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS

//Process
DWORD WINAPI StandardProcess(LPVOID argument)

#endif

//For linux.
#ifdef _REDHAT_LINUX

//Process
void* StandardProcess(void* argument)

#endif
{
	SimpleThread* pThread;

#ifdef _DEBUG
	assert(argument != NULL);
#endif

	//Convert argument into thread.
	pThread = (SimpleThread *)argument;

	//When coming into the main loop, you should set the status to 'running'.
	//Otherwise, the wait() function would wait until timeout.
	pThread->nStatus = THREAD_RUNNING;

#ifdef _DEBUG
	//Dump thread.
	PrintLine(stdout,"Process::%s : running !",pThread->strName);
#endif

	//Do while thread is running.
	while(IsThreadRunning(pThread))
	{
		//When being the loop, start the stopwatch.

		StartWatch(&pThread->watch);

#ifdef _DEBUG
		assert(pThread->lpProcess != NULL);
#endif
		////////////////////////////////////
		//
		// You can add the program here ...
		//
		////////////////////////////////////
		
		if(pThread->bSwitch && !pThread->lpProcess(pThread->lpObject))
		{
#ifdef _DEBUG
			//Dump thread.
			PrintLine(stderr,"Process::%s : breaked !",pThread->strName);
#endif
			break;
		}

		//When end the loop, stop the stopwatch.
		StopWatch(&pThread->watch);

		//Sleep
		SleepMilliseconds(pThread->nWaitTime);
	}

#ifdef _DEBUG
	//Dump thread.
	PrintLine(stdout,"Process::%s : stopped !",pThread->strName);
#endif

	//When exit the main loop, you should set the status to 'stopped'.
	//Otherwise, the wait() function would wait until timeout.
	pThread->nStatus = THREAD_STOPPED;

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//End thread
	return 0;

#endif

//For linux.
#ifdef _REDHAT_LINUX

	return NULL;

#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize thread.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeThread(SimpleThread* pThread)
{
#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Clear thread.
	memset(pThread,0,sizeof(SimpleThread));

	//Set name.
	strcpy(pThread->strName,"Default Process");

	//Initialize watch.
	InitializeWatch(&pThread->watch);

	//Set sequence.
	pThread->nSequence = 1;
	//Set wait time.
	pThread->nWaitTime = MILLISECOND;

	//Set switch.
	pThread->bSwitch = _TRUE;
	//Set process.
	pThread->lpProcess = DefaultProcess;
	//Set object.
	pThread->lpObject = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is thread running.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsThreadRunning(SimpleThread* pThread)
{
#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Check status.
	if(pThread->nStatus == THREAD_RUNNING)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is thread stopped.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsThreadStopped(SimpleThread* pThread)
{
#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Check status.
	if(pThread->nStatus == THREAD_STOPPED)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get thread sequence.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 GetThreadSequence(SimpleThread* pThread)
{
	_INT32 nSequence;

#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	nSequence = pThread->nSequence;
	//Add sequence.
	pThread->nSequence ++;
	//Check sequence.
	if(pThread->nSequence >= MAX_SEQUENCE)
	{
		//Reset sequence.
		pThread->nSequence = 1;
	}
	//Return sequence.
	return nSequence;
}

////////////////////////////////////////////////////////////////////////////////
//
// Startup a thread.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL StartupThread(SimpleThread* pThread)
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Thread id.
	DWORD dwThreadId;
	//Handle.
	HANDLE handle;

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Thread.
	pthread_t thread;
	//Attribute
	pthread_attr_t attribute;

#endif

#ifdef _DEBUG
	assert(pThread != NULL && pThread->lpProcess != NULL);
#endif

	//Check current status.
	if(pThread->nStatus == THREAD_ACCELERATED || pThread->nStatus == THREAD_RUNNING)
	{
		//If the thread has been accelerated or is running, then return.
#ifdef _DEBUG
		PrintLine(stderr,"Process::StartupThread : thread has already startup !");
#endif
		return _TRUE;
	}

	//Set status to be accelerated.
	pThread->nStatus = THREAD_ACCELERATED;

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Call CreateThread() function.
    handle = CreateThread(
						NULL,			// no security attributes
						0,				// use default stack size
						StandardProcess,// thread function
						pThread,		// argument to thread function
						0,				// use default creation flags
						&dwThreadId);	// returns the pThread identifier
 	//Check result.
	if(handle == NULL)

#endif

//For linux
#ifdef _REDHAT_LINUX

	//Initialize thread.
	memset(&thread,0,sizeof(pthread_t));
	//Initialize attribute.
	pthread_attr_init(&attribute);
	
	//Call pthread_create() function.
	if(pthread_create(&thread,&attribute,StandardProcess,pThread) != 0)

#endif                                                                           	

	{
#ifdef _DEBUG
		//Dump thread.
		PrintLine(stderr,"Process::StartupThread : fail to startup %s !",pThread->strName);
#endif
		//Set current status as stopped.
		pThread->nStatus = THREAD_STOPPED;
		//Return false.
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Shutdown a thread.
//
////////////////////////////////////////////////////////////////////////////////

void ShutdownThread(SimpleThread* pThread)
{
#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Check the status.
	if(pThread->nStatus != THREAD_DECELERATED && pThread->nStatus != THREAD_STOPPED)
	{
		//Set status to be decelerated.
		pThread->nStatus = THREAD_DECELERATED;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Switch a thread.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SwitchThread(SimpleThread* pThread,_BOOL bSwitch)
{
	_UINT32 nCount;
	SimpleTimeout timeout;

#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Get last count.
	nCount = pThread->watch.nCount;
	//Initialize timeout.
	InitializeTimeout(&timeout);
	//Set timeout.
	timeout.timeConsumed = DEFAULT_WAIT_TIME;

	//Set switch.
	pThread->bSwitch = bSwitch;
	//Loop while the count still equals former value.
	while(nCount == pThread->watch.nCount)
	{
		//If the checking timeout, exit at once.
		if(IsTimeout(&timeout))
		{
#ifdef _DEBUG
			//Dump thread.
			PrintLine(stderr,"Process::SwitchThread : %s pulse timeout !",pThread->strName);
#endif
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Wait a thread.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WaitThread(SimpleThread* pThread)
{
	_UINT32 nStatus;
	SimpleTimeout timeout;

#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Get the current status of the pThread.
	nStatus = pThread->nStatus;
	//If pThread has already stopped or is running the status would not change, so return right now.
	if(nStatus == THREAD_STOPPED || nStatus == THREAD_RUNNING)
	{
		//Return true.
		return _TRUE;
	}

	//Initialize timeout.
	InitializeTimeout(&timeout);
	//Set timeout.
	timeout.timeConsumed = DEFAULT_WAIT_TIME;

	//Loop when the status still equals former value.
	while(pThread->nStatus == nStatus)
	{
		//If wait for a long time, the loop would be terminated.
		if(IsTimeout(&timeout))
		{
#ifdef _DEBUG
			//Dump thread.
			PrintLine(stderr,"Process::WaitThread : %s waiting timeout !",pThread->strName);
#endif
			//Set flag.
			return _FALSE;
		}

		//Sleep
		SleepMilliseconds(pThread->nWaitTime);
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Check thread pulse.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CheckThreadPulse(SimpleThread* pThread)
{
	_UINT32 nCount;
	SimpleTimeout timeout;

#ifdef _DEBUG
	assert(pThread != NULL);
#endif

	//Get last count.
	nCount = pThread->watch.nCount;
	//Initialize timeout.
	InitializeTimeout(&timeout);
	//Set timeout.
	timeout.timeConsumed = DEFAULT_WAIT_TIME;

	//Loop while the count still equals former value.
	while(nCount == pThread->watch.nCount)
	{
		//If the checking timeout, exit at once.
		if(IsTimeout(&timeout))
		{
#ifdef _DEBUG
			//Dump thread.
			PrintLine(stderr,"Process::CheckThreadPulse : %s pulse timeout !",pThread->strName);
#endif
			return _FALSE;
		}

		//Sleep
		SleepMilliseconds(pThread->nWaitTime);
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get thread status comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetThreadStatusComment(_UINT32 nStatus)
{
	//Check status.
	switch(nStatus)
	{
	case THREAD_STOPPED:
		return "stopped";
	case THREAD_ACCELERATED:
		return "accelerated";
	case THREAD_RUNNING:
		return "running";
	case THREAD_DECELERATED:
		return "decelerated";
	default:;
	}
	//Return unknow.
	return "unknow";
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump thread.
//
////////////////////////////////////////////////////////////////////////////////

_STRING DumpThread(_STRING lpstrFormat,SimpleThread* pThread)
{
#ifdef _DEBUG
	assert(lpstrFormat != NULL && pThread != NULL);
#endif

	lpstrFormat = FormatLine(lpstrFormat,"Thread::DumpThread : show data !");
	//Dump name.
	lpstrFormat = FormatLine(lpstrFormat,"\tstrName = \"%s\"",
		pThread->strName);
	//Dump status.
	lpstrFormat = FormatLine(lpstrFormat,"\tnStatus = 0x%02x [%s]",
		pThread->nStatus,GetThreadStatusComment(pThread->nStatus));
	//Dump wait time.
	lpstrFormat = FormatLine(lpstrFormat,"\tnWaitTime = %u",
		pThread->nWaitTime);
	//Dump sequence.
	lpstrFormat = FormatLine(lpstrFormat,"\tnSequence = 0x%08x",
		pThread->nSequence);
	//Dump thread.
	lpstrFormat = FormatLine(lpstrFormat,"\tlpProcess = 0x%p",
		pThread->lpProcess);
	//Dump object.
	lpstrFormat = FormatLine(lpstrFormat,"\tlpObject = 0x%p",
		pThread->lpObject);
	//Dump watch.
	lpstrFormat = DumpWatch(lpstrFormat,&pThread->watch);
	//Return format.
	return lpstrFormat;
}
