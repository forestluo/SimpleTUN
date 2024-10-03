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
#include <sys/select.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

//Default Connect Timeout
#define DEFAULT_CONNECT_TIMEOUT								15
//Default Read & Write Timeout
#define DEFAULT_RW_TIMEOUT									15

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
// Set socket noblocking mode.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetSocketNoblockingMode(_SOCKET socketClient,_BOOL bNoblockingMode)
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Set noblocking mode.
	if(ioctlsocket(socketClient,FIONBIO,&bNoblockingMode) == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SetSocketNoblockingMode : fail to set noblocking mode !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Set socket nodelay.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetSocketNodelay(_SOCKET socketClient,_BOOL bNodelay)
{
//For windows.
#ifdef _MICROSOFT_WINDOWS

	//Set nodelay.
	if(setsockopt(socketClient,IPPROTO_TCP,TCP_NODELAY,(unsigned char *)&bNodelay,sizeof(_BOOL)))
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SetSocketNodelay : fail to set nodelay !");
#endif
		return _FALSE;
	}

#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Connect with a server.
//
////////////////////////////////////////////////////////////////////////////////

_SOCKET ConnectTCPServer(_STRING lpstrAddress,_UINT16 nPort)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_SOCKET socketClient;
	struct sockaddr_in destination;

#ifdef _DEBUG
	assert(lpstrAddress != NULL);
#endif

	//Create a socket.
	socketClient = (_SOCKET)socket(AF_INET,_SOCK_STREAM,IPPROTO_TCP);

	//Set noblocking mode.
	if(!SetSocketNoblockingMode(socketClient,_TRUE))
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectTCPServer : fail to set noblocking mode !");
#endif
		return _INVALID_SOCKET;
	}

	//Set nodelay.
	if(!SetSocketNodelay(socketClient,_TRUE))
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectTCPServer : fail to set nodelay !");
#endif
		return _INVALID_SOCKET;
	}

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketClient,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = DEFAULT_CONNECT_TIMEOUT;
	tv.tv_usec = 0;

	//Initialize input address.
	memset(&destination,0,sizeof(struct sockaddr_in));
	//Set address family.
	destination.sin_family = AF_INET;
	//Set specified address.
	destination.sin_addr.s_addr = inet_addr(lpstrAddress);
	//Set port.
	destination.sin_port = htons(nPort);

	//Try to connect with server.
	connect(socketClient,(struct sockaddr *)&destination,sizeof(struct sockaddr));

	//Set connection timeout.
	switch(select(socketClient + 1,NULL,&fd,NULL,&tv))
	{
	case _SOCKET_ERROR:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectTCPServer : socket error when connecting with server !");
#endif
		return _INVALID_SOCKET;
	case _SOCKET_TIMEOUT:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectTCPServer : timeout when connecting with server !");
#endif
		return _INVALID_SOCKET;
	default:;
	}
	//Return socket.
	return socketClient;
}

////////////////////////////////////////////////////////////////////////////////
//
// Connect with a server.
//
////////////////////////////////////////////////////////////////////////////////

_SOCKET ConnectUDPServer(_STRING lpstrAddress,_UINT16 nPort)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_SOCKET socketClient;
	struct sockaddr_in destination;

#ifdef _DEBUG
	assert(lpstrAddress != NULL);
#endif

	//Create a socket.
	socketClient = (_SOCKET)socket(AF_INET,_SOCK_DATAGRAM,IPPROTO_UDP);

	//Set noblocking mode.
	if(!SetSocketNoblockingMode(socketClient,_TRUE))
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectUDPServer : fail to set noblocking mode !");
#endif
		return _INVALID_SOCKET;
	}

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketClient,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = DEFAULT_CONNECT_TIMEOUT;
	tv.tv_usec = 0;

	//Initialize input address.
	memset(&destination,0,sizeof(struct sockaddr_in));
	//Set address family.
	destination.sin_family = AF_INET;
	//Set specified address.
	destination.sin_addr.s_addr = inet_addr(lpstrAddress);
	//Set port.
	destination.sin_port = htons(nPort);

	//Try to connect with server.
	connect(socketClient,(struct sockaddr *)&destination,sizeof(struct sockaddr));

	//Set connection timeout.
	switch(select(socketClient + 1,NULL,&fd,NULL,&tv))
	{
	case _SOCKET_ERROR:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectUDPServer : socket error when connecting with server !");
#endif
		return _INVALID_SOCKET;
	case _SOCKET_TIMEOUT:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ConnectUDPServer : timeout when connecting with server !");
#endif
		return _INVALID_SOCKET;
	default:;
	}
	//Return socket.
	return socketClient;
}

////////////////////////////////////////////////////////////////////////////////
//
// Availiable data from a socket.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 Availiable(_SOCKET socketClient)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_UINT32 nCount;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET);
#endif

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketClient,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	//Check availiable bytes.
	nCount = select(socketClient + 1,&fd,NULL,NULL,&tv);
	//Check result.
	if(nCount == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::Availiable : fail to poll state !");
#endif
		return _SOCKET_ERROR;
	}
	//Return value.	
	return nCount;
}

////////////////////////////////////////////////////////////////////////////////
//
// Send data from a socket.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 SocketSend(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize,_UINT32 nInterval)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_INT32 nCount;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
#endif

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketClient,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = nInterval;

	//Set timeout.
	switch(select(socketClient + 1,NULL,&fd,NULL,&tv))
	{
	case _SOCKET_ERROR:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketSend : socket error when sending data !");
#endif
		return _SOCKET_ERROR;
	case _SOCKET_TIMEOUT:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketSend : timeout when sending data !");
#endif
		return _SOCKET_TIMEOUT;
	default:;
	}
	
	//Send data.
	nCount = send(socketClient,lpBuffer,nSize,0);
	//Check result.
	if(nCount == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketSend : fail to send data !");
#endif
		return _SOCKET_ERROR;
	}
	//Return value.
	return nCount;
}

////////////////////////////////////////////////////////////////////////////////
//
// Receive data from a socket.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 SocketReceive(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize,_UINT32 nInterval)
{
	_SOCKET_SET fd;
	struct timeval tv;

	_INT32 nCount = 0;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
#endif

	//Initialize readfs.
	FD_ZERO(&fd);
	//Use marco for settings.
	FD_SET(socketClient,&fd);

	//Initialize timeval.
	memset(&tv,0,sizeof(struct timeval));
	//Set interval.
	tv.tv_sec = nInterval;
	tv.tv_usec = 0;

	//Set timeout.
	switch(select(socketClient + 1,&fd,NULL,NULL,&tv))
	{
	case _SOCKET_ERROR:
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketReceive : socket error when receiving data !");
#endif
		return _SOCKET_ERROR;
	case _SOCKET_TIMEOUT:
/*
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketReceive : timeout when receiving data !");
#endif
*/
		return _SOCKET_TIMEOUT;
	default:;
	}
	
	//Receive data.
	nCount = recv(socketClient,lpBuffer,nSize,0);
	//Check result.
	if(nCount == _SOCKET_ERROR)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SocketReceive : fail to receive data !");
#endif
		return _SOCKET_ERROR;
	}
	//Return value.
	return nCount;
}

////////////////////////////////////////////////////////////////////////////////
//
// Send TCP buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SendTCPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize)
{
	_UINT32 nTotal = 0;
	_INT32 nCount;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
#endif

	//Do while.
	while(nTotal < nSize)
	{
		//Send data.
		nCount = SocketSend(socketClient,lpBuffer + nTotal,nSize - nTotal,DEFAULT_RW_TIMEOUT);
		//Check result.
		if(nCount == _SOCKET_ERROR || nCount == _SOCKET_TIMEOUT)
		{
#ifdef _DEBUG
			PrintLine(stderr,"ClientSocket::SendTCPBuffer : fail to send raw data !");
#endif
			return _FALSE;
		}

		//Add byte count.
		nTotal += nCount;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Receive TCP buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ReceiveTCPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize)
{
	_UINT32 nTotal = 0;
	_INT32 nCount;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
#endif

	while(nTotal < nSize)
	{
		//Receive data.
		nCount = SocketReceive(socketClient,lpBuffer + nTotal,nSize - nTotal,DEFAULT_RW_TIMEOUT);
		//Check result.
		if(nCount == _SOCKET_ERROR || nCount == _SOCKET_TIMEOUT)
		{
#ifdef _DEBUG
			PrintLine(stderr,"ClientSocket::ReceiveTCPBuffer : fail to receive raw data !");
#endif
			return _FALSE;
		}

		//Add byte count.
		nTotal += nCount;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Send UDP buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SendUDPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32* lpSize)
{
	//Size.
	_INT32 nSize;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
	assert(lpSize != NULL && *lpSize > 0);
#endif

	//Send data.
	nSize = SocketSend(socketClient,lpBuffer,*lpSize,DEFAULT_RW_TIMEOUT);
	//Check result.
	if(nSize == _SOCKET_ERROR || nSize == _SOCKET_TIMEOUT)
	{
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::SendUCPBuffer : fail to send raw data !");
#endif
		return _FALSE;
	}
	//Set size.
	*lpSize = nSize;
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Receive UDP buffer.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ReceiveUDPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32* lpSize)
{
	//Size.
	_INT32 nSize;

#ifdef _DEBUG
	assert(socketClient != _INVALID_SOCKET && lpBuffer != NULL);
	assert(lpSize != NULL && *lpSize > 0);
#endif

	//Receive data.
	nSize = SocketReceive(socketClient,lpBuffer,*lpSize,DEFAULT_RW_TIMEOUT);
	//Check result.
	if(nSize == _SOCKET_ERROR || nSize == _SOCKET_TIMEOUT)
	{
/*
#ifdef _DEBUG
		PrintLine(stderr,"ClientSocket::ReceiveUDPBuffer : fail to receive raw data !");
#endif
*/
		return _FALSE;
	}
	//Set size.
	*lpSize = nSize;
	//Return true.
	return _TRUE;
}
