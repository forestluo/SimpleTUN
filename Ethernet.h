#ifndef _SIMPLE_ETHERNET_H
#define _SIMPLE_ETHERNET_H

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//MAC Address
typedef _UINT8 _MAC6[6];
//IP Address
typedef _UINT8 _IPV4[4];

//UDP Packet
typedef struct tagUDPPacket
{
	//Source Port
	_UINT16 nSourcePort;
	//Destination Port
	_UINT16 nDestinationPort;
	//Length
	_UINT16 nLength;
	//Checksum
	_UINT16 nChecksum;

	//Data
	SimpleBuffer buffer;
}

UDPPacket;

//TCP Packet
typedef struct tagTCPPacket
{
	//Source Port
	_UINT16 nSourcePort;
	//Destination Port
	_UINT16 nDestinationPort;
	//Sequence Number
	_UINT32 nSequenceNumber;
	//Acknowledgment Number
	_UINT32 nAcknowledgmentNumber;
	//Offset
	_UINT8 nOffset;
	//Flags
	_BOOL bURG,bACK,bPSH,bRST,bSYN,bFIN;
	//Window Size
	_UINT16 nWindowSize;
	//Checksum
	_UINT16 nChecksum;
	//Urgent Pointer
	_UINT16 nUrgentPointer;
}

TCPPacket;

//ICMP Header
typedef struct tagICMPPacket
{
	//Type
	_UINT8 nType;
	//Code
	_UINT8 nCode;
	//Checksum
	_UINT16 nChecksum;
	//ID
	_UINT16 nID;
	//Sequence Number
	_UINT16 nSequenceNumber;

	//Data
	SimpleBuffer buffer;
}

ICMPPacket;

//IP Header
typedef struct tagIPPacket
{
	//Version Information
	_UINT8 nVersion;
	//Header Length
	_UINT8 nHeaderLength;
	//Type of Service
	_UINT8 nTypeOfService;
	//Totoal Length
	_UINT16 nTotalLength;
	//ID
	_UINT16 nID;
	//Flags
	_UINT8 nFlags;
	//Offset
	_UINT16 nOffset;
	//TTL
	_UINT8 nTTL;
	//Protocol
	_UINT8 nProtocol;
	//Checksum
	_UINT16 nChecksum;
	//Source
	_IPV4 ipSource;
	//Destination
	_IPV4 ipDestination;

	//Packet
	union
	{
		//ICMP Packet
		ICMPPacket icmpPacket;
		//TCP Packet
		TCPPacket tcpPacket;
		//UDP Packet
		UDPPacket udpPacket;
	};
}

IPPacket;

//ARP Packet
typedef struct tagARPPacket
{
	//MAC Address Type
	_UINT16 nMACAddressType;
	//Protocol Address Type
	_UINT16 nProtocolAddressType;
	//MAC Address Size
	_UINT8 nMACAddressSize;
	//Protocol Address Size
	_UINT8 nProtocolAddressSize;
	//Operation
	_UINT16 nOperation;
	//Source MAC Address
	_MAC6 macSource;
	//Source IP Address
	_IPV4 ipSource;
	//Destination MAC Address
	_MAC6 macDestination;
	//Destination IP Address
	_IPV4 ipDestination;
}

ARPPacket;

//Ethernet Header
typedef struct tagEthernetHeader
{
	//Destination MAC Address
	_MAC6 macDestination;
	//Source MAC Address
	_MAC6 macSource;
	//Protocol Type
	_UINT16 nProtocolType;
}

EthernetHeader;

//Ethernet Packet
typedef struct tagEthernetPacket
{
	//Ethernet Header
	EthernetHeader header;
	//Protocol Data
	union
	{
		//IP Packet
		IPPacket ipPacket;
		//ARP Packet
		ARPPacket arpPacket;
	};
}

EthernetPacket;

////////////////////////////////////////////////////////////////////////////////
//
// UDP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeUDPPacket(UDPPacket* lpPacket);

extern _BOOL WrapUDPPacket(SimpleBuffer* lpBuffer,UDPPacket* lpPacket);
extern _BOOL UnwrapUDPPacket(SimpleBuffer* lpBuffer,UDPPacket* lpPacket);

extern void DumpUDPPacket(UDPPacket* lpPacket);

extern _UINT32 GetUDPPacketChecksum(_IPV4 ipSource,_IPV4 ipDestination,UDPPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////
//
// TCP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeTCPPacket(TCPPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////
//
// ICMP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeICMPPacket(ICMPPacket* lpPacket);

extern _BOOL WrapICMPPacket(SimpleBuffer* lpBuffer,ICMPPacket* lpPacket);
extern _BOOL UnwrapICMPPacket(SimpleBuffer* lpBuffer,ICMPPacket* lpPacket);

extern void DumpICMPPacket(ICMPPacket* lpPacket);

extern _UINT32 GetICMPPacketChecksum(ICMPPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////
//
// IP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeIPPacket(IPPacket* lpPacket);

extern _BOOL WrapIPPacketHeader(SimpleBuffer* lpBuffer,IPPacket* lpPacket);
extern _BOOL WrapIPPacket(SimpleBuffer* lpBuffer,IPPacket* lpPacket);

extern _BOOL UnwrapIPPacketHeader(SimpleBuffer* lpBuffer,IPPacket* lpPacket);
extern _BOOL UnwrapIPPacket(SimpleBuffer* lpBuffer,IPPacket* lpPacket);

extern void DumpIPPacket(IPPacket* lpPacket);

extern _UINT32 GetIPPacketChecksum(IPPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////
//
// ARP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeARPPacket(ARPPacket* lpPacket);

extern _BOOL WrapARPPacket(SimpleBuffer* lpBuffer,ARPPacket* lpPacket);
extern _BOOL UnwrapARPPacket(SimpleBuffer* lpBuffer,ARPPacket* lpPacket);

extern void DumpARPPacket(ARPPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////
//
// Ethernet packet functions.
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeEthernetPacket(EthernetPacket* lpPacket);

extern _BOOL WrapEthernetPacket(SimpleBuffer* lpBuffer,EthernetPacket* lpPacket);
extern _BOOL UnwrapEthernetPacket(SimpleBuffer* lpBuffer,EthernetPacket* lpPacket);

extern void DumpEthernetPacket(EthernetPacket* lpPacket);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
