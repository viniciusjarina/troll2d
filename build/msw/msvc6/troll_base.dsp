# Microsoft Developer Studio Project File - Name="troll_base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=troll_base - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "troll_base.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "troll_base.mak" CFG="troll_base - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "troll_base - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "troll_base - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "troll_base - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O1 /I "../../../include/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib\vc6_lib\troll_base.lib"

!ELSEIF  "$(CFG)" == "troll_base - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib\vc6_lib\troll_based.lib"

!ENDIF 

# Begin Target

# Name "troll_base - Win32 Release"
# Name "troll_base - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\graphics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\graphics_factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\graphics_impl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\image_factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\image_impl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\key_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\key_input_factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mouse_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mouse_input_factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\screen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\screen_impl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\surface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\surface_factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\surface_impl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\system.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\system_impl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\troll\color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\draw_flags.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\graphics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\graphics_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\graphics_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\image_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\image_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\key.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\key_input.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\key_input_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\key_input_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\mouse_input.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\mouse_input_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\mouse_input_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\screen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\screen_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\screen_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\size.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\surface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\surface_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\surface_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\system.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\system_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll.h
# End Source File
# End Group
# End Target
# End Project
