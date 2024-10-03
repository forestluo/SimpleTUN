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

//ANSI C standard.
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//Global log.
static SimpleLog theLog;

////////////////////////////////////////////////////////////////////////////////
//
// Get event trace id.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetEventTraceID(_INT32* lpTraceID)
{
	//Open lock.
	if(!OpenLock(&theLog.lock))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::GetEventTraceID : fail to open lock !");
#endif
		return _FALSE;
	}

	//Get unique trace id.
	*lpTraceID = theLog.nSequence;
	//Add sequence.
	theLog.nSequence = (theLog.nSequence ++) & 0x7FFFFFFF;

	//Close lock.
	if(!CloseLock(&theLog.lock))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::GetEventTraceID : fail to close lock !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Trace event.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL TraceEvent(_INT32 nTraceID,_STRING lpstrEvent)
{
	_PASCALSTRING strName;
	FILE* pFile;

	//Current time.
	SimpleTime timeCurrent;

#ifdef _DEBUG
	assert(lpstrEvent != NULL);
#endif

	//Get file name.
	sprintf(strName,"%s%s%08x.evt",
		theLog.recorder.strDirectory,GetFileDirectorySplitter(),nTraceID);
	//Open file.
	pFile = fopen(strName,"a");
	//Check result.
	if(pFile != NULL)
	{
		//Initialize current time.
		if(!InitializeTime(&timeCurrent))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::TraceEvent : fail to initialize time !");
#endif
		}
		//Write event time.
		if(PrintLine(pFile,"%s",GetRecorderFormat(&timeCurrent)) <= 0)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::TraceEvent : fail to write event time !");
#endif
		}
		//Print a new line.
		if(PrintLine(pFile,lpstrEvent) <= 0)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::TraceEvent : fail to write event !");
#endif
		}
		//Close file.
		fclose(pFile);
		//Return true.
		return _TRUE;
	}

#ifdef _DEBUG
	PrintLine(stderr,"Log::TraceEvent : fail to open file !");
#endif
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Combinate event.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CombinateEvent(_INT32 nHeadTraceID,_INT32 nTailTraceID)
{
	_PASCALSTRING strHeadFile;
	_PASCALSTRING strTailFile;

#ifdef _DEBUG
	assert(nHeadTraceID > 0 && nTailTraceID > 0);
	assert(nHeadTraceID != nTailTraceID);
#endif

	//Get head file name.
	sprintf(strHeadFile,"%s%s%08x.evt",
		theLog.recorder.strDirectory,GetFileDirectorySplitter(),nHeadTraceID);
	//Get tail file name.
	sprintf(strTailFile,"%s%s%08x.evt",
		theLog.recorder.strDirectory,GetFileDirectorySplitter(),nTailTraceID);			
	//Combinate event file.
	if(!CombinateFile(strHeadFile,strTailFile))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::CombinateEvent : fail to append event file !");
#endif
		return _FALSE;
	}
	//Remove packet file.
	if(!RemoveFile(strTailFile))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::CombinateEvent : fail to remove tail event file !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize log.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeLog(_STRING lpstrDirectory,_UINT32 nRequests)
{
#ifdef _DEBUG
	assert(lpstrDirectory != NULL && strlen(lpstrDirectory) > 0);
#endif

	//Check directory.
	if(!IsFileDirectoryExist(lpstrDirectory))
	{
		//Create directory.
		if(!CreateFileDirectory(lpstrDirectory))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::InitializeLog : fail to create directory !");
#endif
			return _FALSE;
		}
	}

	//Clear log.
	memset(&theLog,0,sizeof(SimpleLog));

	//Set requests.
	theLog.nRequests = nRequests;

	//Initialize lock.
	if(!InitializeLock(&theLog.lock))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::InitializeLog : fail to initialize lock !");
#endif
		return _FALSE;
	}

	//Initialize recorder.
	InitializeRecorder(&theLog.recorder);
	//Set directory.
	strcpy(theLog.recorder.strDirectory,lpstrDirectory);

	//Open recorder.
	if(!OpenRecorder(&theLog.recorder))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::InitializeLog : fail to open recorder !");
#endif
		return _FALSE;
	}

	//Set sequence.
	theLog.nSequence = 1;
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize log.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UninitializeLog()
{
	//Close recorder.
	if(!CloseRecorder(&theLog.recorder))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::UninitializeLog : fail to close recorder !");
#endif
	}
	//Uninitialize recorder.
	UninitializeRecorder(&theLog.recorder);

	//Uninitialize lock.
	if(!UninitializeLock(&theLog.lock))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Log::UninitializeLog : fail to uninitialize lock !");
#endif
		return _FALSE;
	}
	//Return false.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is log requested.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsLogRequested(_UINT32 nRequests)
{
	//Check requests.
	if(theLog.nRequests & nRequests)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Log requested event.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LogRequestedEvent(_STRING lpstrEvent,_UINT32 nRequests)
{
	_BOOL bResult = _TRUE;

#ifdef _DEBUG
	assert(lpstrEvent != NULL);
#endif

	//Check requests.
	if(IsLogRequested(nRequests))
	{
		//Print event to screen.
		printf("%s\r\n",lpstrEvent);

		//Open Lock.
		if(!OpenLock(&theLog.lock))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::LogRequestedEvent : fail to open lock !");
#endif
			return _FALSE;
		}

		//Recorder event.
		bResult = RecordEvent(&theLog.recorder,lpstrEvent);

		//Close Lock.
		if(!CloseLock(&theLog.lock))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Log::LogRequestedEvent : fail to close lock !");
#endif
			return _FALSE;
		}
	}
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Log requested format event.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LogRequestedFormat(_UINT32 nRequests,_STRING lpstrEvent,...)
{
	//Format block.
	_BLOCK blockFormated;
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpstrEvent != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Initialize variable arguments.
	va_start(argp,lpstrEvent);
	//Print variable arguments.
	vsprintf(blockFormated,lpstrEvent,argp);
	//Reset variable arguments.
	va_end(argp);

	//Return result.
	return LogRequestedEvent((_STRING)blockFormated,nRequests);
}