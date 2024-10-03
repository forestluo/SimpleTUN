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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//Default Queue Size
#define DEFAULT_QUEUE_SIZE									128
//Default Accept Timeout
#define DEFAULT_ACCEPT_TIMEOUT								1

//For windows.
#ifdef _MICROSOFT_WINDOWS
typedef struct fd_set 										_SOCKET_SET;
#endif

//For linux.
#ifdef _REDHAT_LINUX
typedef fd_set												_SOCKET_SET;
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Create a server socket.
//
////////////////////////////////////////////////////////////////////////////////

_SOCKET CreateServer(_UINT16 nPort)
{
	_SOCKET socketServer;
	struct sockaddr_in source;

	//Create a socket.
	socketServer = (_SOCKET)socket(AF_INET,_SOCK_STREAM,0);

	//Initialize input address.
	memset(&source,0,sizeof(struct sockaddr_in));
	//Set address family.
	source.sin_family = AF_INET;
	//Set default address.
	source.sin_addr.s_addr = htonl(INADDR_ANY);
	//Set port.
	source.sin_port = htons(nPort);

	//Bind the socket.
	if(bind(socketServer,(struct sockaddr *)&source,sizeof(struct sockaddr_in)) == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ServerSocket::CreateServer : fail to bind !");
#endif
		return _INVALID_SOCKET;
	}

	//Begin listen on a socket.
	if(listen(socketServer,DEFAULT_QUEUE_SIZE) == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ServerSocket::CreateServer : fail to listen !");
#endif
		return _INVALID_SOCKET;
	}

#ifdef _DEBUG
	PrintLine(stdout,"ServerSocket::CreateServer : server socket created !");
#endif

	//Return socket.
	return socketServer;
}

////////////////////////////////////////////////////////////////////////////////
//
// Accept a client from server socket.
//
////////////////////////////////////////////////////////////////////////////////

_SOCKET AcceptClient(_SOCKET socketServer,_PASCALSTRING strAddress)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_UINT32 nSize;
	_SOCKET socketClient;
	struct sockaddr_in destination;

#ifdef _DEBUG
	assert(socketServer != _INVALID_SOCKET);
#endif

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketServer,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = DEFAULT_ACCEPT_TIMEOUT;
	tv.tv_usec = 0;

	//Set timeout.
	switch(select(socketServer + 1,&fd,NULL,NULL,&tv))
	{
	case _SOCKET_ERROR:
#ifdef _DEBUG
		PrintLine(stderr,"ServerSocket::AcceptClient : socket error when accepting socket !");
#endif
		return _INVALID_SOCKET;
	case _SOCKET_TIMEOUT:
#ifdef _DEBUG
		//PrintLine(stderr,"ServerSocket::AcceptClient : timeout when accepting socket !");
#endif
		return _INVALID_SOCKET;
	default:;
	}
	
	//Check readset.
	if(!FD_ISSET(socketServer,&fd))
	{
#ifdef _DEBUG
		PrintLine(stderr,"ServerSocket::AcceptClient : no socket accepted !");
#endif
		return _INVALID_SOCKET;
	}
			
	//Set default size.
	nSize = sizeof(struct sockaddr_in);
	//Try to accept a socket.
	socketClient = (_SOCKET)accept(socketServer,(struct sockaddr *)&destination,&nSize);
	//Check the result.
	if(socketClient == _INVALID_SOCKET)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ServerSocket::AcceptClient : invalid socket accepted !");
#endif
		return _INVALID_SOCKET;
	}
	
	//Copy ip address.
 	strcpy(strAddress,inet_ntoa(destination.sin_addr));

#ifdef _DEBUG
	PrintLine(stdout,"ServerSocket::AcceptClient : socket(%s) accepted !",strAddress);
#endif

	//Return socket.
	return socketClient;
}
