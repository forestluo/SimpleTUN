#ifndef _GLOBAL_H
#define _GLOBAL_H

////////////////////////////////////////////////////////////////////////////////
//
// OS Type Definition
//
// Definition of the operation system type.
//
// These directives are for the portable program.
// I suppose this program would run on Microsoft Windows, Linux, FreeBSD, Solaris etc.
// For this purpose, I must mainly write in ANSI C.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Microsoft Windows :											_MICROSOFT_WINDOWS
// RedHat Linux :												_REDHAT_LINUX
// SUN Solaris :												_SUN_SOLARIS
// 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <memory.h>
#include <string.h>

#include <assert.h>

#ifdef _MICROSOFT_WINDOWS
#include <conio.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
// General requirements
//
// Including the requirements for general using.
//
// These requirements are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Debug
#ifndef _DEBUG
#define															_DEBUG
#endif

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//INT8
typedef char													_INT8;
//Unsigned INT8
typedef unsigned char											_UINT8;
//INT16
typedef short													_INT16;
//Unsigned INT16
typedef unsigned short											_UINT16;
//INT32
typedef int														_INT32;
//Unsigned INT32
typedef unsigned int											_UINT32;

//BOOL
typedef _UINT32													_BOOL;
//TRUE
#define _TRUE													(_BOOL)1
//FALSE
#define _FALSE													(_BOOL)0

//SUCCESS
#define _SUCCESS												0
//FAILURE
#define _FAILURE												-1

//Byte
typedef _INT8													_BYTE;
//Char
typedef _INT8													_CHAR;
//Wide Char
typedef _INT16													_WIDECHAR;
//Short
typedef _INT16													_SHORT;
//Integer
typedef _INT32													_INTEGER;

//Object
typedef void*													_OBJECT;
//String
typedef _CHAR*													_STRING;
//Wide String
typedef _WIDECHAR*												_WIDESTRING;
//Buffer
typedef _BYTE*													_BUFFER;

//Pascal String Length
#define PASCAL_STRING_LENGTH									256
//Pascal String
typedef _CHAR													_PASCALSTRING[PASCAL_STRING_LENGTH];

//Block Size
#define BLOCK_SIZE												4096 * sizeof(_UINT8)
//Block
typedef _UINT8													_BLOCK[BLOCK_SIZE];

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Print
#include "Print.h"

//Hex
#include "Hex.h"
//Digital
#include "Digital.h"
//Characater
#include "Characater.h"

//Simple Time
#include "SimpleTime.h"
//Timestamp
#include "Timestamp.h"
//Timeout
#include "Timeout.h"
//Watch
#include "Watch.h"

//Chain
#include "Chain.h"
//Directory
#include "Directory.h"

//Socket
#include "Socket.h"
//Server Socket
#include "ServerSocket.h"
//Client Socket
#include "ClientSocket.h"

//Lock
#include "Lock.h"
//Sleep
#include "Sleep.h"
//Thread
#include "Thread.h"

//Buffer
#include "Buffer.h"

//Recorder
#include "Recorder.h"
//Log
#include "Log.h"

//Checksum
#include "Checksum.h"
//Ethernet
#include "Ethernet.h"
//Registration
#include "Registration.h"

//Tunnel
#include "Tunnel.h"
//IPHelper
#include "IPHelper.h"

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

//Odd
#define IsOdd(value) \
	(((value) & 0x01) == 1)
//Even
#define IsEven(value) \
	(((value) & 0x01) == 0)

//Maximum
#define Maximum(a,b) \
	(((a) > (b)) ? (a) : (b))
//Minimum
#define Minimum(a,b) \
	(((a) < (b)) ? (a) : (b))

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
