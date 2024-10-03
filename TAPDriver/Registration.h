#ifndef _SIMPLE_REGISTRATION_H
#define _SIMPLE_REGISTRATION_H

////////////////////////////////////////////////////////////////////////////////
//
// Adapter functions.
//
////////////////////////////////////////////////////////////////////////////////

//Load network adapters.
extern _BOOL LoadNetworkAdapters();
//Release network adapters.
extern void ReleaseNetworkAdapters();
//Show network adapters.
extern void ShowNetworkAdapters();

//Check network adapter by guid.
extern _BOOL CheckNetworkAdapterByGuid(_STRING lpstrGuid);

////////////////////////////////////////////////////////////////////////////////
//
// Connection functions.
//
////////////////////////////////////////////////////////////////////////////////

//Load network connections.
extern _BOOL LoadNetworkConnections();
//Release network connection.
extern void ReleaseNetworkConnections();
//Show network connections.
extern void ShowNetworkConnections();

//Get network connection name by guid.
extern _STRING GetNetworkConnectionNameByGuid(_STRING lpstrGuid);
//Get network connection guid by name.
extern _STRING GetNetworkConnectionGuidByName(_STRING lpstrConnectionName);

////////////////////////////////////////////////////////////////////////////////
//
// Other functions.
//
////////////////////////////////////////////////////////////////////////////////

//Is network Tunnel exists.
extern _BOOL IsNetworkTunnelExists(_STRING lpstrAdapterName);
//Get network tunnel guid.
extern _STRING GetNetworkTunnelGuid(_STRING lpstrAdapterName);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
