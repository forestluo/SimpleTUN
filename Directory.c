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
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//Invalid Handle
#define INVALID_HANDLE											(_UINT32)-1L

////////////////////////////////////////////////////////////////////////////////
//
// Special including files.
//
// Including the files for the specifal operation system.
//
// These including files are used for the specifal operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include <time.h>

//For windows.
#ifdef _MICROSOFT_WINDOWS
#include <direct.h>
#include <io.h>
#include <windows.h>
#endif

//For linux.
#ifdef _REDHAT_LINUX
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Home directory.
//
// Home directory is the working directory of the system.
//
////////////////////////////////////////////////////////////////////////////////

static _PASCALSTRING theHomeDirectory;

////////////////////////////////////////////////////////////////////////////////
//
// Get normal file size.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetNormalFileSize(_STRING lpstrFileName)
{
	_UINT32 nSize = 0;

//For windows.
#ifdef _MICROSOFT_WINDOWS

    struct _finddata_t file;
    _UINT32 handle;

#endif

//For linux.
#ifdef _REDHAT_LINUX

	struct stat file;

#endif

#ifdef _DEBUG
	assert(lpstrFileName != NULL);
#endif

//For windows.
#ifdef _MICROSOFT_WINDOWS

    //Try to find fist file.
	handle = (_UINT32)_findfirst(lpstrFileName,&file);
	//Check result.
	if(handle != INVALID_HANDLE)
	{
		//Get size.
		nSize = file.size;
		//Close find.
		_findclose(handle);
	}

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Get file status.
	if(stat(lpstrFileName,&file) != _FAILURE)
	{
		//Get size.
		nSize = file.st_size;
	}

#endif
	//Return size.
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get normal file Time.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetNormalFileTime(_STRING lpstrFileName,SimpleTime* pTime)
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

    struct _finddata_t file;
    _UINT32 handle;

	struct tm* pToday = NULL;

#endif

#ifdef _DEBUG
	assert(lpstrFileName != NULL && pTime != NULL);
#endif

//For windows.
#ifdef _MICROSOFT_WINDOWS

    //Try to find fist file.
	handle = (_UINT32)_findfirst(lpstrFileName,&file);
	//Check result.
	if(handle != INVALID_HANDLE)
	{
		//Get localtime.
		pToday = localtime(&file.time_write);
		//Check result.
		if(pToday == NULL)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Directory::GetNormalFileTime : fail to get local time !");
#endif
			return _FALSE;
		}

		//Get date values.
		pTime->nDateValues[0] = pToday->tm_year + 1900;
		pTime->nDateValues[1] = pToday->tm_mon + 1;
		pTime->nDateValues[2] = pToday->tm_mday;
		//Get time values.
		pTime->nTimeValues[0] = pToday->tm_hour;
		pTime->nTimeValues[1] = pToday->tm_min;
		pTime->nTimeValues[2] = pToday->tm_sec;

		//Close find.
		_findclose(handle);

		return _TRUE;
	}
#endif

	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Rename file.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RenameFile(_STRING lpstrSource,_STRING lpstrDestination)
{
#ifdef _DEBUG
	assert(lpstrSource != NULL && lpstrDestination != NULL);
#endif

	//Rename file name.
	if(rename(lpstrSource,lpstrDestination) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Directory::RenameFile : fail to write head file !");
#endif
		return _FALSE;
	}

	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Combinate file.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CombinateFile(_STRING lpstrHeadFile,_STRING lpstrTailFile)
{
	_BOOL bResult = _TRUE;

	_BLOCK block;
	_UINT32 nBytesRead;

	FILE* pHeadFile;
	FILE* pTailFile;

#ifdef _DEBUG
	assert(lpstrHeadFile != NULL && lpstrTailFile != NULL);
#endif

	//Open head file.
	pHeadFile = fopen(lpstrHeadFile,"a+");
	//Check result.
	if(pHeadFile != NULL)
	{
		//Open tail file.
		pTailFile = fopen(lpstrTailFile,"r");
		//Check result.
		if(pTailFile != NULL)
		{
			//Copy bytes.
			do
			{
				//Read from tail file.
				nBytesRead = (_UINT32)fread(block,sizeof(_BYTE),BLOCK_SIZE,pTailFile);
				//Check result.
				if(nBytesRead > 0)
				{
					//Write file.
					if(fwrite(block,sizeof(_BYTE),nBytesRead,pHeadFile) != nBytesRead)
					{
#ifdef _DEBUG
						PrintLine(stderr,"Directory::CombinateFile : fail to write head file !");
#endif
						//Set reuslt.
						bResult = _FALSE;

						break;
					}
				}

			}while(nBytesRead == BLOCK_SIZE);

			//Close tail file.
			if(fclose(pTailFile) != 0)
			{
#ifdef _DEBUG
				PrintLine(stderr,"Directory::CombinateFile : fail to close tail file !");
#endif
				//Set result.
				bResult = _FALSE;
			}
		}
		else
		{
#ifdef _DEBUG
			PrintLine(stderr,"Directory::CombinateFile : fail to open tail file !");
#endif
			//Set result.
			bResult = _FALSE;
		}

		//Close head file.
		if(fclose(pHeadFile) != 0)
		{
#ifdef _DEBUG
			PrintLine(stderr,"Directory::CombinateFile : fail to close head file !");
#endif
			//Set result.
			bResult = _FALSE;
		}
	}
	else
	{
#ifdef _DEBUG
		PrintLine(stderr,"Directory::CombinateFile : fail to open head file !");
#endif
		//Set result.
		bResult = _FALSE;
	}

	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove file.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RemoveFile(_STRING lpstrFileName)
{
#ifdef _DEBUG
	assert(lpstrFileName != NULL);
#endif

	//Remove file.
	if(remove(lpstrFileName) != 0)
	{
#ifdef _DEBUG
		LogRequestedEvent("Directory::RemoveFile : fail to remove file !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove files.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL RemoveFiles(_STRING lpstrDirectory,_STRING lpstrExtensionName)
{
	_BOOL bResult = _TRUE;
	_PASCALSTRING strName;

//For windows.
#ifdef _MICROSOFT_WINDOWS

	struct _finddata_t data;
    _UINT32 handle;

#endif

//For linux.
#ifdef _REDHAT_LINUX

	DIR* pDirectory = NULL;
	struct dirent* pEntry;

#endif

#ifdef _DEBUG
	assert(lpstrDirectory != NULL);
#endif

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Get name.
	sprintf(strName,"%s%s*.%s",
		lpstrDirectory,GetFileDirectorySplitter(),lpstrExtensionName);

	//Find first file.
	handle = (_UINT32)_findfirst(strName,&data);
	//Check result.
	if(handle != INVALID_HANDLE)
	{
		//Find next file.
		do
		{
			//Check file name.
			if(strcmp(data.name,".") == 0 || strcmp(data.name,"..") == 0)
			{
				continue;
			}

			//Copy file name.
			sprintf(strName,"%s%s%s",
				lpstrDirectory,GetFileDirectorySplitter(),data.name);
			//Remove file.
			if(!RemoveFile(strName))
			{
#ifdef _DEBUG
				LogRequestedEvent("Directory::RemoveFiles : fail to remove file !",
					LOG_PACKET | LOG_EXCEPTION);
#endif
				//Set result.
				bResult = _FALSE;

				break;
			}

		}while(_findnext(handle,&data) == 0);

		//Close the handle.
		_findclose(handle);
	}

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Open directory.
	pDirectory = opendir(lpstrDirectory);
	//Check result.
	if(pDirectory != NULL)
	{
		//Read entry.
		while((pEntry = readdir(pDirectory)) != NULL)
		{
			//Check file extension.
			if(strrchr(pEntry->d_name,'.') == NULL)
			{
				//File has its specified extension.
				continue;
			}

			//Check file extension.
			if(strcmp(strrchr(pEntry->d_name,'.'),lpstrExtensionName) != 0)
			{
				continue;
			}

			//Copy file name.
			sprintf(strName,"%s%s%s",
				lpstrDirectory,GetFileDirectorySplitter(),pEntry->d_name);
		
			//Remove file.
			if(!RemoveFile(strName))
			{
#ifdef _DEBUG
				LogRequestedEvent("Directory::RemoveFiles : fail to remove file !",
					LOG_PACKET | LOG_EXCEPTION);
#endif
				//Set result.
				bResult = _FALSE;

				break;
			}
		}

		//Close directory.
		if(!closedir(pDirectory) == _FAILURE)
		{
#ifdef _DEBUG
			LogRequestedEvent("Directory::RemoveFiles : fail to close directory !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			//Set result.
			bResult = _FALSE;
		}
	}

#endif
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get file directory splitter.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetFileDirectorySplitter()
{
//For windows.
#ifdef _MICROSOFT_WINDOWS
	return "\\";
#endif

//For linux
#ifdef _REDHAT_LINUX
	return "/";
#endif

#ifdef _DEBUG
	PrintLine(stderr,"Directory::GetFileDirectorySplitter : file directory undefined !");
#endif
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Change file directory.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ChangeFileDirectory(_STRING lpstrDirectory)
{
#ifdef _DEBUG
	assert(lpstrDirectory != NULL);
#endif

	//Change current directory.
	if(chdir(lpstrDirectory) != 0)
	{
#ifdef _DEBUG
		//PrintLine(stderr,"Directory::ChangeFileDirectory : fail to change file directory !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Create file directory.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CreateFileDirectory(_STRING lpstrDirectory)
{
#ifdef _DEBUG
	assert(lpstrDirectory != NULL);
#endif

//For windows.
#ifdef _MICROSOFT_WINDOWS
	//Make directory.
	if(mkdir(lpstrDirectory) != 0)
#endif
//For linux.
#ifdef _REDHAT_LINUX
	//Make directory
	if(mkdir(lpstrDirectory,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
#endif
	{
#ifdef _DEBUG
		//PrintLine(stderr,"Directory::CreateFileDirectory : fail to create file directory !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove file directory.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RemoveFileDirectory(_STRING lpstrDirectory)
{
#ifdef _DEBUG
	assert(lpstrDirectory != NULL);
#endif

	//Remove directory.
	if(rmdir(lpstrDirectory) != 0)
	{
#ifdef _DEBUG
		//PrintLine(stderr,"Directory::RemoveFileDirectory : fail to remove file directory !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get file directory.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetFileDirectory(_PASCALSTRING strDirectory)
{
	//Get directory.
	if(getcwd(strDirectory,PASCAL_STRING_LENGTH) == NULL)
	{
#ifdef _DEBUG
		//PrintLine(stderr,"Directory::GetFileDirectory : fail to get file directory !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get home directory.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetHomeDirectory()
{
	//Return home directory.
	return theHomeDirectory;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set home directory.
//
////////////////////////////////////////////////////////////////////////////////

void SetHomeDirectory(_STRING lpstrDirectory)
{
#ifdef _DEBUG
	assert(lpstrDirectory != NULL);
#endif

	//Set home directory.
	strcpy(theHomeDirectory,lpstrDirectory);
}

////////////////////////////////////////////////////////////////////////////////
//
// Return home directory.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ReturnHomeDirectory()
{
	//Change to home.
	if(!ChangeFileDirectory(theHomeDirectory))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Directory::ReturnHomeDirectory : fail to change home directory !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
