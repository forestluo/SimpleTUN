#ifndef _SIMPLE_TUNNEL_H
#define _SIMPLE_TUNNEL_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Tunnel
typedef struct tagNetworkTunnel
{
	//Handle
	_OBJECT lpHandle;

	//Version
	_UINT32 nVersion[3];
	//MTU
	_UINT32 nMTUSize;

	//Local IP Address
	_IPV4 ipLocal;
	//Local IP Netmask
	_IPV4 ipNetmask;
	//Remote IP Address
	_IPV4 ipRemote;
	//Lease Time (in seconds)
	_UINT32 leaseTime;
	//Local MAC Address
	_MAC6 macLocal;
	//Remote MAC Address
	_MAC6 macRemote;

	//GUID
	_PASCALSTRING strGuid;
	//Adapter Index
	_INT32 nAdapterIndex;
	//DHCP Enabled
	_BOOL bDHCPEnabled;
	//NTE Context
	_UINT32 nConext;
	//NTE Instance
	_UINT32 nInstance;

	//Peer Port
	_UINT16 nPeerPort;
	//Peer IP Address
	_PASCALSTRING strPeerAddress;
	//UDP Socket
	_SOCKET socketUDP;

	//Read Overlapped
	_OBJECT lpRead;
	//Output Size
	_UINT32 nOutputSize;
	//Write Overlapped
	_OBJECT lpWrite;
	//Input Size
	_UINT32 nInputSize;

	//Read Thread.
	SimpleThread readThread;
	//Write Thread.
	SimpleThread writeThread;
}

NetworkTunnel;

////////////////////////////////////////////////////////////////////////////////
//
// Initialize network functions.
//
////////////////////////////////////////////////////////////////////////////////

//Initialize Tunnel Environment
extern _BOOL InitializeTunnelEnvironment();
//Uninitialize Tunnel Environment
extern void UninitializeTunnelEnvironment();

////////////////////////////////////////////////////////////////////////////////
//
// Tunnel functions.
//
////////////////////////////////////////////////////////////////////////////////

//Initialize Network Tunnel
extern void InitializeNetworkTunnel(NetworkTunnel* pTunnel);
//Uninitialize Network Tunnel
extern void UninitializeNetworkTunnel(NetworkTunnel* pTunnel);

//Open Network Tunnel
extern _BOOL OpenNetworkTunnel(NetworkTunnel* pTunnel);
//Open Named Network Tunnel
extern _BOOL OpenNamedNetworkTunnel(NetworkTunnel* pTunnel,_STRING lpstrAdapterName);
//Close Network Tunnel
extern void CloseNetworkTunnel(NetworkTunnel* pTunnel);

//Open Socket of Network Tunnel
extern _BOOL OpenNetworkTunnelSocket(NetworkTunnel* pTunnel);
//Close Socket of Network Tunnel
extern void CloseNetworkTunnelSocket(NetworkTunnel* pTunnel);

//Read Network Tunnel
extern _BOOL ReadNetworkTunnel(NetworkTunnel* pTunnel,_BYTE* lpBuffer,_INT32* lpReadSize);
//Write Network Tunnel
extern _BOOL WriteNetworkTunnel(NetworkTunnel* pTunnel,_BYTE* lpBuffer,_INT32* lpWriteSize);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
