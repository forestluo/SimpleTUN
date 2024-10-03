#ifndef _SIMPLE_SOCKET_H
#define _SIMPLE_SOCKET_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Type Definition
#define _SOCK_STREAM										SOCK_STREAM
#define _SOCK_DATAGRAM										SOCK_DGRAM

//Definition
typedef _UINT32												_SOCKET;

//Invalid Socket
#define _INVALID_SOCKET										(_SOCKET)-1
//Socket Error
#define _SOCKET_ERROR										-1
//Socket Timeout
#define _SOCKET_TIMEOUT										0

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL InitializeSocket();
extern _BOOL UninitializeSocket();

extern _BOOL CloseSocket(_SOCKET socket);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
