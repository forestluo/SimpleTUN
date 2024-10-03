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
// Special includings.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _MICROSOFT_WINDOWS
#include "winsock2.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//
// General definations.
//
////////////////////////////////////////////////////////////////////////////////

//Tunnel
static NetworkTunnel theNetworkTunnel;

////////////////////////////////////////////////////////////////////////////////
//
// Initialize TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeTAPDriver()
{
	//Path
	_PASCALSTRING strPath;
	//Directory
	_PASCALSTRING strDirectory;

	//Get current working directory.
	if(!GetFileDirectory(strDirectory))
	{
#ifdef _DEBUG
		PrintLine(stderr,"TAPDriver::InitializeTAPDriver : fail to get current working directory !");
#endif
		return _FALSE;
	}
	//Set home directory.
	SetHomeDirectory(strDirectory);

	//Set log directory.
	sprintf(strPath,"%s%s",strDirectory,GetFileDirectorySplitter());
	//Initialize log.
	if(!InitializeLog(strPath,LOG_ALL))
	{
#ifdef _DEBUG
		PrintLine(stderr,"TAPDriver::InitializeTAPDriver : fail to initialize log !");
#endif
		return _FALSE;
	}

	//Initialize socket.
	if(!InitializeSocket())
	{
#ifdef _DEBUG
		LogRequestedEvent("TAPDriver::InitializeTAPDriver : fail to initialize socket !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Initialize tunnel environment.
	if(!InitializeTunnelEnvironment())
	{
#ifdef _DEBUG
		LogRequestedEvent("TAPDriver::InitializeTAPDriver : fail to initialize tunnel environments !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Initialize tunnel.
	InitializeNetworkTunnel(&theNetworkTunnel);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

void UninitializeTAPDriver()
{
	//Uninitialize tunnel.
	UninitializeNetworkTunnel(&theNetworkTunnel);
	//Uninitialize tunnel environment.
	UninitializeTunnelEnvironment();

	//Uninitialize socket.
	UninitializeSocket();
	//Uninitialize log.
	UninitializeLog();
}

////////////////////////////////////////////////////////////////////////////////
//
// Set virtual address.
//
////////////////////////////////////////////////////////////////////////////////

void SetVirtualAddress(_STRING lpstrLocalIPAddress,_STRING lpstrLocalNetmask,_STRING lpstrRemoteIPAddress)
{
	//Value
	_UINT32 nValue;

#ifdef _DEBUG
	assert(lpstrLocalIPAddress != NULL);
	assert(lpstrLocalNetmask != NULL);
	assert(lpstrRemoteIPAddress != NULL);
#endif
	//Get value.
	nValue = inet_addr(lpstrLocalIPAddress);
	//Set local.
	memcpy(theNetworkTunnel.ipLocal,&nValue,sizeof(_IPV4));

	//Get value.
	nValue = inet_addr(lpstrLocalNetmask);
	//Set mask.
	memcpy(theNetworkTunnel.ipNetmask,&nValue,sizeof(_IPV4));

	//Get value.
	nValue = inet_addr(lpstrRemoteIPAddress);
	//Set remote.
	memcpy(theNetworkTunnel.ipRemote,&nValue,sizeof(_IPV4));
}

////////////////////////////////////////////////////////////////////////////////
//
// Set virtual address.
//
////////////////////////////////////////////////////////////////////////////////

void SetL2TPServer(_STRING lpstrIPAddress,_UINT16 nPort)
{
#ifdef _DEBUG
	assert(lpstrIPAddress != NULL);
#endif
	//Set ip address.
	strcpy(theNetworkTunnel.strPeerAddress,lpstrIPAddress);
	//Set port.
	theNetworkTunnel.nPeerPort = nPort;
}

////////////////////////////////////////////////////////////////////////////////
//
// Whether TAP driver exists.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL TAPDriverExists(_STRING lpstrAdapterName)
{
#ifdef _DEBUG
	assert(lpstrAdapterName != NULL);
#endif
	//Return result.
	return IsNetworkTunnelExists(lpstrAdapterName);
}

////////////////////////////////////////////////////////////////////////////////
//
// Open TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenTAPDriver(_STRING lpstrAdapterName)
{
#ifdef _DEBUG
	assert(lpstrAdapterName != NULL);
#endif
	//Return result.
	return OpenNamedNetworkTunnel(&theNetworkTunnel,lpstrAdapterName);
}

////////////////////////////////////////////////////////////////////////////////
//
// Close TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

void CloseTAPDriver()
{
	//Close network tunnel.
	CloseNetworkTunnel(&theNetworkTunnel);
}

////////////////////////////////////////////////////////////////////////////////
//
// Open socket of TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenTAPDriverSocket()
{
	//Return result.
	return OpenNetworkTunnelSocket(&theNetworkTunnel);
}

////////////////////////////////////////////////////////////////////////////////
//
// Close socket of TAP driver.
//
////////////////////////////////////////////////////////////////////////////////

void CloseTAPDriverSocket()
{
	//Close network tunnel.
	CloseNetworkTunnelSocket(&theNetworkTunnel);
}

////////////////////////////////////////////////////////////////////////////////
//
// Wheter TAP driver is running.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsTAPDriverRunning()
{
	//Check status.
	return IsThreadRunning(&theNetworkTunnel.readThread) &&
		IsThreadRunning(&theNetworkTunnel.writeThread);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get TAP driver input size.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetTAPDriverInputSize()
{
	//Return result.
	return theNetworkTunnel.nInputSize;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get TAP driver output size.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetTAPDriverOutputSize()
{
	//Return result.
	return theNetworkTunnel.nOutputSize;
}

////////////////////////////////////////////////////////////////////////////////
//
// Swith TAP driver log.
//
////////////////////////////////////////////////////////////////////////////////

void SetTAPDriverLog(_BOOL bLog)
{
	//Set log requests.
	SetLogRequests(bLog ? LOG_ALL : LOG_NONE);
}
