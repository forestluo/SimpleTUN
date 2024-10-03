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
//
////////////////////////////////////////////////////////////////////////////////

//For windows.
#ifdef _MICROSOFT_WINDOWS
#include <winsock.h>
#endif

//For linux.
#ifdef _REDHAT_LINUX
#include <sys/socket.h>
#include <unistd.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Initialize socket.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeSocket()
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	WSADATA wsaData;
	//Startup socket module.
	if(WSAStartup(MAKEWORD(2,1),&wsaData) != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Socket::InitializeSocket : fail to startup socket !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize socket.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UninitializeSocket()
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Clean up all the sockets.
	if(WSACleanup() != 0)
	{
#ifdef _DEBUG
		PrintLine(stderr,"Socket::UninitializeSocket : fail to cleanup socket !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Close a socket.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CloseSocket(_SOCKET socket)
{
#ifdef _DEBUG
	assert(socket != _INVALID_SOCKET);
#endif

//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Close socket.
	if(closesocket(socket) == _SOCKET_ERROR)

#endif

//For linux.
#ifdef _REDHAT_LINUX

	//Close socket.
	if(close(socket) == _SOCKET_ERROR)

#endif

	{
#ifdef _DEBUG
		PrintLine(stderr,"Socket::CloseSocket : error on closing socket !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
