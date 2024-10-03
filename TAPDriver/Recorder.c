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
// Initialize recorder.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeRecorder(SimpleRecorder* pRecorder)
{
#ifdef _DEBUG
	assert(pRecorder != NULL);
#endif

	//Clear log.
	memset(pRecorder,0,sizeof(SimpleRecorder));

	//Set trace id.
	pRecorder->nTraceID = 0;
	//Set locked.
	pRecorder->bLocked = _FALSE;

	//Initialize open time.
	InitializeTime(&pRecorder->timeOpen);
	//Set directory.
	strcpy(pRecorder->strDirectory,"");
	//Set file name.
	strcpy(pRecorder->strFileName,"");
	//Set file.
	pRecorder->lpFile = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize recorder.
//
////////////////////////////////////////////////////////////////////////////////

void UninitializeRecorder(SimpleRecorder* pRecorder)
{
#ifdef _DEBUG
	assert(pRecorder != NULL);
#endif

	//Check file.
	if(pRecorder->lpFile != NULL)
	{
		//Close file.
		fclose(pRecorder->lpFile);
		//Set NULL.
		pRecorder->lpFile = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get recorder file name.
//
////////////////////////////////////////////////////////////////////////////////

void GetRecorderFileName(SimpleRecorder* pRecorder,_STRING strFileName)
{
#ifdef _DEBUG
	assert(pRecorder != NULL);
#endif

	//Check trace id.
	if(pRecorder->nTraceID > 0)
	{
		//Get file name.
		sprintf(strFileName,"%s%s%08x.evt",
			pRecorder->strDirectory,GetFileDirectorySplitter(),pRecorder->nTraceID);
	}
	else
	{
		/*
		//Get file name.
		sprintf(strFileName,"%s%s%s.log",
			pRecorder->strDirectory,GetFileDirectorySplitter(),FormatDate(&pRecorder->timeOpen,""));
		*/
		strcpy(strFileName,"speednet.log");
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Open recorder.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenRecorder(SimpleRecorder* pRecorder)
{
#ifdef _DEBUG
	assert(pRecorder != NULL);
#endif

	//Check file.
	if(pRecorder->lpFile != NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::OpenRecorder : file has already been opened !");
#endif
		return _FALSE;
	}

	//Initialize open time.
	if(!InitializeTime(&pRecorder->timeOpen))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::OpenRecorder : fail to initialize open time !");
#endif
		return _FALSE;
	}

	//Get recorder file name.
	GetRecorderFileName(pRecorder,pRecorder->strFileName);

	//Try to open a log file.
	pRecorder->lpFile = fopen(pRecorder->strFileName,"a+");
	//Check result.
	if(pRecorder->lpFile == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::OpenRecorder : fail to open file !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Close recorder.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CloseRecorder(SimpleRecorder* pRecorder)
{
#ifdef _DEBUG
	assert(pRecorder != NULL);
#endif

	//Check log and file.
	if(pRecorder->lpFile == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::CloseRecorder : null log file !");
#endif
		return _FALSE;
	}

	//Close a log file.
	if(fclose(pRecorder->lpFile) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::CloseRecorder : fail to close file !");
#endif
		return _FALSE;
	}

	//Set NULL.
	pRecorder->lpFile = NULL;
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Record event.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RecordEvent(SimpleRecorder* pRecorder,_STRING lpstrEvent)
{
	//Current time.
	SimpleTime timeCurrent;

#ifdef _DEBUG
	assert(pRecorder != NULL && lpstrEvent != NULL);
#endif

	//Check event.
	if(strlen(lpstrEvent) <= 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::RecordEvent : empty event !");
#endif
		return _TRUE;
	}

	//Check file pionter.
	if(pRecorder->lpFile == NULL)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::RecordEvent : null file pointer !");
#endif
		return _FALSE;
	}

	//Initialize current time.
	if(!InitializeTime(&timeCurrent))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::RecordEvent : fail to initialize current time !");
#endif
		return _FALSE;
	}

	/*
	//Check date.
	if(timeCurrent.nDateValues[2] != pRecorder->timeOpen.nDateValues[2])
	{
		//Close recorder.
		if(!CloseRecorder(pRecorder))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Recorder::RecordEvent : fail to close recorder !");
#endif
			return _FALSE;
		}

		//Open recorder.
		if(!OpenRecorder(pRecorder))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Recorder::RecordEvent : fail to open recorder !");
#endif
			return _FALSE;
		}
	}
	*/

	//Write event time.
	if(PrintLine(pRecorder->lpFile,"%s",GetRecorderFormat(&timeCurrent)) <= 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::RecordEvent : fail to write event time !");
#endif
		return _FALSE;
	}
	//Write event.
	if(PrintLine(pRecorder->lpFile,"%s",lpstrEvent) <= 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Recorder::RecordEvent : fail to write event with new line !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
