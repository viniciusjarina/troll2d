# Microsoft Developer Studio Project File - Name="test_blit_png" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=test_blit_png - Win32 Debug Allegro
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test_blit_png.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_blit_png.mak" CFG="test_blit_png - Win32 Debug Allegro"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_blit_png - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test_blit_png - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "test_blit_png - Win32 Release Allegro" (based on "Win32 (x86) Application")
!MESSAGE "test_blit_png - Win32 Debug Allegro" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test_blit_png - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 SDL.lib troll_base.lib troll_sdl.lib zlib.lib libpng.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../../../bin/test_blit_png_sdl.exe" /libpath:"../../../dependencies/SDL-1.2.13/lib/VisualC/" /libpath:"../../../lib/vc6_lib" /libpath:"../../../dependencies/libpng/lib/msvc"
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test_blit_png___Win32_Debug"
# PROP BASE Intermediate_Dir "test_blit_png___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SDL.lib troll_sdld.lib troll_based.lib zlibd.lib libpngd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../../../bin/test_blit_pngd_sdl.exe" /pdbtype:sept /libpath:"../../../dependencies/SDL-1.2.13/lib/VisualC/" /libpath:"../../../lib/vc6_lib" /libpath:"../../../dependencies/libpng/lib/msvc"
# SUBTRACT LINK32 /incremental:no /force

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Release Allegro"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "test_blit_png___Win32_Release_Allegro"
# PROP BASE Intermediate_Dir "test_blit_png___Win32_Release_Allegro"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "test_blit_png___Win32_Release_Allegro"
# PROP Intermediate_Dir "test_blit_png___Win32_Release_Allegro"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 alleg_s.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib troll_base.lib troll_allegro.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../../../bin/test_blit_png.exe" /libpath:"../../../dependencies/SDL-1.2.13/lib/VisualC/" /libpath:"../../../dependencies/allegro/lib/msvc/"
# ADD LINK32 alleg_s.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib troll_base.lib troll_allegro.lib zlib.lib libpng.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../../../bin/test_blit_png_allegro.exe" /libpath:"../../../dependencies/allegro/lib/msvc/" /libpath:"../../../lib/vc6_lib" /libpath:"../../../dependencies/libpng/lib/msvc"
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug Allegro"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test_blit_png___Win32_Debug_Allegro"
# PROP BASE Intermediate_Dir "test_blit_png___Win32_Debug_Allegro"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "test_blit_png___Win32_Debug_Allegro"
# PROP Intermediate_Dir "test_blit_png___Win32_Debug_Allegro"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 SDLD.lib SDLmainD.lib alld_s.lib troll_sdld.lib troll_based.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../../dependencies/SDL-1.2.13/lib/VisualC/" /libpath:"../../../dependencies/allegro/lib/msvc/"
# ADD LINK32 alld_s.lib troll_allegrod.lib troll_based.lib dxguid.lib ddraw.lib dsound.lib dinput.lib winmm.lib zlibd.lib libpngd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../../../bin/test_blit_pngd_allegro.exe" /pdbtype:sept /libpath:"../../../dependencies/allegro/lib/msvc/" /libpath:"../../../lib/vc6_lib" /libpath:"../../../dependencies/libpng/lib/msvc"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "test_blit_png - Win32 Release"
# Name "test_blit_png - Win32 Debug"
# Name "test_blit_png - Win32 Release Allegro"
# Name "test_blit_png - Win32 Debug Allegro"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\test\msw\test.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\test\test_blit_png.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE="..\..\..\dependencies\SDL-1.2.13\lib\VisualC\SDL.dll"

!IF  "$(CFG)" == "test_blit_png - Win32 Release"

# Begin Custom Build
InputPath="..\..\..\dependencies\SDL-1.2.13\lib\VisualC\SDL.dll"

"..\..\..\bin\SDL.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	IF         EXIST         $(InputPath)         xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug"

# Begin Custom Build
InputPath="..\..\..\dependencies\SDL-1.2.13\lib\VisualC\SDL.dll"

"..\..\..\bin\SDL.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	IF         EXIST         $(InputPath)         xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Release Allegro"

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug Allegro"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\data\images\troll.png

!IF  "$(CFG)" == "test_blit_png - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\data\images\troll.png

"..\..\..\bin\images\troll.png" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\images\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\data\images\troll.png

"..\..\..\bin\images\troll.png" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\images\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Release Allegro"

# Begin Custom Build
InputPath=..\..\..\data\images\troll.png

"..\..\..\bin\images\troll.png" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\images\ 

# End Custom Build

!ELSEIF  "$(CFG)" == "test_blit_png - Win32 Debug Allegro"

# Begin Custom Build
InputPath=..\..\..\data\images\troll.png

"..\..\..\bin\images\troll.png" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy         /Y         /Q         /D        $(InputPath)        ..\..\..\bin\images\ 

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
