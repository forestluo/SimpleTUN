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
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Registry Keys
//
////////////////////////////////////////////////////////////////////////////////

//Componenet ID
#define COMPONENT_ID										"ComponentId"
//Net Config Instance ID
#define NET_CONFIG_INSTANCE_ID								"NetCfgInstanceId"
//Connection Name
#define CONNECTION_NAME										"Name"

//Adapter Key
#define ADAPTER_KEY "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002BE10318}"
//Network Connections Key
#define NETWORK_CONNECTIONS_KEY "SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}"

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

//Adapter
typedef struct tagNetworkAdapter
{
	//Component ID
	_PASCALSTRING strComponentID;
	//Instance ID
	_PASCALSTRING strInstanceID;
}

NetworkAdapter;

//Connection
typedef struct tagNetworkConnection
{
	//Guid
	_PASCALSTRING strGuid;
	//Name
	_PASCALSTRING strName;
}

NetworkConnection;

//Adapters.
SimpleChain theAdapters;
//Connections
SimpleChain theConnections;

////////////////////////////////////////////////////////////////////////////////
//
// Initialize network adapter.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeNetworkAdapter(NetworkAdapter* lpAdapter)
{
#ifdef _DEBUG
	assert(lpAdapter != NULL);
#endif

	//Clear adapter.
	memset(lpAdapter,0,sizeof(NetworkAdapter));
}

////////////////////////////////////////////////////////////////////////////////
//
// Load network adapters.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LoadNetworkAdapters()
{
	//Status.
	_INT32 nStatus;

	//Length
	_INT32 nLength;
	//Int.
	_INT32 nIndex = 0;

	//Key.
	HKEY hAdapterKey;
	//Name
	_PASCALSTRING strName[256];
	//Unit String
	_PASCALSTRING strUnit[256];
	//Unit Key
	HKEY hUnitKey;
	//Component ID
	_PASCALSTRING strComponentID;
	//Net Config Instance ID
	_PASCALSTRING strInstanceID;
	//Data Type
	_UINT32 nDataType;

	//Adapter.
	NetworkAdapter* pAdapter;

	//Initialize adapters.
	InitializeChain(&theAdapters);

	//Open registry key.
	nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,ADAPTER_KEY,0,KEY_READ,&hAdapterKey);
	//Check result.
	if(nStatus != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to open registry key !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Do loop.
	while(_TRUE)
	{
		//Set length.
		nLength = PASCAL_STRING_LENGTH;
		//Enum key.
		nStatus = RegEnumKeyEx(hAdapterKey,nIndex,(_STRING)strName,&nLength,NULL,NULL,NULL,NULL);
		//Check status.
		if(nStatus == ERROR_NO_MORE_ITEMS)
		{
#ifdef _DEBUG
			//PrintLine(stderr,"Registration::LoadNetworkAdapters : No more registry subkeys !");
#endif
			break;
		}
		//Add index.
		nIndex ++;
		//Check stats.
		if(nStatus != ERROR_SUCCESS)
		{
#ifdef _DEBUG
			LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to enumerate registry subkeys of key !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
			continue;
		}
		//Format.
		Format((_STRING)strUnit,"%s\\%s",ADAPTER_KEY,(_STRING)strName);
	
		//Open registry key.
		nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,(_STRING)strUnit,0,KEY_READ,&hUnitKey);
		//Check stats.
		if(nStatus == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//PrintLine(stdout,"Registration::LoadNetworkAdapters : subkey(%s) was opened !",strUnit);
#endif

			//Get length.
			nLength = PASCAL_STRING_LENGTH;
			//Query.
			nStatus = RegQueryValueEx(hUnitKey,COMPONENT_ID,NULL,&nDataType,strComponentID,&nLength);
			//Check status.
			if(nStatus == ERROR_SUCCESS && nDataType == REG_SZ)
			{
#ifdef _DEBUG
				//PrintLine(stdout,"Registration::LoadNetworkAdapters : component id = \"%s\" !",strComponentID);
#endif
			}
			else
			{
#ifdef _DEBUG
				LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to query component id !",
					LOG_TUNNEL | LOG_EXCEPTION);
#endif
				continue;
			}

			//Get length.
			nLength = PASCAL_STRING_LENGTH;
			//Query.
			nStatus = RegQueryValueEx(hUnitKey,NET_CONFIG_INSTANCE_ID,NULL,&nDataType,strInstanceID,&nLength);
			//Check status.
			if(nStatus == ERROR_SUCCESS && nDataType == REG_SZ)
			{
#ifdef _DEBUG
				//PrintLine(stdout,"Registration::LoadNetworkAdapters : instance id = \"%s\" !",strInstanceID);
#endif
			}
			else
			{
#ifdef _DEBUG
				LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to query instance id !",
					LOG_TUNNEL | LOG_EXCEPTION);
#endif
				continue;
			}

			//Create adapter.
			pAdapter = (NetworkAdapter *)malloc(sizeof(NetworkAdapter));
#ifdef _DEBUG
			assert(pAdapter != NULL);
#endif
			//Initialize adapter.
			InitializeNetworkAdapter(pAdapter);
			//Copy component id.
			strcpy(pAdapter->strComponentID,(_STRING)strComponentID);
			//Copy instance id.
			strcpy(pAdapter->strInstanceID,(_STRING)strInstanceID);
			//Insert into adapters.
			if(!InsertChainObject(&theAdapters,pAdapter))
			{
				//Free adapter.
				free(pAdapter);
#ifdef _DEBUG
				LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to add adapter !",
					LOG_TUNNEL | LOG_EXCEPTION);
#endif
			}
		}
		else
		{
#ifdef _DEBUG
			LogRequestedEvent("Registration::LoadNetworkAdapters : Fail to open registry subkeys !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
		//Close unit key.
		RegCloseKey(hUnitKey);
	}
	//Close registry key.
    RegCloseKey(hAdapterKey);

	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Show network adapters.
//
////////////////////////////////////////////////////////////////////////////////

void ShowNetworkAdapters()
{
	//Node.
	ChainNode* pCurrent;
	//Adapter.
	NetworkAdapter* pAdapter;

	//Print.
	PrintLine(stdout,"Registration::ShowNetworkAdapters : show adapters !");

	//Get root.
	pCurrent = &theAdapters.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theAdapters.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into adapter.
		pAdapter = (NetworkAdapter *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pAdapter != NULL);
#endif

		//Print component id.
		PrintLine(stdout,"\tComponent ID = \"%s\"",pAdapter->strComponentID);
		//Print instance id.
		PrintLine(stdout,"\tInstance ID = \"%s\"",pAdapter->strInstanceID);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Check network adapter by guid.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL CheckNetworkAdapterByGuid(_STRING lpstrGuid)
{
	//Node.
	ChainNode* pCurrent;
	//Adapter.
	NetworkAdapter* pAdapter;

#ifdef _DEBUG
	assert(lpstrGuid != NULL);
#endif

	//Get root.
	pCurrent = &theAdapters.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theAdapters.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into adapter.
		pAdapter = (NetworkAdapter *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pAdapter != NULL);
#endif

		//Compare.
		if(!strcmp(lpstrGuid,pAdapter->strInstanceID))
		{
			//Return ture.
			return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Release network adapters.
//
////////////////////////////////////////////////////////////////////////////////

void ReleaseNetworkAdapters()
{
#ifdef _DEBUG
	LogRequestedEvent("Registration::ReleaseNetworkAdapters : adapters was released !",
		LOG_TUNNEL | LOG_EXCEPTION);
#endif
	//Delete adapters.
	DeleteChainObjects(&theAdapters);
}

////////////////////////////////////////////////////////////////////////////////
//
// Initialize network connection.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeNetworkConnection(NetworkConnection* lpConnection)
{
#ifdef _DEBUG
	assert(lpConnection != NULL);
#endif

	//Clear connection.
	memset(lpConnection,0,sizeof(NetworkConnection));
}

////////////////////////////////////////////////////////////////////////////////
//
// Load network connections.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL LoadNetworkConnections()
{
	//Status.
	_INT32 nStatus;

	//Length
	_INT32 nLength;
	//Index
	_INT32 nIndex = 0;

	//Network Connections Key
	HKEY hNetworkConnectionsKey;
	//Name
	_PASCALSTRING strName[256];
	//Connection String
	_PASCALSTRING strConnection[256];
	//Connection Key
	HKEY hConnectionKey;
	//Connection Name
	_PASCALSTRING strConnectionName;
	//Data Type
	_UINT32 nNameType;

	//Connection
	NetworkConnection* pConnection;

	//Initialize connections.
	InitializeChain(&theConnections);

	//Open registry key.
	nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,NETWORK_CONNECTIONS_KEY,0,KEY_READ,&hNetworkConnectionsKey);
	//Check result.
	if(nStatus != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		LogRequestedEvent("Registration::LoadNetworkConnections : Fail to open registry key !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FALSE;
	}

	//Do loop.
	while(_TRUE)
	{
		//Set length.
		nLength = PASCAL_STRING_LENGTH;
		//Enum key.
		nStatus = RegEnumKeyEx(hNetworkConnectionsKey,nIndex,(_STRING)strName,&nLength,NULL,NULL,NULL,NULL);
		//Check status.
		if(nStatus == ERROR_NO_MORE_ITEMS)
		{
#ifdef _DEBUG
			//PrintLine(stderr,"Registration::LoadNetworkConnections : No more registry subkeys !");
#endif
			break;
		}
		//Add index.
		nIndex ++;
		//Check stats.
		if(nStatus != ERROR_SUCCESS)
		{
#ifdef _DEBUG
			LogRequestedEvent("Registration::LoadNetworkConnections : Fail to enumerate registry subkeys of key !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
			continue;
		}
		//Format.
		Format((_STRING)strConnection,"%s\\%s\\Connection",NETWORK_CONNECTIONS_KEY,(_STRING)strName);
	
		//Open registry key.
		nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,(_STRING)strConnection,0,KEY_READ,&hConnectionKey);
		//Check stats.
		if(nStatus == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//PrintLine(stdout,"Registration::LoadNetworkConnections : subkey(%s) was opened !",strConnection);
#endif

			//Get length.
			nLength = PASCAL_STRING_LENGTH;
			//Query.
			nStatus = RegQueryValueEx(hConnectionKey,CONNECTION_NAME,NULL,&nNameType,strConnectionName,&nLength);
			//Check status.
			if(nStatus == ERROR_SUCCESS && nNameType == REG_SZ)
			{
#ifdef _DEBUG
				//PrintLine(stdout,"Registration::LoadNetworkConnections : connection name = \"%s\" !",strConnectionName);
#endif
			}
			else
			{
#ifdef _DEBUG
				LogRequestedEvent("Registration::LoadNetworkConnections : Fail to query component id !",
					LOG_TUNNEL | LOG_EXCEPTION);
#endif
				continue;
			}

			//Create connection.
			pConnection = (NetworkConnection *)malloc(sizeof(NetworkConnection));
#ifdef _DEBUG
			assert(pConnection != NULL);
#endif
			//Initialize connection.
			InitializeNetworkConnection(pConnection);
			//Copy name.
			strcpy(pConnection->strName,(_STRING)strConnectionName);
			//Copy guid.
			strcpy(pConnection->strGuid,(_STRING)strName);
			//Insert into adapters.
			if(!InsertChainObject(&theConnections,pConnection))
			{
				//Free connection.
				free(pConnection);
#ifdef _DEBUG
				LogRequestedEvent("Registration::LoadNetworkConnections : Fail to add connection !",
					LOG_TUNNEL | LOG_EXCEPTION);
#endif
			}
		}
		else
		{
#ifdef _DEBUG
			LogRequestedEvent("Registration::LoadNetworkConnections : Fail to open registry subkeys !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
		//Close connection key.
		RegCloseKey(hConnectionKey);
	}
	//Close registry key.
	RegCloseKey(hNetworkConnectionsKey);

	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Show network connections.
//
////////////////////////////////////////////////////////////////////////////////

void ShowNetworkConnections()
{
	//Node.
	ChainNode* pCurrent;
	//Connection.
	NetworkConnection* pConnection;

	//Print.
	PrintLine(stdout,"Registration::ShowNetworkConnections : show connections !");

	//Get root.
	pCurrent = &theConnections.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theConnections.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into connection.
		pConnection = (NetworkConnection *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pConnection != NULL);
#endif

		//Print name.
		PrintLine(stdout,"\tName = \"%s\"",pConnection->strName);
		//Print instance id.
		PrintLine(stdout,"\tGuid = \"%s\"",pConnection->strGuid);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Get network connection name by guid.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetNetworkConnectionNameByGuid(_STRING lpstrGuid)
{
	//Node.
	ChainNode* pCurrent;
	//Connection.
	NetworkConnection* pConnection;

#ifdef _DEBUG
	assert(lpstrGuid != NULL);
#endif

	//Get root.
	pCurrent = &theConnections.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theConnections.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into connection.
		pConnection = (NetworkConnection *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pConnection != NULL);
#endif

		//Check name.
		if(!strcmp(pConnection->strGuid,lpstrGuid))
		{
			//Return name.
			return (_STRING)pConnection->strName;
		}
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get network connection guid by name.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetNetworkConnectionGuidByName(_STRING lpstrConnectionName)
{
	//Node.
	ChainNode* pCurrent;
	//Connection.
	NetworkConnection* pConnection;

#ifdef _DEBUG
	assert(lpstrConnectionName != NULL);
#endif

	//Get root.
	pCurrent = &theConnections.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theConnections.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into connection.
		pConnection = (NetworkConnection *)pCurrent->lpObject;

		//Check name.
		if(!strcmp(pConnection->strName,lpstrConnectionName) && CheckNetworkAdapterByGuid(pConnection->strGuid))
		{
			//Return guid.
			return (_STRING)pConnection->strGuid;
		}

#ifdef _DEBUG
		assert(pConnection != NULL);
#endif
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Release network connections.
//
////////////////////////////////////////////////////////////////////////////////

void ReleaseNetworkConnections()
{
#ifdef _DEBUG
	LogRequestedEvent("Registration::ReleaseNetworkConnections : connections was released !",
		LOG_TUNNEL | LOG_EXCEPTION);
#endif
	//Delete connections.
	DeleteChainObjects(&theConnections);
}

////////////////////////////////////////////////////////////////////////////////
//
// Get network tunnel guid.
//
////////////////////////////////////////////////////////////////////////////////

_STRING GetNetworkTunnelGuid(_STRING lpstrAdapterName)
{
	//Node.
	ChainNode* pCurrent;
	//Adapter.
	NetworkAdapter* pAdapter;

#ifdef _DEBUG
	assert(lpstrAdapterName != NULL);
#endif

	//Get root.
	pCurrent = &theAdapters.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theAdapters.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into adapter.
		pAdapter = (NetworkAdapter *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pAdapter != NULL);
#endif

		//Check component id.
		if(strcmp(pAdapter->strComponentID,lpstrAdapterName) == 0)
		{
			//Check result.
			if(GetNetworkConnectionNameByGuid(pAdapter->strInstanceID) != NULL)
				return pAdapter->strInstanceID;
		}
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get network tunnel guid.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsNetworkTunnelExists(_STRING lpstrAdapterName)
{
	//Node.
	ChainNode* pCurrent;
	//Adapter.
	NetworkAdapter* pAdapter;

	//Name
	_STRING lpstrName;

#ifdef _DEBUG
	assert(lpstrAdapterName != NULL);
#endif

	//Get root.
	pCurrent = &theAdapters.nodeRoot;
	//Check attributes.
	while(pCurrent->lpNext != &theAdapters.nodeRoot)
	{
		//Get next.
		pCurrent = pCurrent->lpNext;

#ifdef _DEBUG
		assert(pCurrent != NULL);
#endif

		//Convert it into adapter.
		pAdapter = (NetworkAdapter *)pCurrent->lpObject;

#ifdef _DEBUG
		assert(pAdapter != NULL);
#endif

		//Check component id.
		if(strcmp(pAdapter->strComponentID,lpstrAdapterName) == 0)
		{
			//Get name.
			lpstrName = GetNetworkConnectionNameByGuid(pAdapter->strInstanceID);
			//Check result.
			if(lpstrName != NULL)
			{
				//Return true.
				return _TRUE;
			}
		}
	}
	//Return false.
	return _FALSE;
}

