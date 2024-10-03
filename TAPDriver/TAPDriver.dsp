# Microsoft Developer Studio Project File - Name="TAPDriver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=TAPDriver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TAPDriver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TAPDriver.mak" CFG="TAPDriver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TAPDriver - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TAPDriver - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TAPDriver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_MICROSOFT_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "TAPDriver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_MICROSOFT_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "TAPDriver - Win32 Release"
# Name "TAPDriver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Buffer.c
# End Source File
# Begin Source File

SOURCE=.\Chain.c
# End Source File
# Begin Source File

SOURCE=.\Characater.c
# End Source File
# Begin Source File

SOURCE=.\Checksum.c
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.c
# End Source File
# Begin Source File

SOURCE=.\Digital.c
# End Source File
# Begin Source File

SOURCE=.\Directory.c
# End Source File
# Begin Source File

SOURCE=.\Ethernet.c
# End Source File
# Begin Source File

SOURCE=.\Hex.c
# End Source File
# Begin Source File

SOURCE=.\IPHelper.c
# End Source File
# Begin Source File

SOURCE=.\Lock.c
# End Source File
# Begin Source File

SOURCE=.\Log.c
# End Source File
# Begin Source File

SOURCE=.\Print.c
# End Source File
# Begin Source File

SOURCE=.\Recorder.c
# End Source File
# Begin Source File

SOURCE=.\Registration.c
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.c
# End Source File
# Begin Source File

SOURCE=.\SimpleClient.c
# End Source File
# Begin Source File

SOURCE=.\SimpleTime.c
# End Source File
# Begin Source File

SOURCE=.\Sleep.c
# End Source File
# Begin Source File

SOURCE=.\Socket.c
# End Source File
# Begin Source File

SOURCE=.\TAPDriver.c
# End Source File
# Begin Source File

SOURCE=.\Thread.c
# End Source File
# Begin Source File

SOURCE=.\Timeout.c
# End Source File
# Begin Source File

SOURCE=.\Timestamp.c
# End Source File
# Begin Source File

SOURCE=.\Tunnel.c
# End Source File
# Begin Source File

SOURCE=.\Watch.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\Chain.h
# End Source File
# Begin Source File

SOURCE=.\Characater.h
# End Source File
# Begin Source File

SOURCE=.\Checksum.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\Digital.h
# End Source File
# Begin Source File

SOURCE=.\Directory.h
# End Source File
# Begin Source File

SOURCE=.\Ethernet.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\Hex.h
# End Source File
# Begin Source File

SOURCE=.\IPHelper.h
# End Source File
# Begin Source File

SOURCE=.\Lock.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\Print.h
# End Source File
# Begin Source File

SOURCE=.\Recorder.h
# End Source File
# Begin Source File

SOURCE=.\Registration.h
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\SimpleTime.h
# End Source File
# Begin Source File

SOURCE=.\Sleep.h
# End Source File
# Begin Source File

SOURCE=.\Socket.h
# End Source File
# Begin Source File

SOURCE=.\TAPDriver.h
# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# Begin Source File

SOURCE=.\Timeout.h
# End Source File
# Begin Source File

SOURCE=.\Timestamp.h
# End Source File
# Begin Source File

SOURCE=.\Tunnel.h
# End Source File
# Begin Source File

SOURCE=.\Watch.h
# End Source File
# End Group
# End Target
# End Project
