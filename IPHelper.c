////////////////////////////////////////////////////////////////////////////////
//
// General including files
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
#include <Iphlpapi.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Genernal definations.
//
////////////////////////////////////////////////////////////////////////////////

//Adapters Information List
IP_ADAPTER_INFO* theAdaptersInformationList						= NULL;
//Interface Information List
IP_INTERFACE_INFO* theInterfaceInformationList					= NULL;

////////////////////////////////////////////////////////////////////////////////
//
// Load adapters information list.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LoadAdaptersInformationList()
{
	//Size.
	_UINT32 nSize;
	//Status
	_UINT32 nStatus;

#ifdef _DEBUG
	assert(theAdaptersInformationList == NULL);
#endif

	//Set size.
	nSize = 0;
	//Get size of adapters information.
	nStatus = GetAdaptersInfo(NULL,&nSize);
	//Check result.
	if(nStatus != ERROR_BUFFER_OVERFLOW)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::LoadAdaptersInformationList : fail to get size !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	PrintLine(stdout,"IPHelper::LoadAdaptersInformationList : IP_ADAPTER_INFO(%d)/%d !",sizeof(IP_ADAPTER_INFO),nSize);
#endif

	//Create adapters information list.
	theAdaptersInformationList = (IP_ADAPTER_INFO *)malloc(nSize);
#ifdef _DEBUG
	assert(theAdaptersInformationList != NULL);
#endif
	//Clear adapters information list.
	memset(theAdaptersInformationList,0,nSize);

	//Get adapters information list.
	nStatus = GetAdaptersInfo(theAdaptersInformationList,&nSize);
	//Check result.
	if(nStatus != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::LoadAdaptersInformationList : fail to get list !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Show adapters information list
//
////////////////////////////////////////////////////////////////////////////////

void ShowAdaptersInformationList()
{
	//Count
	_UINT32 nCount = 0;
	//Index.
	_INT32 nIndex = 0;
	//Current member.
	IP_ADAPTER_INFO* pCurrent;

#ifdef _DEBUG
	assert(theAdaptersInformationList != NULL);
#endif

	//Print.
	PrintLine(stdout,"IPHelper::ShowAdaptersInformationList : show adapters information !");
	//Get current memeber.
	pCurrent = theAdaptersInformationList;
	//Check index.
	do
	{
		//Print.
		PrintLine(stdout,"Adapter[%d]",nIndex);
		//Print.
		PrintLine(stdout,"\tAdapter Index: %d",pCurrent->Index);
		//Print.
		PrintLine(stdout,"\tAdapter Name: %s",pCurrent->AdapterName);
		//Print.
		PrintLine(stdout,"\tMAC Address : %02x-%02x-%02x-%02x-%02x-%02x",
			pCurrent->Address[0],pCurrent->Address[1],pCurrent->Address[2],
			pCurrent->Address[3],pCurrent->Address[4],pCurrent->Address[5]);
		//Print.
		PrintLine(stdout,"\tDescription: %s",pCurrent->Description);
		//Print.
		PrintLine(stdout,"\tIP Address : %s",pCurrent->IpAddressList.IpAddress.String);
		//Print
		PrintLine(stdout,"\tIP Mask : %s",pCurrent->IpAddressList.IpMask.String);
		//Print.
		PrintLine(stdout,"\tGateway IP : %s",pCurrent->GatewayList.IpAddress.String);

		//Add index.
		nIndex ++;
		//Set next.
		pCurrent = pCurrent->Next;

	}while(pCurrent != NULL);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter information by index.
//
////////////////////////////////////////////////////////////////////////////////

IP_ADAPTER_INFO* GetAdapterInformationByIndex(_UINT32 nAdapterIndex)
{
	//Current member.
	IP_ADAPTER_INFO* pCurrent;

#ifdef _DEBUG
	assert(theAdaptersInformationList != NULL);
#endif

	//Get current memeber.
	pCurrent = theAdaptersInformationList;
	//Check index.
	do
	{
		//Check result.
		if(pCurrent->Index == nAdapterIndex)
		{
			//Return result.
			return pCurrent;
		}
		//Set next.
		pCurrent = pCurrent->Next;

	}while(pCurrent != NULL);
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter ip count.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 GetAdapterIPCount(IP_ADAPTER_INFO* lpAdapterInformation)
{
	//Count
	_INT32 nCount = 0;
	//IP Address
	IP_ADDR_STRING* lpAddress;

#ifdef _DEBUG
	assert(lpAdapterInformation != NULL);
#endif

	//Get header.
	lpAddress = &lpAdapterInformation->IpAddressList;
	//Check result.
	while(lpAddress != NULL)
	{
		//Add count.
		nCount ++;
		//Set next.
		lpAddress = lpAddress->Next;
	}
	//Return count.
	return nCount;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter MAC address.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetAdapterMACAddress(_UINT32 nAdapterIndex,_MAC6 macAddress)
{
	//Index.
	_INT32 nIndex;
	//Adapter.
	IP_ADAPTER_INFO* pAdapter;

	//Get adapter.
	pAdapter = GetAdapterInformationByIndex(nAdapterIndex);
	//Check result.
	if(pAdapter != NULL)
	{
		//Copy address.
		for(nIndex = 0;nIndex < sizeof(_MAC6);nIndex ++)
		{
			//Set mac address.
			macAddress[nIndex] = pAdapter->Address[nIndex];
		}
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter DHCP status.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL GetAdapterDHCPStatus(_UINT32 nAdapterIndex,_BOOL* lpStatus)
{
	//Current member.
	IP_ADAPTER_INFO* pCurrent;

#ifdef _DEBUG
	assert(theAdaptersInformationList != NULL);
#endif

	//Get current memeber.
	pCurrent = theAdaptersInformationList;
	//Check index.
	do
	{
		//Check result.
		if(pCurrent->Index == nAdapterIndex)
		{
			//Set status.
			*lpStatus = pCurrent->DhcpEnabled;
			//Return true.
			return _TRUE;
		}
		//Set next.
		pCurrent = pCurrent->Next;

	}while(pCurrent != NULL);
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Delete adapter addresses.
//
////////////////////////////////////////////////////////////////////////////////

void DeleteAdapterAddresses(_UINT32 nAdapterIndex)
{
	//Result.
	_UINT32 nResult;
	//Adapter.
	IP_ADAPTER_INFO* pAdapter;
	//Address.
	IP_ADDR_STRING* lpAddress;

	//Get adapter.
	pAdapter = GetAdapterInformationByIndex(nAdapterIndex);
	//Check result.
	if(pAdapter != NULL)
	{
		//Get address.
		lpAddress = &pAdapter->IpAddressList;
		//Do while.
		while(lpAddress != NULL)
		{
			//Delete ip address.
			nResult = DeleteIPAddress(lpAddress->Context);
			//Check result.
			if(nResult == NO_ERROR)
			{
#ifdef _DEBUG
				LogRequestedEvent("IPHelper::DeleteAdapterAddresses : ip was deleted !",
					LOG_TUNNEL | LOG_EXCEPTION);
				//Print.
				PrintLine(stdout,"\tIP = %s",lpAddress->IpAddress.String);
				PrintLine(stdout,"\tNetmask = %s",lpAddress->IpMask.String);
#endif
			}
			else
			{
#ifdef _DEBUG
				LogRequestedFormat(LOG_TUNNEL | LOG_EXCEPTION,
					"IPHelper::DeleteAdapterAddresses : fail(%d) to delete ip !",
					nResult);
#endif
			}
			//Get next.
			lpAddress = lpAddress->Next;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Unload adapters information list.
//
////////////////////////////////////////////////////////////////////////////////

void UnloadAdaptersInformationList()
{
	//Check result.
	if(theAdaptersInformationList != NULL)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::UnloadAdaptersInformationList : list was freed !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
		//Free it.
		free(theAdaptersInformationList);
		//Clear it.
		theAdaptersInformationList = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Load interface information list.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LoadInterfaceInformationList()
{
	//Size.
	_UINT32 nSize;
	//Status
	_UINT32 nStatus;

#ifdef _DEBUG
	assert(theInterfaceInformationList == NULL);
#endif

	//Set size.
	nSize = 0;
	//Get size of interface information.
	nStatus = GetInterfaceInfo(NULL,&nSize);
	//Check result.
	if(nStatus != ERROR_INSUFFICIENT_BUFFER)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::LoadInterfaceInformationList : fail to get size !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	PrintLine(stdout,"IPHelper::LoadInterfaceInformationList : IP_INTERFACE_INFO(%d)/%d !",sizeof(IP_INTERFACE_INFO),nSize);
#endif

	//Create interface information list.
	theInterfaceInformationList = (IP_INTERFACE_INFO *)malloc(nSize);
#ifdef _DEBUG
	assert(theInterfaceInformationList != NULL);
#endif
	//Clear interface information list.
	memset(theInterfaceInformationList,0,nSize);

	//Get interface information list.
	nStatus = GetInterfaceInfo(theInterfaceInformationList,&nSize);
	//Check result.
	if(nStatus != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::LoadInterfaceInformationList : fail to get list !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Show interface information list
//
////////////////////////////////////////////////////////////////////////////////

void ShowInterfaceInformationList()
{
	//Index.
	_INT32 nIndex = 0;

#ifdef _DEBUG
	assert(theInterfaceInformationList != NULL);
#endif

	//Print.
	PrintLine(stdout,"IPHelper::ShowInterfaceInformationList : show interfaces information !");
	//Check index.
	while(nIndex < theInterfaceInformationList->NumAdapters)
	{
		//Print.
		PrintLine(stdout,"\tInterface[%d]",nIndex);
		//Print.
		PrintLine(stdout,"\tAdapter Index = %ld",theInterfaceInformationList->Adapter[nIndex].Index);
		//Print.
		PrintLine(stdout,"\tAdapter Name = \"%ws\"",theInterfaceInformationList->Adapter[nIndex].Name);

		//Add index.
		nIndex ++;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter index map.
//
////////////////////////////////////////////////////////////////////////////////

IP_ADAPTER_INDEX_MAP* GetAdapterIndexMap(_UINT32 nAdapterIndex)
{
	//Count.
	_INT32 nCount = 0;

#ifdef _DEBUG
	assert(theInterfaceInformationList != NULL);
#endif

	//Check index.
	while(nCount < (_INT32)theInterfaceInformationList->NumAdapters)
	{
		//Check result.
		if(theInterfaceInformationList->Adapter[nCount].Index = nAdapterIndex)
		{
			//Return result.
			return &theInterfaceInformationList->Adapter[nCount];
		}
		//Add index.
		nCount ++;
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get adapter index by guid.
//
////////////////////////////////////////////////////////////////////////////////

_UINT32 GetAdapterIndexByGuid(_STRING lpstrGuid)
{
	//Index.
	_INT32 nIndex = 0;
	//Name.
	_PASCALSTRING strName;

#ifdef _DEBUG
	assert(theInterfaceInformationList != NULL);
#endif

	//Clear string.
	memset(strName,0,PASCAL_STRING_LENGTH);
	//Format.
	wsprintf((_STRING)strName,"\\DEVICE\\TCPIP_%s",lpstrGuid);

	//Check index.
	while(nIndex < theInterfaceInformationList->NumAdapters)
	{
		//Check result.
		if(wcscmp((_UINT16 *)strName,theInterfaceInformationList->Adapter[nIndex].Name))
		{
			//Return result.
			return theInterfaceInformationList->Adapter[nIndex].Index;
		}
		//Add index.
		nIndex ++;
	}
	//Return result.
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//
// Flush adapter ARP cache information.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL FlushAdapterARPCacheInformation(_UINT32 nAdapterIndex)
{
	//Check result.
	if(FlushIpNetTable(nAdapterIndex) != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::FlushAdapterARPCacheInformation : fail to flush ARP table !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Release adapter DHCP.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL ReleaseAdapterDHCPInformation(_UINT32 nAdapterIndex)
{
	//Index Map
	IP_ADAPTER_INDEX_MAP* pIndexMap;

	//Flush ip tables.
	pIndexMap = GetAdapterIndexMap(nAdapterIndex);
	//Check result.
	if(pIndexMap == NULL)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::ReleaseAdapterDHCPInformation : fail to get index map !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Release address.
	if(IpReleaseAddress(pIndexMap) != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::ReleaseAdapterDHCPInformation : fail to release address !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}


////////////////////////////////////////////////////////////////////////////////
//
// Renew adapter DHCP information.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RenewAdapterDHCPInformation(_UINT32 nAdapterIndex)
{
	//Index Map
	IP_ADAPTER_INDEX_MAP* pIndexMap;

	//Flush ip tables.
	pIndexMap = GetAdapterIndexMap(nAdapterIndex);
	//Check result.
	if(pIndexMap == NULL)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::RenewAdapterDHCPInformation : fail to get index map !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Release ip address.
	if(IpRenewAddress(pIndexMap) != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::RenewAdapterDHCPInformation : fail to renew address !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Add adapter IP address.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL AddAdapterIPAddress(_UINT32 nAdapterIndex,_IPV4 ipLocal,_IPV4 ipNetmask,_UINT32* lpContext,_UINT32* lpInstance)
{
	//Result.
	_UINT32 nResult;

#ifdef _DEBUG
	assert(lpContext != NULL && lpInstance != NULL);
#endif

	//Get result.
	nResult = AddIPAddress(*((_UINT32 *)ipLocal),*((_UINT32 *)ipNetmask),
					nAdapterIndex,lpContext,lpInstance);
	//Check result.
	if(nResult != NO_ERROR)
	{
#ifdef _DEBUG
		LogRequestedFormat(LOG_TUNNEL | LOG_EXCEPTION,
			"IPHelper::AddAdapterIPAddress : fail(%d) to add ip address !",
			nResult);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Unload interface information list.
//
////////////////////////////////////////////////////////////////////////////////

void UnloadInterfaceInformationList()
{
	//Check result.
	if(theInterfaceInformationList != NULL)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::UnloadInterfaceInformationList : list was freed !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
		//Free it.
		free(theInterfaceInformationList);
		//Clear it.
		theInterfaceInformationList = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Set nework tunnel local address.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL SetNetworkTunnelLocalAddress(NetworkTunnel* pTunnel)
{
#ifdef _DEBUG
	assert(pTunnel != NULL && strlen(pTunnel->strGuid) > 0);
#endif

	//Get adapter index.
	pTunnel->nAdapterIndex = GetAdapterIndexByGuid(pTunnel->strGuid);
	//Check result.
	if(pTunnel->nAdapterIndex == -1)
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : fail to get index of adapter !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"IPHelper::SetNetworkTunnelLocalAddress : index(%d) of adapter !",
		pTunnel->nAdapterIndex);
#endif

	//Get mac address.
	if(!GetAdapterMACAddress(pTunnel->nAdapterIndex,pTunnel->macLocal))
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : fail to get index of adapter !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"IPHelper::SetNetworkTunnelLocalAddress : local(%02x-%02x-%02x-%02x-%02x-%02x) !",
		pTunnel->macLocal[0],pTunnel->macLocal[1],pTunnel->macLocal[2],
		pTunnel->macLocal[3],pTunnel->macLocal[4],pTunnel->macLocal[5]);
#endif

	//Copy MAC address.
	memcpy(pTunnel->macRemote,pTunnel->macLocal,sizeof(_MAC6));
	//Adjust the last.
	pTunnel->macRemote[5] = 0x01;

#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_INFORMATION,
		"IPHelper::SetNetworkTunnelLocalAddress : remote(%02x-%02x-%02x-%02x-%02x-%02x) !",
		pTunnel->macRemote[0],pTunnel->macRemote[1],pTunnel->macRemote[2],
		pTunnel->macRemote[3],pTunnel->macRemote[4],pTunnel->macRemote[5]);
#endif

	//Flush ARP cache.
	if(!FlushAdapterARPCacheInformation(pTunnel->nAdapterIndex))
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : fail to flush ARP cache !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
	}
	else
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : ARP cache was flushed !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
	}

	//Get DHCP status.
	if(!GetAdapterDHCPStatus(pTunnel->nAdapterIndex,&pTunnel->bDHCPEnabled))
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : fail to get DHCP status !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
	}
#ifdef _DEBUG
	LogRequestedFormat(LOG_TUNNEL | LOG_EXCEPTION,
		"IPHelper::SetNetworkTunnelLocalAddress : DHCP(%s) !",
		pTunnel->bDHCPEnabled ? "TRUE" : "FALSE");
#endif

	//Delete adapter addresses.
	DeleteAdapterAddresses(pTunnel->nAdapterIndex);
	//Add IP address.
	if(!AddAdapterIPAddress(pTunnel->nAdapterIndex,
							pTunnel->ipLocal,pTunnel->ipNetmask,
							&pTunnel->nConext,&pTunnel->nInstance))
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : fail to add ip addresses !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}
	else
	{
#ifdef _DEBUG
		LogRequestedEvent("IPHelper::SetNetworkTunnelLocalAddress : ip address was added !",
			LOG_TUNNEL | LOG_INFORMATION);
#endif
	}
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Clear nework tunnel local address.
//
////////////////////////////////////////////////////////////////////////////////

void ClearNetworkTunnelLocalAddress(NetworkTunnel* pTunnel)
{
#ifdef _DEBUG
	assert(pTunnel != NULL);
#endif

	//Check adapter index.
	if(pTunnel->nAdapterIndex != -1 && pTunnel->nConext)
	{
		//Delete IP address.
		if(DeleteIPAddress(pTunnel->nConext) != NO_ERROR)
		{
#ifdef _DEBUG
			LogRequestedEvent("IPHelper::ClearNetworkTunnelLocalAddress : fail to delete ip addresses !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
		else
		{
#ifdef _DEBUG
			LogRequestedEvent("IPHelper::ClearNetworkTunnelLocalAddress : ip address was delete !",
				LOG_TUNNEL | LOG_INFORMATION);
#endif
		}
	}
}
