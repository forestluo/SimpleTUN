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

//For windows.
#ifdef _MICROSOFT_WINDOWS
#include <windows.h>
#include <winioctl.h>
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

//Default Timeout
#define DEFAULT_TIMEOUT										SECOND

////////////////////////////////////////////////////////////////////////////////
//
// Directorys
//
////////////////////////////////////////////////////////////////////////////////

//User Mode Device Directory
#define USER_MODE_DEVICE_DIRECTORY							"\\\\.\\Global\\"
//System Device Directory
#define SYSTEM_DEVICE_DIRECTORY 							"\\Device\\"
//User Device Directory
#define USER_DEVICE_DIRECTORY								"\\DosDevices\\Global\\"
//Tap Suffix
#define TAP_SUFFIX											".tap"

////////////////////////////////////////////////////////////////////////////////
//
// TAP IOCTLs.
//
////////////////////////////////////////////////////////////////////////////////

#define TAP_CONTROL_CODE(request,method) \
	CTL_CODE(FILE_DEVICE_UNKNOWN,request,method,FILE_ANY_ACCESS)
//Version 8.1
#define TAP_IOCTL_GET_MAC									TAP_CONTROL_CODE(1,METHOD_BUFFERED)
#define TAP_IOCTL_GET_VERSION								TAP_CONTROL_CODE(2,METHOD_BUFFERED)
#define TAP_IOCTL_GET_MTU									TAP_CONTROL_CODE(3,METHOD_BUFFERED)
#define TAP_IOCTL_GET_INFO									TAP_CONTROL_CODE(4,METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_POINT_TO_POINT						TAP_CONTROL_CODE(5,METHOD_BUFFERED)
#define TAP_IOCTL_SET_MEDIA_STATUS							TAP_CONTROL_CODE(6,METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_DHCP_MASQ							TAP_CONTROL_CODE(7,METHOD_BUFFERED)
#define TAP_IOCTL_GET_LOG_LINE								TAP_CONTROL_CODE(8,METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_DHCP_SET_OPT						TAP_CONTROL_CODE(9,METHOD_BUFFERED)
//Version 8.2
#define TAP_IOCTL_CONFIG_TUN								TAP_CONTROL_CODE (10, METHOD_BUFFERED)

////////////////////////////////////////////////////////////////////////////////
//
// Initialize tunnel environment.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InitializeTunnelEnvironment()
{
	//Load adapters information list.
	if(!LoadAdaptersInformationList())
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::InitializeTunnelEnvironment : fail to load adapters information list !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Show adapters information list.
	ShowAdaptersInformationList();

	//Load interface information list.
	if(!LoadInterfaceInformationList())
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::InitializeTunnelEnvironment : fail to load interfaces information list !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Show interface information list.
	ShowInterfaceInformationList();

	//Load adapters.
	if(!LoadNetworkAdapters())
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::InitializeTunnelEnvironment : fail to load network adapters !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FAILURE;
	}
	//Show adapters.
	ShowNetworkAdapters();

	//Load connections.
	if(!LoadNetworkConnections())
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::InitializeTunnelEnvironment : fail to load network connections !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FAILURE;
	}
	//Show connections.
	ShowNetworkConnections();

	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize tunnel environment.
//
////////////////////////////////////////////////////////////////////////////////

void UninitializeTunnelEnvironment()
{
	//Release connections.
	ReleaseNetworkConnections();
	//Release adapters.
	ReleaseNetworkAdapters();

	//Unload interface information list.
	UnloadInterfaceInformationList();
	//Unload adapters information list.
	UnloadAdaptersInformationList();
}

////////////////////////////////////////////////////////////////////////////////
//
// Network ARP response.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL NetworkARPResponse(NetworkTunnel* pTunnel,_MAC6 macDestination,_IPV4 ipDestination)
{
	//Buffer
	SimpleBuffer buffer;
	//Ethernet Packet
	EthernetPacket packet;

#ifdef _DEBUG
	assert(pTunnel != NULL && pTunnel->lpHandle != INVALID_HANDLE_VALUE);
#endif

	//Initialize packet.
	InitializeEthernetPacket(&packet);

	//Set ethernet packet.
	//Set MAC source address.
	memcpy(packet.header.macSource,pTunnel->macRemote,sizeof(_MAC6));
	//Set MAC destination address.
	memcpy(packet.header.macDestination,macDestination,sizeof(_MAC6));
	//Set protocol type.
	packet.header.nProtocolType = 0x0806;//ARP

	//Set ARP packet.
	//Initialize ARP packet.
	InitializeARPPacket(&packet.arpPacket);
	//Set opertaion.
	packet.arpPacket.nOperation = 2;//ARP Response
	//Set MAC source address.
	memcpy(packet.arpPacket.macSource,pTunnel->macRemote,sizeof(_MAC6));
	//Set IP source address.
	memcpy(packet.arpPacket.ipSource,pTunnel->ipRemote,sizeof(_IPV4));
	//Set MAC destination address.
	memcpy(packet.arpPacket.macDestination,macDestination,sizeof(_MAC6));
	//Set IP destination address.
	memcpy(packet.arpPacket.ipDestination,ipDestination,sizeof(_IPV4));
	
#ifdef _DEBUG
	//Dump packet.
	DumpEthernetPacket(&packet);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Wrap packet.
	if(!WrapEthernetPacket(&buffer,&packet))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkARPResponse : fail to wrap packet !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	//Log buffer.
	LogBuffer(&buffer);
#endif

	//Write response.
	if(!WriteNetworkTunnel(pTunnel,(_BYTE *)buffer.block,&buffer.nCount))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkARPResponse : fail to write response !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Network Ping response.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL NetworkPingResponse(NetworkTunnel* pTunnel,_MAC6 macDestination,_IPV4 ipDestination,IPPacket* lpPacket)
{
	//Buffer
	SimpleBuffer buffer;
	//Ethernet Packet
	EthernetPacket packet;

#ifdef _DEBUG
	assert(pTunnel != NULL && pTunnel->lpHandle != INVALID_HANDLE_VALUE);
	assert(lpPacket != NULL);
#endif

	//Initialize packet.
	InitializeEthernetPacket(&packet);

	//Set ethernet packet.
	//Set MAC source address.
	memcpy(packet.header.macSource,pTunnel->macRemote,sizeof(_MAC6));
	//Set MAC destination address.
	memcpy(packet.header.macDestination,macDestination,sizeof(_MAC6));
	//Set protocol type.
	packet.header.nProtocolType = 0x0800;//IP

	//Initialize IP packet.
	InitializeIPPacket(&packet.ipPacket);
	//Set IP packet.
	packet.ipPacket.nID = lpPacket->nID;
	//Set protocol.
	packet.ipPacket.nProtocol = 1;//ICMP
	//Set IP source address.
	memcpy(packet.ipPacket.ipSource,pTunnel->ipRemote,sizeof(_IPV4));
	//Set IP destination address.
	memcpy(packet.ipPacket.ipDestination,ipDestination,sizeof(_IPV4));

	//Copy ICMP packet.
	memcpy(&packet.ipPacket.icmpPacket,&lpPacket->icmpPacket,sizeof(ICMPPacket));
	//Set type.
	packet.ipPacket.icmpPacket.nType = 0;//Echo Response
	//Set code.
	packet.ipPacket.icmpPacket.nCode = 0;//Success
	//Get checksum.
	if(!GetICMPPacketChecksum(&packet.ipPacket.icmpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkPingResponse : fail to get checksum !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Set total length.
	packet.ipPacket.nTotalLength = packet.ipPacket.nHeaderLength * sizeof(_UINT32) + 
		8 * sizeof(_UINT8) + packet.ipPacket.icmpPacket.buffer.nCount;
	//Get checksum.
	if(!GetIPPacketChecksum(&packet.ipPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkPingResponse : fail to get checksum !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	//Dump packet.
	DumpEthernetPacket(&packet);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Wrap packet.
	if(!WrapEthernetPacket(&buffer,&packet))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkPingResponse : fail to wrap packet !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	//Log buffer.
	LogBuffer(&buffer);
#endif

	//Write response.
	if(!WriteNetworkTunnel(pTunnel,(_BYTE *)buffer.block,&buffer.nCount))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkPingResponse : fail to write response !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Network L2TP Out.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL NetworkL2TPOut(NetworkTunnel* pTunnel,IPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(pTunnel != NULL && pTunnel->lpHandle != INVALID_HANDLE_VALUE);
	assert(lpPacket != NULL);
#endif

	//Send udp data.
	if(!SendUDPBuffer(pTunnel->socketUDP,(_BYTE *)lpPacket->udpPacket.buffer.block,&lpPacket->udpPacket.buffer.nCount))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkL2TPOut : fail to send L2TP packet !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Network read process.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL NetworkReadProcess(_OBJECT lpObject)
{
	//Network Tunnel
	NetworkTunnel* pTunnel;

	//Simple Buffer
	SimpleBuffer buffer;
	//Ethernet Packet
	EthernetPacket packet;

#ifdef _DEBUG
	assert(lpObject != NULL);
#endif
	
	//Change argument.
	pTunnel = (NetworkTunnel *)lpObject;

#ifdef _DEBUG
	assert(pTunnel->socketUDP != _INVALID_SOCKET);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Set count.
	buffer.nCount = BLOCK_SIZE;
	//Try to read it.
	if(!ReadNetworkTunnel(pTunnel,(_BYTE *)&buffer.block,&buffer.nCount))
	{
		//Return true.
		return _TRUE;
	}

	//Check count.
	if(buffer.nCount <= 0)
	{
		//Return true.
		return _TRUE;
	}
	//Add read size.
	pTunnel->nReadSize += buffer.nCount;

#ifdef _DEBUG
	//Log buffer.
	LogBuffer(&buffer);
#endif

	//Unwrap packet.
	if(!UnwrapEthernetPacket(&buffer,&packet))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkReadProcess : fail to unwrap packet !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _TRUE;
	}

#ifdef _DEBUG
	//Dump packet.
	DumpEthernetPacket(&packet);
#endif

	//Check packet.
	if(packet.header.nProtocolType == 0x0806)
	{
		//Check destination.
		if(memcmp(packet.arpPacket.ipDestination,pTunnel->ipRemote,sizeof(_IPV4)) != 0)
		{
			//Return true.
			return _TRUE;
		}
		//Network ARP response.
		if(!NetworkARPResponse(pTunnel,packet.arpPacket.macSource,packet.arpPacket.ipSource))
		{
#ifdef _DEBUG
			LogRequestedEvent("Tunnel::NetworkReadProcess : fail to do ARP response !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
	}
	else if(packet.header.nProtocolType == 0x0800)
	{
		//Check destination.
		if(memcmp(packet.ipPacket.ipDestination,pTunnel->ipRemote,sizeof(_IPV4)) != 0)
		{
			//Return true.
			return _TRUE;
		}
		//Check protocol type.
		if(packet.ipPacket.nProtocol == 1)
		{
#ifdef _DEBUG
			LogRequestedEvent("Tunnel::NetworkReadProcess : ICMP packet was received !",
				LOG_TUNNEL | LOG_INFORMATION);
#endif
			//Check icmp type.
			if(packet.ipPacket.icmpPacket.nType == 8)
			{
				//Do ping response.
				if(!NetworkPingResponse(pTunnel,packet.header.macSource,packet.ipPacket.ipSource,&packet.ipPacket))
				{
#ifdef _DEBUG
					LogRequestedEvent("Tunnel::NetworkReadProcess : fail to do ping response !",
						LOG_TUNNEL | LOG_EXCEPTION);
#endif
				}
			}
		}
		else if(packet.ipPacket.nProtocol == 17)
		{
#ifdef _DEBUG
			LogRequestedEvent("Tunnel::NetworkReadProcess : UDP packet was received !",
				LOG_TUNNEL | LOG_INFORMATION);
#endif
			//Check icmp type.
			if(packet.ipPacket.udpPacket.nDestinationPort = 1701)
			{
#ifdef _DEBUG
				LogRequestedEvent("Tunnel::NetworkReadProcess : L2TP packet was received !",
					LOG_TUNNEL | LOG_INFORMATION);
#endif
				//Send L2TP packet.
				if(!NetworkL2TPOut(pTunnel,&packet.ipPacket))
				{
#ifdef _DEBUG
					LogRequestedEvent("Tunnel::NetworkReadProcess : L2TP packet was received !",
						LOG_TUNNEL | LOG_EXCEPTION);
#endif
				}
				else
				{
#ifdef _DEBUG
					LogRequestedEvent("Tunnel::NetworkReadProcess : L2TP packet was sent !",
						LOG_TUNNEL | LOG_INFORMATION);
#endif
				}
			}
		}
	}
	else
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkReadProcess : packet was discarded !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Network write process.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL NetworkWriteProcess(_OBJECT lpObject)
{
	//Network Tunnel
	NetworkTunnel* pTunnel;

	//Simple Buffer
	SimpleBuffer buffer;
	//IP Packet
	EthernetPacket packet;

#ifdef _DEBUG
	assert(lpObject != NULL);
#endif
	
	//Change argument.
	pTunnel = (NetworkTunnel *)lpObject;

#ifdef _DEBUG
	assert(pTunnel->socketUDP != _INVALID_SOCKET);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Set count.
	buffer.nCount = BLOCK_SIZE;
	//Receive buffer.
	if(!ReceiveUDPBuffer(pTunnel->socketUDP,(_BYTE *)buffer.block,&buffer.nCount))
	{
		//Return true.
		return _TRUE;
	}

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::NetworkWriteProcess : receive UDP packet !",
		LOG_TUNNEL | LOG_EXCEPTION);
#endif

	//Check count,
	if(buffer.nCount <= 0)
	{
		//Return true.
		return _TRUE;
	}
	//Add write size.
	pTunnel->nWriteSize += buffer.nCount;

#ifdef _DEBUG
	//Log buffer.
	LogBuffer(&buffer);
#endif

	//Initialize packet.
	InitializeEthernetPacket(&packet);

	//Set ethernet packet.
	//Set MAC source address.
	memcpy(packet.header.macSource,pTunnel->macRemote,sizeof(_MAC6));
	//Set MAC destination address.
	memcpy(packet.header.macDestination,pTunnel->macLocal,sizeof(_MAC6));
	//Set protocol type.
	packet.header.nProtocolType = 0x0800;//IP

	//Initialize IP packet.
	InitializeIPPacket(&packet.ipPacket);
	//Set IP packet.
	//packet.ipPacket.nID = 0;
	//Set protocol.
	packet.ipPacket.nProtocol = 17;//UDP
	//Set IP source address.
	memcpy(packet.ipPacket.ipSource,pTunnel->ipRemote,sizeof(_IPV4));
	//Set IP destination address.
	memcpy(packet.ipPacket.ipDestination,pTunnel->ipLocal,sizeof(_IPV4));

	//Get udp packet.
	//Set source port.
	packet.ipPacket.udpPacket.nSourcePort = 1701;
	//Set destination port.
	packet.ipPacket.udpPacket.nDestinationPort = 1701;
	//Set
	packet.ipPacket.udpPacket.nLength = buffer.nCount + 4 * sizeof(_UINT16);
	//Copy buffer.
	memcpy(&packet.ipPacket.udpPacket.buffer,&buffer,sizeof(SimpleBuffer));
	//Set checksum.
	packet.ipPacket.udpPacket.nChecksum = 0;
	//Get checksum.
	if(!GetUDPPacketChecksum(packet.ipPacket.ipSource,packet.ipPacket.ipDestination,&packet.ipPacket.udpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkWriteResponse : fail to get checksum !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set total length.
	packet.ipPacket.nTotalLength = packet.ipPacket.nHeaderLength * sizeof(_UINT32) + packet.ipPacket.udpPacket.nLength;
	//Get checksum.
	if(!GetIPPacketChecksum(&packet.ipPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkWriteResponse : fail to get checksum !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	//Dump packet.
	DumpEthernetPacket(&packet);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Wrap packet.
	if(!WrapEthernetPacket(&buffer,&packet))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkWriteResponse : fail to wrap packet !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	//Log buffer.
	LogBuffer(&buffer);
#endif

	//Print.
	PrintLine(stdout,"--------------------UDP packet was sent--------------------");

	//Write response.
	if(!WriteNetworkTunnel(pTunnel,(_BYTE *)buffer.block,&buffer.nCount))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::NetworkWriteResponse : fail to write response !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeNetworkTunnel(NetworkTunnel* pTunnel)
{
#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

	//Clear.
	memset(pTunnel,0,sizeof(NetworkTunnel));
	//Set handle.
	pTunnel->lpHandle = INVALID_HANDLE_VALUE;

	//Clear socket.
	pTunnel->socketUDP = _INVALID_SOCKET;

	//Create overlapped.
	pTunnel->lpRead = (OVERLAPPED *)malloc(sizeof(OVERLAPPED));
#ifdef _DEBG
	assert(pTunnel->lpRead != NULL);
#endif
	//Clear.
	memset(pTunnel->lpRead,0,sizeof(OVERLAPPED));
	//Set the read event.
	((OVERLAPPED *)pTunnel->lpRead)->hEvent = INVALID_HANDLE_VALUE;
	((OVERLAPPED *)pTunnel->lpRead)->Offset = 0;
	((OVERLAPPED *)pTunnel->lpRead)->OffsetHigh = 0;

	//Create overlapped.
	pTunnel->lpWrite = (OVERLAPPED *)malloc(sizeof(OVERLAPPED));
#ifdef _DEBG
	assert(pTunnel->lpWrite != NULL);
#endif
	//Clear.
	memset(pTunnel->lpWrite,0,sizeof(OVERLAPPED));
	//Set the read event.
	((OVERLAPPED *)pTunnel->lpWrite)->hEvent = INVALID_HANDLE_VALUE;
	((OVERLAPPED *)pTunnel->lpWrite)->Offset = 0;
	((OVERLAPPED *)pTunnel->lpWrite)->OffsetHigh = 0;

	//Initialize thread.
	InitializeThread(&pTunnel->readThread);
	//Set name.
	strcpy(pTunnel->readThread.strName,"NetworkReadProcess");
	//Set process.
	pTunnel->readThread.lpProcess = NetworkReadProcess;
	//Set object.
	pTunnel->readThread.lpObject = pTunnel;
	//Set wait time.
	pTunnel->readThread.nWaitTime = 0;

	//Initialize thread.
	InitializeThread(&pTunnel->writeThread);
	//Set name.
	strcpy(pTunnel->writeThread.strName,"NetworkWriteProcess");
	//Set process.
	pTunnel->writeThread.lpProcess = NetworkWriteProcess;
	//Set object.
	pTunnel->writeThread.lpObject = pTunnel;
	//Set wait time.
	pTunnel->writeThread.nWaitTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

void UninitializeNetworkTunnel(NetworkTunnel* pTunnel)
{
#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

	//Check result.
	if(pTunnel->lpRead != NULL)
	{
		//Delete.
		free(pTunnel->lpRead);
		//Clear.
		pTunnel->lpRead = NULL;
	}
	//Check result.
	if(pTunnel->lpWrite != NULL)
	{
		//Delete.
		free(pTunnel->lpWrite);
		//Clear.
		pTunnel->lpWrite = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Set TAP network tunnel status.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetTAPNetworkTunnelStatus(NetworkTunnel* pTunnel,_BOOL bStatus)
{
	//Length.
	_INT32 nLength;
	//Timeout.
	SimpleTimeout timeout;

#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

	//Set length.
	nLength = 0;
	//Set status.
    if(!DeviceIoControl(pTunnel->lpHandle,TAP_IOCTL_SET_MEDIA_STATUS,
					&bStatus,sizeof(_BOOL),
					&bStatus,sizeof(_BOOL),&nLength,NULL))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::SetTAPNetworkTunnelStatus : fail to set status of device !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
		return _FALSE;
	}

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::SetTAPNetworkTunnelStatus : wait its changing !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Initialize timeout.
	InitializeTimeout(&timeout);
	//Set timeout.
	timeout.timeConsumed = DEFAULT_TIMEOUT;
	//Wait device to come up.
	while(!IsTimeout(&timeout)) SleepMilliseconds(SECOND);
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::SetTAPNetworkTunnelStatus : finish waiting !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Open TAP network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenTAPNetworkTunnel(NetworkTunnel* pTunnel)
{
	//Status.
	//Length.
	_INT32 nLength;
	//Device Path
	_PASCALSTRING strDevicePath;

#ifdef _DEBUG
	assert(pTunnel != NULL && strlen(pTunnel->strGuid) > 0);
#endif

	//Format device path.
	Format(strDevicePath,"%s%s%s",USER_MODE_DEVICE_DIRECTORY,pTunnel->strGuid,TAP_SUFFIX);
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"Tunnel::OpenTAPNetworkTunnel : device path(%s) !",strDevicePath);
#endif

	//Create file.
	pTunnel->lpHandle = CreateFile(strDevicePath,
									GENERIC_READ | GENERIC_WRITE,
									FILE_SHARE_READ,
									0,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_OVERLAPPED,
									0);
	//Check result.
	if(pTunnel->lpHandle == INVALID_HANDLE_VALUE)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to open device !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : device was opened !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Set length.
	nLength = 0;
	//Get version.
    if(!DeviceIoControl(pTunnel->lpHandle,TAP_IOCTL_GET_VERSION,
						&pTunnel->nVersion,3 * sizeof(_UINT32),
						&pTunnel->nVersion,3 * sizeof(_UINT32),&nLength,NULL))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to get version of device !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"Tunnel::OpenTAPNetworkTunnel : version(%d.%d %s) !",
		pTunnel->nVersion[0],pTunnel->nVersion[1],pTunnel->nVersion[2] ? "Debug" : "Release");
#endif

	//Set length.
	nLength = 0;
	//Get MTU
    if(!DeviceIoControl(pTunnel->lpHandle,TAP_IOCTL_GET_MTU,
					&pTunnel->nMTUSize,sizeof(_UINT32),
					&pTunnel->nMTUSize,sizeof(_UINT32),&nLength,NULL))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to get MTU of device !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"Tunnel::OpenTAPNetworkTunnel : MTU(%d) !",pTunnel->nMTUSize);
#endif

	//Set status.
    if(!SetTAPNetworkTunnelStatus(pTunnel,_TRUE))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to enable device !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : device was enabled !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Set local address.
	if(!SetNetworkTunnelLocalAddress(pTunnel))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to set local address !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : local address was set !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Create I/O event used for overlapped reads.
	((OVERLAPPED *)pTunnel->lpRead)->hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//Check result.
	if(((OVERLAPPED *)pTunnel->lpRead)->hEvent == INVALID_HANDLE_VALUE)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : Cannot create I/O event for reading !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : create I/O event for reading !",
		LOG_TUNNEL | LOG_EXCEPTION);
#endif

	//Create I/O event used for overlapped writes.
	((OVERLAPPED *)pTunnel->lpWrite)->hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//Check result.
	if(((OVERLAPPED *)pTunnel->lpWrite)->hEvent == INVALID_HANDLE_VALUE)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : cannot create I/O event for writing !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : create I/O event for writing !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Create socket.
	pTunnel->socketUDP = ConnectUDPServer(pTunnel->strPeerAddress,pTunnel->nPeerPort);
	//Check result.
	if(pTunnel->socketUDP == _INVALID_SOCKET)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to connect server !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : server was connected !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Start write.
	if(!StartupThread(&pTunnel->writeThread))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to startup write thread !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : read thread was startup !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif

	//Start read.
	if(!StartupThread(&pTunnel->readThread))
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : fail to startup read thread !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::OpenTAPNetworkTunnel : read thread was startup !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Open network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenNetworkTunnel(NetworkTunnel* pTunnel)
{
	//Connection
	_STRING lpstrGuid;

#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

	//Get guid.
	lpstrGuid = GetNetworkTunnelGuid("tap0801");
	//Check result.
	if(lpstrGuid == NULL || strlen(lpstrGuid) <= 0)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenNetworkTunnel : fail to find TAP adapter !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Copy
	strcpy(pTunnel->strGuid,lpstrGuid);

#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"Tunnel::OpenNetworkTunnel : GUID(\"%s\") !",
		pTunnel->strGuid);
#endif
	//Return result.
	return OpenTAPNetworkTunnel(pTunnel);
}

////////////////////////////////////////////////////////////////////////////////
//
// Open named network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL OpenNamedNetworkTunnel(NetworkTunnel* pTunnel,_STRING lpstrAdapterName)
{
	//Connection
	_STRING lpstrGuid;

#ifdef _DEBUG
	assert(pTunnel != NULL && lpstrAdapterName != NULL);
#endif

	//Get guid.
	lpstrGuid = GetNetworkTunnelGuid(lpstrAdapterName);
	//Check result.
	if(lpstrGuid == NULL || strlen(lpstrGuid) <= 0)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::OpenNamedNetworkTunnel : fail to find TAP adapter !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Copy
	strcpy(pTunnel->strGuid,lpstrGuid);

#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"Tunnel::OpenNetworkTunnel : GUID(\"%s\") !",
		pTunnel->strGuid);
#endif
	//Return result.
	return OpenTAPNetworkTunnel(pTunnel);
}

////////////////////////////////////////////////////////////////////////////////
//
// Close network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

void CloseNetworkTunnel(NetworkTunnel* pTunnel)
{
#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : shutdown read thread !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Shutdown read thread.
	ShutdownThread(&pTunnel->readThread);

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : shutdown write thread !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Shutdown write thread.
	ShutdownThread(&pTunnel->writeThread);

	//Check socket.
	if(pTunnel->socketUDP != _INVALID_SOCKET)
	{
#ifdef _DEBUG
		LogRequestedEvent("Tunnel::CloseNetworkTunnel : socket was closed !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
		//Close socket.
		CloseSocket(pTunnel->socketUDP);
		//Clear socket.
		pTunnel->socketUDP = _INVALID_SOCKET;
	}

	//Check handle.
	if(pTunnel->lpHandle != INVALID_HANDLE_VALUE)
	{
		//Close file.
		if(!CancelIo(pTunnel->lpHandle))
		{
#ifdef _DEBUG
			LogRequestedEvent("Tunnel::CloseNetworkTunnel : fail to cancel I/O !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
		else
		{
#ifdef _DEBUG
			LogRequestedEvent("Tunnel::CloseNetworkTunnel : I/O was cancel !",
				LOG_TUNNEL | LOG_INFORMATION);
#endif
		}
	}

	//Clear local address.
	ClearNetworkTunnelLocalAddress(pTunnel);

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : close read I/O event !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Clean up read event objects.
	if(((OVERLAPPED *)pTunnel->lpRead)->hEvent != INVALID_HANDLE_VALUE)
	{
		//Close the I/O read events.
		CloseHandle(((OVERLAPPED *)pTunnel->lpRead)->hEvent);

		//Set read event.
		((OVERLAPPED *)pTunnel->lpRead)->hEvent = INVALID_HANDLE_VALUE;
		((OVERLAPPED *)pTunnel->lpRead)->Offset = 0;
		((OVERLAPPED *)pTunnel->lpRead)->OffsetHigh = 0;
	}

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : close write I/O event !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Clean up write event objects.
	if(((OVERLAPPED *)pTunnel->lpWrite)->hEvent != INVALID_HANDLE_VALUE)
	{
		//Close the I/O write events.
		CloseHandle(((OVERLAPPED *)pTunnel->lpWrite)->hEvent);

		//Set write event.
		((OVERLAPPED *)pTunnel->lpWrite)->hEvent = INVALID_HANDLE_VALUE;
		((OVERLAPPED *)pTunnel->lpWrite)->Offset = 0;
		((OVERLAPPED *)pTunnel->lpWrite)->OffsetHigh = 0;
	}

#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : close device handle !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
	//Check handle.
	if(pTunnel->lpHandle != INVALID_HANDLE_VALUE)
	{
		//Close file.
		CloseHandle(pTunnel->lpHandle);
		//Clear handle.
		pTunnel->lpHandle = INVALID_HANDLE_VALUE;
	}
#ifdef _DEBUG
	LogRequestedEvent("Tunnel::CloseNetworkTunnel : device was closed !",
		LOG_TUNNEL | LOG_INFORMATION);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// Read network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ReadNetworkTunnel(NetworkTunnel* pTunnel,_BYTE* lpBuffer,_INT32* lpReadSize)
{
	//Result.
	_BOOL bResult;
	//Set size.
	_UINT32 nSize;

#ifdef _DEBUG
	assert(lpBuffer != NULL && lpReadSize != NULL && *lpReadSize > 0);
	assert(pTunnel != NULL && pTunnel->lpHandle != INVALID_HANDLE_VALUE);
	assert(pTunnel->lpRead != NULL && ((OVERLAPPED *)pTunnel->lpRead)->hEvent != INVALID_HANDLE_VALUE);
#endif

	//Set size.
	nSize = *lpReadSize;
	//Read the data from the file.
	bResult = ReadFile(pTunnel->lpHandle,lpBuffer,nSize,lpReadSize,(OVERLAPPED *)pTunnel->lpRead);
	//Check result.
	if(!bResult && GetLastError() == ERROR_IO_PENDING)
	{
		//Get result.
		bResult = WaitForSingleObject(((OVERLAPPED *)pTunnel->lpRead)->hEvent,INFINITE) == WAIT_OBJECT_0;
        //OVERLAPPED structure's event has been signaled. 
		if(bResult)
		{
			//Get overlapped result.
			bResult = GetOverlappedResult(pTunnel->lpHandle,(OVERLAPPED *)pTunnel->lpRead,lpReadSize,_FALSE);
#ifdef _DEBUG
			LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
				"Tunnel::ReadNetworkTunnel : result(%d)/read size(%d) !",bResult,*lpReadSize);
#endif
		}
	}
	//Return result.
	return bResult;
}

////////////////////////////////////////////////////////////////////////////////
//
// Write network tunnel.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WriteNetworkTunnel(NetworkTunnel* pTunnel,_BYTE* lpBuffer,_INT32* lpWriteSize)
{
	//Result.
	_BOOL bResult;
	//Set size.
	_UINT32 nSize;

#ifdef _DEBUG
	assert(lpBuffer != NULL && lpWriteSize != NULL && *lpWriteSize > 0);
	assert(pTunnel != NULL && pTunnel->lpHandle != INVALID_HANDLE_VALUE);
	assert(pTunnel->lpWrite != NULL && ((OVERLAPPED *)pTunnel->lpWrite)->hEvent != INVALID_HANDLE_VALUE);
#endif

	//Set size.
	nSize = *lpWriteSize;
	//Write the data into the file.
	bResult = WriteFile(pTunnel->lpHandle,lpBuffer,nSize,lpWriteSize,(OVERLAPPED *)pTunnel->lpWrite);
	//Check result.
	if(!bResult && GetLastError() == ERROR_IO_PENDING)
	{
		//Get result.
		bResult = WaitForSingleObject(((OVERLAPPED *)pTunnel->lpWrite)->hEvent,INFINITE) == WAIT_OBJECT_0;
        //OVERLAPPED structure's event has been signaled. 
		if(bResult)
		{
			//Get overlapped result.
			bResult = GetOverlappedResult(pTunnel->lpHandle,(OVERLAPPED *)pTunnel->lpWrite,lpWriteSize,FALSE);
#ifdef _DEBUG
			LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
				"Tunnel::WriteNetworkTunnel : result(%d)/write size(%d) !",bResult,*lpWriteSize);
#endif
		}
	}
	//Return result.
	return bResult;
}
