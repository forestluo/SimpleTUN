////////////////////////////////////////////////////////////////////////////////
//
// General including files.
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include "..\\Global.h"
#include "..\\TAPDriver\\TAPDriver.h"

//Import Library
#pragma comment(lib,"..\\TAPDriver\\Debug\\TAPDriver.lib")
//#pragma comment(lib,"..\\TAPDriver\\Release\\TAPDriver.lib")

//TAP Driver Name
#define TAP_DRIVER_NAME										"tap0801"

////////////////////////////////////////////////////////////////////////////////
//
// Main function.
//
////////////////////////////////////////////////////////////////////////////////

_INT32 main(_INT32 argc,_STRING argv[])
{
	//Initialize TAP driver.
	if(InitializeTAPDriver())
	{
		//Check existance.
		if(TAPDriverExists(TAP_DRIVER_NAME))
		{
			//Set address.
			SetVirtualAddress("10.7.0.6","255.0.0.0","10.7.0.5");
			//Set L2TP server.
			SetL2TPServer("60.28.160.110",1701);
			//Open TAP driver.
			if(OpenTAPDriver(TAP_DRIVER_NAME))
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
						else if(c == 'A')
						{
							SetTAPDriverLog(_TRUE);
						}
						else if(c == 'X')
						{
							SetTAPDriverLog(_FALSE);
						}
						else if(c == 'R')
						{
							//Print.
							Print(stdout,"TAPExample::main : socket is closing !");
							//Close socket of TAP Driver.
							CloseTAPDriverSocket();
							//Print.
							Print(stdout,"TAPExample::main : socket was closed !");

							//Set L2TP server.
							SetL2TPServer("60.28.160.110",1701);

							//Reopen socket of TAP driver.
							if(!OpenTAPDriverSocket()) break;
							//Print.
							Print(stdout,"TAPExample::main : socket was restart !");
						}
						else
						{
							//Print information.
							PrintLine(stdout,"Main::main : press \"Q\" for exit !");
						}
#ifdef _MICROSOFT_WINDOWS
					}
#endif
					//Print.
					Print(stdout,"Output = %dByte(s),Input = %dByte(s)\r",
						GetTAPDriverOutputSize(),GetTAPDriverInputSize());
					//Sleep
					SleepMilliseconds(SECOND);

				}while(IsTAPDriverRunning());
			}
			else
			{
#ifdef _DEBUG
				PrintLine(stderr,"Main::main : fail to open TAP driver !");
#endif
			}
			//Close TAP Driver.
			CloseTAPDriver();
		}
		else
		{
#ifdef _DEBUG
			PrintLine(stderr,"Main::main : TAP driver not exists !");
#endif
		}
	}
	else
	{
#ifdef _DEBUG
		PrintLine(stderr,"Main::main : fail to initialize TAP driver !");
#endif
	}
	//Uninitialize TAP driver.
	UninitializeTAPDriver();

#ifdef _DEBUG
	PrintLine(stdout,"Main::main : successfully done !");
#endif
	//Return success.
	return _SUCCESS;
}
