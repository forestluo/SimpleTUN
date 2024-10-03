#ifndef _SIMPLE_THREAD_H
#define _SIMPLE_THREAD_H

////////////////////////////////////////////////////////////////////////////////
//
// External definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Process
typedef _BOOL												(* _PROCESS)(_OBJECT);

//Accerelated
#define THREAD_ACCELERATED									0x00000001
//Running
#define THREAD_RUNNING										0x00000002
//Decelerated
#define THREAD_DECELERATED									0x00000003
//Stopped
#define THREAD_STOPPED										0x00000000

//Max Sequence
#define MAX_SEQUENCE										0x7FFFFFFF

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleThread
{
	//Name
	_PASCALSTRING strName;

	//Status
	//Thread Life Cycle : accelerated, running, decelerated and stopped.
	_UINT32 nStatus;
	//Watch
	SimpleWatch watch;
	//Wait Time (Millisecond)
	_UINT32 nWaitTime;

	//Sequence
	_INT32 nSequence;

	//Switch
	//Process ON or OFF.
	_BOOL bSwitch;
	//Process
	_PROCESS lpProcess;
	//Object
	_OBJECT lpObject;

}

SimpleThread;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeThread(SimpleThread* pThread);

extern _BOOL IsThreadRunning(SimpleThread* pThread);
extern _BOOL IsThreadStopped(SimpleThread* pThread);

extern _INT32 GetThreadSequence(SimpleThread* pThead);

extern _BOOL StartupThread(SimpleThread* pThread);
extern void ShutdownThread(SimpleThread* pThread);

extern _BOOL SwitchThread(SimpleThread* pThread,_BOOL bSwitch);

extern _BOOL WaitThread(SimpleThread* pThread);
extern _BOOL CheckThreadPulse(SimpleThread* pThread);

extern _STRING GetThreadStatusComment(_UINT32 nStatus);
extern _STRING DumpThread(_STRING lpstrFomrat,SimpleThread* pThread);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
