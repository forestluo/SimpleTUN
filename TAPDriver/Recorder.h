#ifndef _SIMPLE_RECORDER_H
#define _SIMPLE_RECORDER_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleRecorder
{
	//Trace ID
	_INT32 nTraceID;
	//Locked
	_BOOL bLocked;

	//Open Time
	SimpleTime timeOpen;
	//Directory
	_PASCALSTRING strDirectory;
	//File Name
	_PASCALSTRING strFileName;

	//File
	FILE* lpFile;
}

SimpleRecorder;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeRecorder(SimpleRecorder* pRecorder);
extern void UninitializeRecorder(SimpleRecorder* pRecorder);

extern _BOOL OpenRecorder(SimpleRecorder* pRecorder);
extern _BOOL CloseRecorder(SimpleRecorder* pRecorder);

extern _BOOL RecordEvent(SimpleRecorder* pRecorder,_STRING lpstrEvent);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
