////////////////////////////////////////////////////////////////////////////////
//
// General including files.
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include "Global.h"

////////////////////////////////////////////////////////////////////////////////
//
// Main function.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 main(_INT32 argc,_STRING argv[])
{
	//Path
	_PASCALSTRING strPath;
	//Directory
	_PASCALSTRING strDirectory;

	//Tunnel
	NetworkTunnel tunnel;

	//Get current working directory.
	if(!GetFileDirectory(strDirectory))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Main::main : fail to get current working directory !");
#endif
		return _FAILURE;
	}
	//Set home directory.
	SetHomeDirectory(strDirectory);

	//Set log directory.
	sprintf(strPath,"%s%slog",
		strDirectory,GetFileDirectorySplitter());
	//Initialize log.
	if(!InitializeLog(strPath,LOG_ALL))
	{
#ifdef _DEBUG
		PrintLine(stderr,"Main::main : fail to initialize log !");
#endif
		return _FAILURE;
	}

	//Initialize socket.
	if(!InitializeSocket())
	{
#ifdef _DEBUG
		LogRequestedEvent("Main::main : fail to initialize socket !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FAILURE;
	}

	//Initialize tunnel environment.
	if(InitializeTunnelEnvironment())
	{
		//Initialize tunnel.
		InitializeNetworkTunnel(&tunnel);

		//Set configuration of address.
		//Local.
		tunnel.ipLocal[0] = 10;tunnel.ipLocal[1] = 7;tunnel.ipLocal[2] = 0;tunnel.ipLocal[3] = 6;
		//Netmask.
		tunnel.ipNetmask[0] = 255;tunnel.ipNetmask[1] = 0;tunnel.ipNetmask[2] = 0;tunnel.ipNetmask[3] = 0;
		//Remote.
		tunnel.ipRemote[0] = 10;tunnel.ipRemote[1] = 7;tunnel.ipRemote[2] = 0;tunnel.ipRemote[3] = 5;

		//Set configuration of peer.
		//Address.
		strcpy(tunnel.strPeerAddress,"60.28.160.110");
		//Port.
		tunnel.nPeerPort = 1701;

		//Open tunnel.
		if(OpenNetworkTunnel(&tunnel))
		{
			//Do process.
			do
			{
#ifdef _MICROSOFT_WINDOWS
				//Check keyboard.
				if(kbhit())
				{
#endif
					//Get a char.
					_CHAR c = getchar();
					//Get a char.
					if(c == 'Q')
					{
						break;
					}
					else
					{
						//Print information.
						PrintLine(stdout,"Main::main : press \"Q\" for exit !");
					}

#ifdef _MICROSOFT_WINDOWS
				}
#endif
				//Sleep
				SleepMilliseconds(MILLISECOND);

			}while(_TRUE);
		}
		else
		{
#ifdef _DEBUG
			LogRequestedEvent("Main::main : fail to open tunnel !",
				LOG_TUNNEL | LOG_EXCEPTION);
#endif
		}
		//Close tunnel.
		CloseNetworkTunnel(&tunnel);
		//Uninitialize tunnel.
		UninitializeNetworkTunnel(&tunnel);
	}
	else
	{
#ifdef _DEBUG
		LogRequestedEvent("Main::main : fail to initialize tunnel environments !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		return _FAILURE;
	}
	//Uninitialize tunnel environment.
	UninitializeTunnelEnvironment();

	//Uninitialize socket.
	if(!UninitializeSocket())
	{
#ifdef _DEBUG
		LogRequestedEvent("Main::main : fail to uninitialize socket !",
			LOG_TUNNEL | LOG_EXCEPTION);
#endif
		//return _FAILURE;
	}

	//Uninitialize log.
	if(!UninitializeLog())
	{
#ifdef _DEBUG
		PrintLine(stderr,"Main::main : fail to uninitialize log !");
#endif
		//return _FAILURE;
	}

#ifdef _DEBUG
	PrintLine(stdout,"Main::main : successfully done !");
#endif
	//Return success.
	return _SUCCESS;
}
