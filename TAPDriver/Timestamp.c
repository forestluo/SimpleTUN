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
// Get timestamp comment.
//
////////////////////////////////////////////////////////////////////////////////

void GetTimestampComment(_PASCALSTRING strTimestamp,_UINT32 nTimestamp)
{
	//Timestamp is MMDDHHMMSS in DEC.
	_UINT32 nMonth,nDay,nHour,nMinute,nSecond;

	//Get month.
	nMonth = nTimestamp / 100000000;
	nTimestamp = nTimestamp % 100000000;
	//Get day.
	nDay = nTimestamp / 1000000;
	nTimestamp = nTimestamp % 1000000;
	//Get hour.
	nHour = nTimestamp / 10000;
	nTimestamp = nTimestamp % 10000;
	//Get minute.
	nMinute = nTimestamp / 100;
	//Get second.
	nSecond = nTimestamp % 100;

	//Convert into string.
	sprintf(strTimestamp,"%02d-%02d %02d:%02d:%02d",
		nMonth,nDay,nHour,nMinute,nSecond);
}

////////////////////////////////////////////////////////////////////////////////
//
// Format timestamp.
//
////////////////////////////////////////////////////////////////////////////////

void FormatTimestamp(_PASCALSTRING strTimestamp,_UINT32 nTimestamp)
{
	//Timestamp is MMDDHHMMSS in DEC.
	_UINT32 nMonth,nDay,nHour,nMinute,nSecond;

	//Get month.
	nMonth = nTimestamp / 100000000;
	nTimestamp = nTimestamp % 100000000;
	//Get day.
	nDay = nTimestamp / 1000000;
	nTimestamp = nTimestamp % 1000000;
	//Get hour.
	nHour = nTimestamp / 10000;
	nTimestamp = nTimestamp % 10000;
	//Get minute.
	nMinute = nTimestamp / 100;
	//Get second.
	nSecond = nTimestamp % 100;

	//Convert into string.
	sprintf(strTimestamp,"%02d%02d%02d%02d%02d",
		nMonth,nDay,nHour,nMinute,nSecond);
}

////////////////////////////////////////////////////////////////////////////////
//
// Scan timestamp.
//
////////////////////////////////////////////////////////////////////////////////

void ScanTimestamp(_PASCALSTRING strTimestamp,_UINT32* lpTimestamp)
{
	//Timestamp is MMDDHHMMSS in DEC.
	int nMonth = 0,nDay = 0,nHour = 0,nMinute = 0,nSecond = 0;

	//Scan month, day, hour, minute and second.
	sscanf(strTimestamp,"%02d%02d%02d%02d%02d",
		&nMonth,&nDay,&nHour,&nMinute,&nSecond);

	*lpTimestamp = nMonth * 100000000 +
		nDay * 1000000 + nHour * 10000 + nMinute * 100 + nSecond;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get current timestamp comment.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetCurrentTimestamp()
{
	SimpleTime timeCurrent;
	_PASCALSTRING strTimeCompactFormat;
	_UINT32 nTimestamp = 0;

	//Initialize current time.
	InitializeTime(&timeCurrent);
	//Get rid of the year.
	sprintf(strTimeCompactFormat,"%02d%02d%02d%02d%02d",
				timeCurrent.nDateValues[1],timeCurrent.nDateValues[2],
				timeCurrent.nTimeValues[0],timeCurrent.nTimeValues[1],timeCurrent.nTimeValues[2]);
	//Scan timestamp.
	ScanTimestamp(strTimeCompactFormat,&nTimestamp);

	return nTimestamp;
}
