# Microsoft Developer Studio Project File - Name="troll_sdl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=troll_sdl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "troll_sdl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "troll_sdl.mak" CFG="troll_sdl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "troll_sdl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "troll_sdl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "troll_sdl - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O1 /I "../../../../../include/" /I "../../../include/" /I "../../../include/sprig/" /I "../../../include/SDL_image/" /I "../../../../../dependencies/SDL-1.2.13/include/" /I "../../../../../dependencies/libpng/include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "LOAD_PNG" /D "LOAD_BMP" /D "_SGE_NOTTF" /YX /FD /c
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_sdl.lib"

!ELSEIF  "$(CFG)" == "troll_sdl - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../../../include/" /I "../../../include/" /I "../../../include/sprig/" /I "../../../include/sge/" /I "../../../include/SDL_image/" /I "../../../../../dependencies/SDL-1.2.13/include/" /I "../../../../../dependencies/libpng/include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "LOAD_PNG" /D "LOAD_BMP" /D "_SGE_NOTTF" /YX /FD /GZ /c
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\..\lib\vc6_lib\troll_sdld.lib"

!ENDIF 

# Begin Target

# Name "troll_sdl - Win32 Release"
# Name "troll_sdl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "SPriG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\sprig\SPG_blib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sprig\SPG_extended.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sprig\SPG_primitives.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sprig\SPG_rotation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sprig\SPG_surface.cpp
# End Source File
# End Group
# Begin Group "SDL_image"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_bmp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_gif.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_jpg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_lbm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_pcx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_png.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_pnm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_tga.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_tif.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_xcf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_xpm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_xv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_image\IMG_xxx.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\do_arc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_gfxPrimitives.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SDL_gfxPrimitives_ex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_graphics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_image_alpha_surface_impl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_image_surface_helper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_mouseinput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_screen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_screen_helper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_surface.cpp

!IF  "$(CFG)" == "troll_sdl - Win32 Release"

!ELSEIF  "$(CFG)" == "troll_sdl - Win32 Debug"

# ADD CPP /I "../../../../../../../../../../include/"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\sdl_system.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\do_arc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\SDL_gfxPrimitives.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\SDL_gfxPrimitives_ex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_graphics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_image_alpha_surface_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_image_surface_helper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_image_surface_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_keyinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_mouseinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_screen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_screen_helper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_surface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\troll\sdl_system.h
# End Source File
# End Group
# End Target
# End Project
