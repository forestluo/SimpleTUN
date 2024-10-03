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
// They are mainly concert about the management of thread, synchronization, socket etc.
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
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS
typedef HANDLE												_LOCK;
#endif

//For linux.
#ifdef _REDHAT_LINUX
//Lock
typedef pthread_mutex_t										_LOCK;
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Initialize lock.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeLock(SimpleLock* pLock)
{
#ifdef _DEBUG
	assert(pLock != NULL);
#endif

	//Clear lock.
	memset(pLock,0,sizeof(SimpleLock));

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Create lock.
	pLock->lpLock = (_OBJECT)malloc(sizeof(CRITICAL_SECTION));
	//Check result.
	if(pLock->lpLock == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::InitializeLock : fail to create critical section !");
#endif
		return _FALSE;
	}
	//Initialize cirtical section.
	InitializeCriticalSection((LPCRITICAL_SECTION)pLock->lpLock);

#endif

//For linux
#ifdef _REDHAT_LINUX

	//Allocate memory.
	pLock->lpLock = (_OBJECT)malloc(sizeof(_LOCK));
	//Check result.
	if(pLock->lpLock == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::InitializeLock : fail to create mutex !");
#endif
		return _FALSE;
	}

	//Initialize lock.
	pthread_mutex_init((_LOCK *)pLock->lpLock,NULL);

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize lock.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UninitializeLock(SimpleLock* pLock)
{
#ifdef _DEBUG
	assert(pLock != NULL);
#endif

	//Check lock.
	if(pLock->lpLock == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::UninitializeLock : null lock !");
#endif
		return _FALSE;
	}

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Delete critical section.
	DeleteCriticalSection((LPCRITICAL_SECTION)pLock->lpLock);

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Destroy lock.
	if(pthread_mutex_destroy((_LOCK *)pLock->lpLock) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::UninitializeLock : fail to destroy mutex !");
#endif
		return _FALSE;
	}

#endif

	//Free lock.
	free(pLock->lpLock);
	//Set NULL.
	pLock->lpLock = NULL;
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Open lock.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenLock(SimpleLock* pLock)
{
#ifdef _DEBUG
	assert(pLock != NULL);
#endif

	//Check lock.
	if(pLock->lpLock == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::OpenLock : null lock !");
#endif
		return _FALSE;
	}

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Enter critical section.
	EnterCriticalSection((LPCRITICAL_SECTION)pLock->lpLock);

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Mutex lock.
	if(pthread_mutex_lock((_LOCK *)pLock->lpLock) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::OpenLock : fail to lock mutex !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Close lock.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CloseLock(SimpleLock* pLock)
{
#ifdef _DEBUG
	assert(pLock != NULL);
#endif

	//Check lock.
	if(pLock->lpLock == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::CloseLock : null lock !");
#endif
		return _FALSE;
	}

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Leave critical section.
	LeaveCriticalSection((LPCRITICAL_SECTION)pLock->lpLock);

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Unlock mutex.
	if(pthread_mutex_unlock((_LOCK *)pLock->lpLock) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Lock::CloseLock : fail to unlock mutex !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}
