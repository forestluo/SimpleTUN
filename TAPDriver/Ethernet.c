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
// Get protocol type comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetProtocolTypeComment(_UINT16 nProtocolType)
{
	//Check protocol type.
	switch(nProtocolType)
	{
	case 0x0600:
		return "XEROX NS IDP";
	case 0x0800:
		return "DOD InternetЭ��/IP";
	case 0x0801:
		return "X.75 Internet";
	case 0x0802:
		return "NBS Internet";
	case 0x0803:
		return "ECMA Internet";
	case 0x0804:
		return "Chaosnet";
	case 0x0805:
		return "X.25 ������";
	case 0x0806:
		return "��ַ����Э��/ARP";
	case 0x0807:
		return "XNS������";
	case 0x1000:
		return "Berkeley��β";
	case 0x5208:
		return "BBN Simnet";
	case 0x6001:
		return "DEC MOP ת��/װ��";
	case 0x6002:
		return "DEC MOP Զ�̿���̨";
	case 0x6003:
		return "DEC DECnet Phase IV";
	case 0x6004:
		return "DEC LAT";
	case 0x6005:
	case 0x6006:
		return "DEC";
	case 0x8005:
		return "HP probe";
	case 0x8010:
		return "Excelan";
	case 0x8035:
		return "����ARP";
	case 0x8038:
		return "DEC LANBridge";
	case 0x8098:
		return "Appletalk";
	default:
		return "Unknown";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get mac address type comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetMACAddressTypeComment(_UINT16 nMACAddressType)
{
	//Check MAC address type.
	switch(nMACAddressType)
	{
	case 1:
		return "��̫��(10MB)";
	case 2:
		return "��������̫��(3MB)";
	case 3:
		return "ҵ������X.25��";
	case 4:
		return "Proteon ProNet ���ƻ���";
	case 5:
		return "Chaos��";
	case 6:
		return "IEEE.802����";
	case 7:
		return "ARCNET";
	default:
		return "Unknow";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get ARP operation comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetARPOperationComment(_UINT16 nOperation)
{
	//Check operation.
	switch(nOperation)
	{
	case 1:
		return "ARP����";
	case 2:
		return "ARPӦ��";
	default:
		return "Unknow";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get ICMP type comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetICMPTypeComment(_UINT8 nType)
{
	//Check type.
	switch(nType)
	{
	case 0:
		return "����(echo)�ش�";
	case 3:
		return "���޲��ɵ���";
	case 4:
		return "��Դ����";
	case 5:
		return "�ض���";
	case 8:
		return "����(echo)����";
	case 9:
		return "·��������";
	case 10:
		return "·��������";
	case 11:
		return "��ʱ";
	case 12:
		return "�����������";
	case 13:
		return "ʱ�������";
	case 14:
		return "ʱ���Ӧ��";
	case 15:
		return "��Ϣ����";
	case 16:
		return "��ϢӦ��";
	case 17:
		return "��ַ��������";
	case 18:
		return "��ַ����Ӧ��";
	default:
		return "Unknow";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get ICMP code comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetICMPCodeComment(_UINT8 nCode)
{
	//Check code.
	switch(nCode)
	{
	case 0:
		return "����";
	case 1:
		return "�������ɵ���";
	case 2:
		return "Э�鲻�ɵ���";
	case 3:
		return "�˿ڲ��ɵ���";
	case 4:
		return "��Ҫ���зֶΣ���ȴ�����˽�ֹ�ֶα�־";
	case 5:
		return "Դ·��ʧ��";
	case 6:
		return "Ŀ������δ֪";
	case 7:
		return "Ŀ������δ֪";
	case 8:
		return "Դ��������(����ʹ�û��ʱ)";
	case 9:
		return "�����Խ�ֹĿ������";
	case 10:
		return "�����Խ�ֹĿ������";
	case 11:
		return "�����޷��ṩָ����TOS";
	case 12:
		return "�����޷��ṩָ����TOS";
	case 13:
		return "�����Խ�ֹͨѶ";
	case 14:
		return "Υ���������ȼ�";
	case 15:
		return "���ȼ�ֹͣʹ��";
	default:
		return "Unknow";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get IP protocol comment.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetIPProtocolComment(_UINT8 nProtocol)
{
	//Check protocol.
	switch(nProtocol)
	{
	case 1:
		return "ICMP/���ʿ��Ʊ���Э��";
	case 2:
		return "IGMP/���������Э��";
	case 3:
		return "GGP/���ص�����Э��";
	case 5:
		return "ST/��";
	case 6:
		return "TCP/�������Э��";
	case 7:
		return "UCL";
	case 8:
		return "EGP/�ⲿ����Э��";
	case 9:
		return "IGP/�ڲ�����Э��";
	case 10:
		return "BBN-MON/BBN-RCC���";
	case 11:
		return "NVP-II/��������Э��";
	case 12:
		return "PUP";
	case 13:
		return "ARGUS";
	case 14:
		return "EMCON";
	case 15:
		return "XNET/Խ��������";
	case 16:
		return "CHAOS";
	case 17:
		return "UDP/�û����ݱ�Э��";
	case 18:
		return "MUX/��·����";
	case 19:
		return "DCN-MEAS/DCN������ϵͳ";
	case 20:
		return "HMP/�������Э��";
	case 21:
		return "PRM/�������߼��";
	case 22:
		return "XNS-IDP/Xerox NS IDP";
	case 23:
		return "TRUNK-1";
	case 24:
		return "TRUNK-2";
	case 25:
		return "LEAF-1";
	case 26:
		return "LEAF-2";
	case 27:
		return "RDP/�ɿ�������Э��";
	case 28:
		return "IPTP/Internet�ɿ���TP";
	case 29:
		return "ISO-TP4";
	case 30:
		return "NETBLT/������ݴ���";
	case 31:
		return "MEF-NSP/MFE�������";
	case 32:
		return "MERIT-INP/MERIT�ڵ��Э��";
	case 33:
		return "SEP/˳�򽻻�";
	case 61:
		return "�κ������ڲ�Э��";
	case 62:
		return "CFTP";
	case 63:
		return "�κξ�����Э��";
	case 64:
		return "SAT-EXPAK/SATNET��Backroom EXPAK";
	case 65:
		return "MIT-SUBN/MIT����֧��";
	case 66:
		return "RVD/MITԶ���������";
	case 67:
		return "IPPC/Internet Plur.�������";
	case 68:
		return "�κηֲ�ʽ�ļ�ϵͳ";
	case 69:
		return "SAT-MON/SATNET���";
	case 71:
		return "IPCV/�������Ӧ��";
	case 76:
		return "BRSAT-MON/Backroom SATNET���";
	case 78:
		return "WB-MON/������";
	case 79:
		return "WB-EXPAK/���EXPAK";
	case 0:
	case 255:
		return "����";
	default:
		return "δ����";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump mac address.
//
////////////////////////////////////////////////////////////////////////////////

void DumpMACAddress(_STRING lpstrName,_MAC6 macAddress)
{
#ifdef _DEBUG
	assert(lpstrName != NULL);
#endif

	//Print MAC address.
	LogRequestedFormat(LOG_PACKET | LOG_INFORMATION,
		"\t%s = %02x-%02x-%02x-%02x-%02x-%02x",
		lpstrName,
		macAddress[0],macAddress[1],macAddress[2],
		macAddress[3],macAddress[4],macAddress[5]);
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump IP address.
//
////////////////////////////////////////////////////////////////////////////////

void DumpIPAddress(_STRING lpstrName,_IPV4 ipAddress)
{
#ifdef _DEBUG
	assert(lpstrName != NULL);
#endif

	//Print MAC address.
	LogRequestedFormat(LOG_PACKET | LOG_INFORMATION,
		"\t%s = %d.%d.%d.%d",
		lpstrName,
		ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3]);
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize UDP packet.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeUDPPacket(UDPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(UDPPacket));
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap UDP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapUDPPacket(SimpleBuffer* lpBuffer,UDPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Set source port.
	if(!SetShort(lpBuffer,lpPacket->nSourcePort))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapUDPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set destination port.
	if(!SetShort(lpBuffer,lpPacket->nDestinationPort))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapUDPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Calculate length.
	lpPacket->nLength = lpPacket->buffer.nCount + 4 * sizeof(_UINT16);
	//Set length.
	if(!SetShort(lpBuffer,lpPacket->nLength))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapUDPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set checksum.
	if(!SetShort(lpBuffer,lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapUDPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check count.
	if(lpPacket->buffer.nCount > 0)
	{
		//Set bytes.
		if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->buffer.block,lpPacket->buffer.nCount))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::WrapUDPPacket : fail to set bytes !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap UDP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapUDPPacket(SimpleBuffer* lpBuffer,UDPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get source port.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nSourcePort))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapUDPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get destination port.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nDestinationPort))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapUDPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get length.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nLength))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapUDPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get checksum.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapUDPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Initialize buffer.
	InitializeBuffer(&lpPacket->buffer);
	//Get bytes.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->buffer.block,lpPacket->nLength - 4 * sizeof(_UINT16)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapUDPPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Set count.
	lpPacket->buffer.nCount = lpPacket->nLength - 4 * sizeof(_UINT16);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump UDP packet.
//
////////////////////////////////////////////////////////////////////////////////

void DumpUDPPacket(UDPPacket* lpPacket)
{
	//Format pointer.
	_STRING lpstrFormated;
	//Formated block.
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Set formated.
	lpstrFormated = (_STRING)blockFormated;
	//Print.
	lpstrFormated = FormatLine(lpstrFormated,
		"Ethernet::DumpUDPPacket : dump packet !");
	//Print source port.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tSource Port = %d",lpPacket->nSourcePort);
	//Print destination port.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tDestination Port = %d",lpPacket->nDestinationPort);
	//Print length.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tLength = %d",lpPacket->nLength);
	//Print checksum.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tChecksum = 0x%04x",lpPacket->nChecksum);
	//Dump buffer.
	lpstrFormated = DumpBuffer(lpstrFormated,&lpPacket->buffer);

	//Log event.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_PACKET | LOG_INFORMATION);
}


////////////////////////////////////////////////////////////////////////////////
//
// Get UDP packet checksum.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetUDPPacketChecksum(_IPV4 ipSource,_IPV4 ipDestination,UDPPacket* lpPacket)
{
	//Buffer
	SimpleBuffer buffer;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Initialize buffer.
	InitializeBuffer(&buffer);

	//Set bytes.
	if(!SetBytes(&buffer,(_BYTE *)ipSource,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetUDPPacketChecksum : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set bytes.
	if(!SetBytes(&buffer,(_BYTE *)ipDestination,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetUDPPacketChecksum : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set short.
	if(!SetShort(&buffer,(_SHORT)17))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetUDPPacketChecksum : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set short.
	if(!SetShort(&buffer,lpPacket->nLength))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetUDPPacketChecksum : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Clear checksum.
	lpPacket->nChecksum = 0;
	//Wrap UDP packet.
	if(!WrapUDPPacket(&buffer,lpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetUDPPacketChecksum : fail to wrap packet !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Get checksum.
	lpPacket->nChecksum = GetChecksum16((_BYTE *)&buffer.block,buffer.nCount);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize TCP packet.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeTCPPacket(TCPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(TCPPacket));
}

////////////////////////////////////////////////////////////////////////////////
//
// ICMP packet functions.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeICMPPacket(ICMPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(ICMPPacket));
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap ICMP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapICMPPacket(SimpleBuffer* lpBuffer,ICMPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Set type.
	if(!SetByte(lpBuffer,lpPacket->nType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set code.
	if(!SetByte(lpBuffer,lpPacket->nCode))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set checksum.
	if(!SetShort(lpBuffer,lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set id.
	if(!SetShort(lpBuffer,lpPacket->nID))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set sequence number.
	if(!SetShort(lpBuffer,lpPacket->nSequenceNumber))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check count.
	if(lpPacket->buffer.nCount > 0)
	{
		//Set bytes.
		if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->buffer.block,lpPacket->buffer.nCount))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::WrapICMPPacket : fail to set bytes !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap ICMP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapICMPPacket(SimpleBuffer* lpBuffer,ICMPPacket* lpPacket)
{
	//Offset.
	_INT32 nOffset;

#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get type.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get code.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nCode))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get checksum.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get id.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nID))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get sequence number.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nSequenceNumber))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Initialize buffer.
	InitializeBuffer(&lpPacket->buffer);

	//Get offset.
	nOffset = lpBuffer->nOffset;
	//Get bytes.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->buffer.block,lpBuffer->nCount - nOffset))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapICMPPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Set size.
	lpPacket->buffer.nCount = lpBuffer->nCount - nOffset;

	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump ICMP packet.
//
////////////////////////////////////////////////////////////////////////////////

void DumpICMPPacket(ICMPPacket* lpPacket)
{
	//Format pointer.
	_STRING lpstrFormated;
	//Formated block.
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Set formated.
	lpstrFormated = (_STRING)blockFormated;
	//Print.
	lpstrFormated = FormatLine(lpstrFormated,
		"Ethernet::DumpICMPPacket : dump packet !");
	//Dump type.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tType = %d (%s)",lpPacket->nType,GetICMPTypeComment(lpPacket->nType));
	//Dump code.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tCode = %d (%s)",lpPacket->nCode,GetICMPCodeComment(lpPacket->nCode));
	//Dump checksum.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tChecksum = 0x%04x",lpPacket->nChecksum);
	//Dump id.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tID = %d",lpPacket->nID);
	//Dump sequence number.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tSequence Number = %d",lpPacket->nSequenceNumber);
	//Dump buffer.
	lpstrFormated = DumpBuffer(lpstrFormated,&lpPacket->buffer);

	//Log.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_PACKET | LOG_INFORMATION);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get ICMP packet checksum.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetICMPPacketChecksum(ICMPPacket* lpPacket)
{
	//Buffer
	SimpleBuffer buffer;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear checksum.
	lpPacket->nChecksum = 0;
	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Wrap ICMP packet.
	if(!WrapICMPPacket(&buffer,lpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetICMPPacketChecksum : fail to wrap packet !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Get checksum.
	lpPacket->nChecksum = GetChecksum16((_BYTE *)&buffer.block,buffer.nCount);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize IP packet.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeIPPacket(IPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(IPPacket));

	//Set version.
	lpPacket->nVersion = 4;
	//Set header lenght.
	lpPacket->nHeaderLength = 5;
	//Set type of service.
	lpPacket->nTypeOfService = 0;
	//Set id.
	lpPacket->nID = 0;
	//Set flags.
	lpPacket->nFlags = 0;
	//Set segment offset.
	lpPacket->nOffset = 0;
	//Set ttl.
	lpPacket->nTTL = 128;
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap IP packet header.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapIPPacketHeader(SimpleBuffer* lpBuffer,IPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Set version.
	if(!SetByte(lpBuffer,(_BYTE)(((lpPacket->nVersion << 4) & 0xF0) | (lpPacket->nHeaderLength & 0x0F))))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set type of service.
	if(!SetByte(lpBuffer,lpPacket->nTypeOfService))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set total length.
	if(!SetShort(lpBuffer,lpPacket->nTotalLength))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set id.
	if(!SetShort(lpBuffer,lpPacket->nID))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set flags and offset.
	if(!SetShort(lpBuffer,(_SHORT)(((lpPacket->nFlags << 13) & 0xE000) | (lpPacket->nOffset & 0x1FFF))))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set TTL.
	if(!SetByte(lpBuffer,lpPacket->nTTL))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set protocol.
	if(!SetByte(lpBuffer,lpPacket->nProtocol))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set checksum.
	if(!SetShort(lpBuffer,lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set source IP
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->ipSource,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set destination IP
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->ipDestination,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacketHeader : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap IP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapIPPacket(SimpleBuffer* lpBuffer,IPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Wrap IP packet header.
	if(!WrapIPPacketHeader(lpBuffer,lpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapIPPacket : fail to wrap IP header !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check protocol.
	switch(lpPacket->nProtocol)
	{
	//ICMP
	case 1:
		//Wrap ICMP packet.
		if(!WrapICMPPacket(lpBuffer,&lpPacket->icmpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::WrapIPPacket : fail to unwrap ICMP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		//Update total length.
		//Update checksum.
		break;
	//UDP
	case 17:
		//Wrap UDP packet.
		if(!WrapUDPPacket(lpBuffer,&lpPacket->udpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::WrapIPPacket : fail to unwrap udp packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		//Update total length.
		//Update checksum.
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::WrapIPPacket : protocol(%d) not supported !",
			lpPacket->nProtocol);
#endif
	}
	//Retrun true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap IP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapIPPacketHeader(SimpleBuffer* lpBuffer,IPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get version.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nVersion))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Set header length.
	lpPacket->nHeaderLength = lpPacket->nVersion & 0x0F;
	//Set version.
	lpPacket->nVersion = (lpPacket->nVersion >> 4) & 0x0F;

	//Get service type.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nTypeOfService))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get total length.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nTotalLength))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get id.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nID))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get flags and offset.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nOffset))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Set flags.
	lpPacket->nFlags = (lpPacket->nOffset >> 13) & 0x07;
	//Get offset.
	lpPacket->nOffset &= 0x1FFF;

	//Get TTL.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nTTL))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get protocol.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nProtocol))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get checksum.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nChecksum))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get source IP
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->ipSource,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get destination IP
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->ipDestination,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacketHeader : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap IP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapIPPacket(SimpleBuffer* lpBuffer,IPPacket* lpPacket)
{
	//Offset.
	_UINT32 nOffset;

#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get offset.
	nOffset = lpBuffer->nOffset;
	//Unwrap IP packet header.
	if(!UnwrapIPPacketHeader(lpBuffer,lpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacket : fail to unwrap IP header !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Check offset and skip options.
	nOffset = nOffset + lpPacket->nHeaderLength * 4;
	//Set offset.
	if(!SetBufferOffset(lpBuffer,nOffset,_TRUE))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapIPPacket : fail to set offset !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check protocol.
	switch(lpPacket->nProtocol)
	{
	//ICMP
	case 1:
		//Unwrap ICMP packet.
		if(!UnwrapICMPPacket(lpBuffer,&lpPacket->icmpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::UnwrapIPPacket : fail to unwrap ICMP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	//UDP
	case 17:
		//Unwrap UDP packet.
		if(!UnwrapUDPPacket(lpBuffer,&lpPacket->udpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::UnwrapIPPacket : fail to unwrap UDP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::UnwrapIPPacket : protocol(%d) not supported !",
			lpPacket->nProtocol);
#endif
	}
	//Retrun true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump IP packet.
//
////////////////////////////////////////////////////////////////////////////////

void DumpIPPacket(IPPacket* lpPacket)
{
	//Format pointer.
	_STRING lpstrFormated;
	//Formated block.
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Set formated.
	lpstrFormated = (_STRING)blockFormated;
	//Print.
	lpstrFormated = FormatLine(lpstrFormated,
		"Ethernet::DumpIPPacket : dump packet !");
	//Print version.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tVersion = IPv%d",lpPacket->nVersion);
	//Print length of header.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tHeader Length = %d x 32bits (%s)",
		lpPacket->nHeaderLength,(lpPacket->nHeaderLength <= 5) ? "����QOS" : "��QOS");
	//Print service type.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tType Of Service = 0x%02x",lpPacket->nTypeOfService);
	lpstrFormated = FormatLine(lpstrFormated,
		"\t\tpriority = %d",
		(lpPacket->nTypeOfService >> 5) & 0x07);
	lpstrFormated = FormatLine(lpstrFormated,
		"\t\tD Bit = %d (%s)",
		(lpPacket->nTypeOfService >> 4) & 0x01,((lpPacket->nTypeOfService >> 4) & 0x01) ? "�ӳ�" : "���ӳ�");
	lpstrFormated = FormatLine(lpstrFormated,
		"\t\tT bit = %d (%s)",
		(lpPacket->nTypeOfService >> 3) & 0x01,((lpPacket->nTypeOfService >> 3) & 0x01) ? "Ҫ��ϸ�������" : "����Ҫ��");
	lpstrFormated = FormatLine(lpstrFormated,
		"\t\tR bit = %d (%s)",
		(lpPacket->nTypeOfService >> 2) & 0x01,((lpPacket->nTypeOfService >> 2) & 0x01) ? "Ҫ��ϸ߿ɿ���" : "����Ҫ��");
	lpstrFormated = FormatLine(lpstrFormated,
		"\t\tC bit = %d (%s)",
		(lpPacket->nTypeOfService >> 1) & 0x01,((lpPacket->nTypeOfService >> 1) & 0x01) ? "Ҫ��ϵͽ�Ǯ����" : "����Ҫ��");
	//Print length of packet.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tTotal Length = %u",lpPacket->nTotalLength);
	//Print id.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tnID = %d",lpPacket->nID);
	//Print flags.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tFlags = 0x%02x (%s)",
		lpPacket->nFlags,lpPacket->nFlags == 0 ? "���ְ�" : "�ְ�");
	//Print segment offset.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tSegment Offset = %d Byte(s)",lpPacket->nOffset);
	//Print ttl.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tTTL = %u",lpPacket->nTTL);
	//Print protocol.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tProtocol = %d (%s)",
		lpPacket->nProtocol,GetIPProtocolComment(lpPacket->nProtocol));
	//Print checksum.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tChecksum = 0x%04x",lpPacket->nChecksum);
	//Print IP address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %d.%d.%d.%d",
		"Source IP Address",
		lpPacket->ipSource[0],lpPacket->ipSource[1],
		lpPacket->ipSource[2],lpPacket->ipSource[3]);
	//Print IP address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %d.%d.%d.%d",
		"Destination IP Address",
		lpPacket->ipDestination[0],lpPacket->ipDestination[1],
		lpPacket->ipDestination[2],lpPacket->ipDestination[3]);
	//Print length of data.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tData Length = %d",lpPacket->nTotalLength - lpPacket->nHeaderLength * 4);

	//Log event.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_PACKET | LOG_INFORMATION);

	//Check protocol.
	switch(lpPacket->nProtocol)
	{
	//ICMP
	case 1:
		//Dump icmp packet.
		DumpICMPPacket(&lpPacket->icmpPacket);
		break;
	//UDP
	case 17:
		//Dump udp packet.
		DumpUDPPacket(&lpPacket->udpPacket);
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::DumpIPPacket : protocol(%d) not supported !",
			lpPacket->nProtocol);
#endif
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get IP packet checksum.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetIPPacketChecksum(IPPacket* lpPacket)
{
	//Buffer
	SimpleBuffer buffer;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear checksum.
	lpPacket->nChecksum = 0;
	//Initialize buffer.
	InitializeBuffer(&buffer);
	//Wrap IP packet header.
	if(!WrapIPPacketHeader(&buffer,lpPacket))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::GetIPPacketChecksum : fail to wrap packet !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Get checksum.
	lpPacket->nChecksum = GetChecksum16((_BYTE *)&buffer.block,buffer.nCount);
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize ARP packet.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeARPPacket(ARPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(ARPPacket));

	//Set MAC address type.
	lpPacket->nMACAddressType = 1;
	//Set protocol address type.
	lpPacket->nProtocolAddressType = 0x0800;
	//Set MAC address size.
	lpPacket->nMACAddressSize = 6;
	//Set protocol address size.
	lpPacket->nProtocolAddressSize = 4;
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap ARP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapARPPacket(SimpleBuffer* lpBuffer,ARPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Set mac address type.
	if(!SetShort(lpBuffer,lpPacket->nMACAddressType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set protocol address type.
	if(!SetShort(lpBuffer,lpPacket->nProtocolAddressType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set mac address size.
	if(!SetByte(lpBuffer,lpPacket->nMACAddressSize))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set protocol address size.
	if(!SetByte(lpBuffer,lpPacket->nProtocolAddressSize))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set operation.
	if(!SetShort(lpBuffer,lpPacket->nOperation))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set source mac address.
	if(!SetBytes(lpBuffer,lpPacket->macSource,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set source ip address.
	if(!SetBytes(lpBuffer,lpPacket->ipSource,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set destination mac address.
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->macDestination,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set destination ip address.
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->ipDestination,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapARPPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap ARP packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapARPPacket(SimpleBuffer* lpBuffer,ARPPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get mac address type.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nMACAddressType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get protocol address type.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nProtocolAddressType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get mac address size.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nMACAddressSize))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get protocol address size.
	if(!GetByte(lpBuffer,(_BYTE *)&lpPacket->nProtocolAddressSize))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get byte !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get operation.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->nOperation))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get source mac address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->macSource,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get source ip address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->ipSource,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get destination mac address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->macDestination,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get destination ip address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->ipDestination,sizeof(_IPV4)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapARPPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump ARP packet.
//
////////////////////////////////////////////////////////////////////////////////

void DumpARPPacket(ARPPacket* lpPacket)
{
	//Format pointer.
	_STRING lpstrFormated;
	//Formated block.
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Set formated.
	lpstrFormated = (_STRING)blockFormated;
	//Print.
	lpstrFormated = FormatLine(lpstrFormated,
						"Ethernet::DumpARPPacket : dump packet !");
	//Print MAC address type.
	lpstrFormated = FormatLine(lpstrFormated,
						"\tMAC Address Type = %d (%s)",
						lpPacket->nMACAddressType,GetMACAddressTypeComment(lpPacket->nMACAddressType));
	//Print protocol address type.
	lpstrFormated = FormatLine(lpstrFormated,
						"\tProtocol Address Type = 0x%04x (%s)",
						lpPacket->nProtocolAddressType,GetProtocolTypeComment(lpPacket->nProtocolAddressType));
	//Print MAC address size.
	lpstrFormated = FormatLine(lpstrFormated,
						"\tMAC Address Size = %d",lpPacket->nMACAddressSize);
	//Print protocol address size.
	lpstrFormated = FormatLine(lpstrFormated,
						"\tProtocol Address Size = %d",lpPacket->nProtocolAddressSize);
	//Print operation.
	lpstrFormated = FormatLine(lpstrFormated,
						"\tOperation = %d (%s)",
						lpPacket->nOperation,GetARPOperationComment(lpPacket->nOperation));
	//Print MAC address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %02x-%02x-%02x-%02x-%02x-%02x",
		"Source MAC Address",
		lpPacket->macSource[0],lpPacket->macSource[1],lpPacket->macSource[2],
		lpPacket->macSource[3],lpPacket->macSource[4],lpPacket->macSource[5]);
	//Print IP address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %d.%d.%d.%d",
		"Source IP Address",
		lpPacket->ipSource[0],lpPacket->ipSource[1],
		lpPacket->ipSource[2],lpPacket->ipSource[3]);
	//Print MAC address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %02x-%02x-%02x-%02x-%02x-%02x",
		"Destination MAC Address",
		lpPacket->macDestination[0],lpPacket->macDestination[1],lpPacket->macDestination[2],
		lpPacket->macDestination[3],lpPacket->macDestination[4],lpPacket->macDestination[5]);
	//Print IP address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %d.%d.%d.%d",
		"Destination IP Address",
		lpPacket->ipDestination[0],lpPacket->ipDestination[1],
		lpPacket->ipDestination[2],lpPacket->ipDestination[3]);

	//Log event.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_PACKET | LOG_INFORMATION);
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize ethernet packet.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeEthernetPacket(EthernetPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif
	//Clear.
	memset(lpPacket,0,sizeof(EthernetPacket));
}

////////////////////////////////////////////////////////////////////////////////
//
// Wrap ethernet packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL WrapEthernetPacket(SimpleBuffer* lpBuffer,EthernetPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Set destination mac address.
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->header.macDestination,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set source mac address.
	if(!SetBytes(lpBuffer,(_BYTE *)lpPacket->header.macSource,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to set bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Set protocol type.
	if(!SetShort(lpBuffer,lpPacket->header.nProtocolType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to set short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check protocol.
	switch(lpPacket->header.nProtocolType)
	{
	case 0x0806:
		//Wrap ARP packet.
		if(!WrapARPPacket(lpBuffer,&lpPacket->arpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::WrapEthernetPacket : fail to wrap ARP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	case 0x0800:
		//Wrap IP packet.
		if(!WrapIPPacket(lpBuffer,&lpPacket->ipPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to wrap IP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::WrapEthernetPacket : protocol(0x%04x) not supported !",
			lpPacket->header.nProtocolType);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unwrap ethernet packet.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL UnwrapEthernetPacket(SimpleBuffer* lpBuffer,EthernetPacket* lpPacket)
{
#ifdef _DEBUG
	assert(lpBuffer != NULL && lpPacket != NULL);
#endif

	//Get destination mac address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->header.macDestination,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get source mac address.
	if(!GetBytes(lpBuffer,(_BYTE *)lpPacket->header.macSource,sizeof(_MAC6)))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to get bytes !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Get protocol type.
	if(!GetShort(lpBuffer,(_SHORT *)&lpPacket->header.nProtocolType))
	{
#ifdef _DEBUG
		LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to get short !",
			LOG_PACKET | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Check protocol.
	switch(lpPacket->header.nProtocolType)
	{
	case 0x0806:
		//Unwrap ARP packet.
		if(!UnwrapARPPacket(lpBuffer,&lpPacket->arpPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to unwrap ARP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	case 0x0800:
		//Unwrap IP packet.
		if(!UnwrapIPPacket(lpBuffer,&lpPacket->ipPacket))
		{
#ifdef _DEBUG
			LogRequestedEvent("Ethernet::UnwrapEthernetPacket : fail to unwrap IP packet !",
				LOG_PACKET | LOG_EXCEPTION);
#endif
			return _FALSE;
		}
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::UnwrapEthernetPacket : protocol(0x%04x) not supported !",
			lpPacket->header.nProtocolType);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Dump ethernet packet.
//
////////////////////////////////////////////////////////////////////////////////

void DumpEthernetPacket(EthernetPacket* lpPacket)
{
	//Format pointer.
	_STRING lpstrFormated;
	//Formated block.
	_BLOCK blockFormated;

#ifdef _DEBUG
	assert(lpPacket != NULL);
#endif

	//Clear block.
	memset(blockFormated,0,BLOCK_SIZE);
	//Set formated.
	lpstrFormated = (_STRING)blockFormated;
	//Print.
	lpstrFormated = FormatLine(lpstrFormated,
		"Ethernet::DumpEthernetPacket : show packets !");
	//Print MAC address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %02x-%02x-%02x-%02x-%02x-%02x",
		"Destination MAC Address",
		lpPacket->header.macDestination[0],lpPacket->header.macDestination[1],lpPacket->header.macDestination[2],
		lpPacket->header.macDestination[3],lpPacket->header.macDestination[4],lpPacket->header.macDestination[5]);
	//Print MAC address.
	lpstrFormated = FormatLine(lpstrFormated,
		"\t%s = %02x-%02x-%02x-%02x-%02x-%02x",
		"Source MAC Address",
		lpPacket->header.macSource[0],lpPacket->header.macSource[1],lpPacket->header.macSource[2],
		lpPacket->header.macSource[3],lpPacket->header.macSource[4],lpPacket->header.macSource[5]);
	//Print value.
	lpstrFormated = FormatLine(lpstrFormated,
		"\tProtocol Type = 0x%04x (%s)",
		lpPacket->header.nProtocolType,GetProtocolTypeComment(lpPacket->header.nProtocolType));

	//Log event.
	LogRequestedEvent((_STRING)blockFormated,
		LOG_PACKET | LOG_INFORMATION);

	//Check protocol type.
	switch(lpPacket->header.nProtocolType)
	{
	case 0x0806:
		//Dump ARP packet.
		DumpARPPacket(&lpPacket->arpPacket);
		break;
	case 0x0800:
		//Dump IP Packet.
		DumpIPPacket(&lpPacket->ipPacket);
		break;
	default:
#ifdef _DEBUG
		LogRequestedFormat(LOG_PACKET | LOG_WARNNING,
			"Ethernet::DumpEthernetPacket : protocol(0x%04x) not supported !",
			lpPacket->header.nProtocolType);
#endif
	}
}
