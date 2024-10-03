#ifndef _SIMPLE_DIRECTORY_H
#define _SIMPLE_DIRECTORY_H

////////////////////////////////////////////////////////////////////////////////
//
// General file functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _UINT32 GetNormalFileSize(_STRING lpstrFileName);
extern _BOOL GetNormalFileTime(_STRING lpstrFileName,SimpleTime* pTime);

extern _BOOL RenameFile(_STRING lpstrSource,_STRING lpstrDestination);
extern _BOOL CombinateFile(_STRING lpstrHeadFile,_STRING lpstrTailFile);

extern _BOOL RemoveFile(_STRING lpstrFileName);
extern _BOOL RemoveFiles(_STRING lpstrDirectory,_STRING lpstrExtensionName);

////////////////////////////////////////////////////////////////////////////////
//
// General directory functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _STRING GetFileDirectorySplitter();

extern _BOOL ChangeFileDirectory(_STRING lpstrDirectory);
#define IsFileDirectoryExist(lpstrDirectory) \
	ChangeFileDirectory(lpstrDirectory)

extern _BOOL CreateFileDirectory(_STRING lpstrDirectory);
extern _BOOL RemoveFileDirectory(_STRING lpstrDirectory);

extern _BOOL GetFileDirectory(_PASCALSTRING strDirectory);

extern _STRING GetHomeDirectory();
extern void SetHomeDirectory(_STRING lpstrDirectory);
extern _BOOL ReturnHomeDirectory();

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
