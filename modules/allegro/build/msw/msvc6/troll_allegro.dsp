# Microsoft Developer Studio Project File - Name="troll_allegro" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=troll_allegro - Win32 Debug Allegro
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "troll_allegro.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "troll_allegro.mak" CFG="troll_allegro - Win32 Debug Allegro"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "troll_allegro - Win32 Release Allegro" (based on "Win32 (x86) Static Library")
!MESSAGE "troll_allegro - Win32 Debug Allegro" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "troll_allegro - Win32 Release Allegro"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "troll_allegro___Win32_Release_Allegro"
# PROP BASE Intermediate_Dir "troll_allegro___Win32_Release_Allegro"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "troll_allegro___Win32_Release_Allegro"
# PROP Intermediate_Dir "troll_allegro___Win32_Release_Allegro"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I "../../../../../include/" /I "../../../include/" /I "../../../../../dependencies/allegro/include/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ALLEGRO_STATICLINK" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "../../../../../include/" /I "../../../include/" /I "../../../../../dependencies/allegro/include/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ALLEGRO_STATICLINK" /YX /FD /c
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_allegro.lib"
# ADD LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_allegro.lib"

!ELSEIF  "$(CFG)" == "troll_allegro - Win32 Debug Allegro"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "troll_allegro___Win32_Debug_Allegro"
# PROP BASE Intermediate_Dir "troll_allegro___Win32_Debug_Allegro"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "troll_allegro___Win32_Debug_Allegro"
# PROP Intermediate_Dir "troll_allegro___Win32_Debug_Allegro"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../../../include/" /I "../../../include/" /I "../../../../../dependencies/allegro/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ALLEGRO_STATICLINK" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../../../include/" /I "../../../include/" /I "../../../../../dependencies/allegro/include/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ALLEGRO_STATICLINK" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_allegrod.lib"
# ADD LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_allegrod.lib"

!ENDIF 

# Begin Target

# Name "troll_allegro - Win32 Release Allegro"
# Name "troll_allegro - Win32 Debug Allegro"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\allegro_graphics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_image_surface_helper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_keyinput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_mouseinput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_screen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_screen_helper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_surface.cpp

!IF  "$(CFG)" == "troll_allegro - Win32 Release Allegro"

!ELSEIF  "$(CFG)" == "troll_allegro - Win32 Debug Allegro"

# ADD BASE CPP /I "../../../../../../../../../../include/"
# ADD CPP /I "../../../../../../../../../../include/"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\allegro_system.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\gfx_ex.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_graphics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_image_surface_helper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_keyinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_mouseinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_screen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_screen_helper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_surface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\allegro_system.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\gfx_ex.h
# End Source File
# End Group
# End Target
# End Project
