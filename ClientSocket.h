#ifndef _CLIENT_SOCKET_H
#define _CLIENT_SOCKET_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _SOCKET ConnectTCPServer(_STRING lpstrAddress,_UINT16 nPort);
extern _SOCKET ConnectUDPServer(_STRING lpstrAddress,_UINT16 nPort);

extern _INT32 Availiable(_SOCKET socketClient);

extern _BOOL SendTCPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize);
extern _BOOL ReceiveTCPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32 nSize);

extern _BOOL SendUDPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32* lpSize);
extern _BOOL ReceiveUDPBuffer(_SOCKET socketClient,_BYTE* lpBuffer,_UINT32* lpSize);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
