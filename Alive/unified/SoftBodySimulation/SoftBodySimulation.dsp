# Microsoft Developer Studio Project File - Name="SoftBodySimulation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=SoftBodySimulation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SoftBodySimulation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SoftBodySimulation.mak" CFG="SoftBodySimulation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SoftBodySimulation - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SoftBodySimulation - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoftBodySimulation - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "SoftBodySimulation - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SoftBodySimulation - Win32 Release"
# Name "SoftBodySimulation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\simulation\EulerIntegrator.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Face.cpp
# End Source File
# Begin Source File

SOURCE=.\simulation\Integrator.cpp
# End Source File
# Begin Source File

SOURCE=.\simulation\MidpointIntegrator.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Object1D.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Object2D.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Object3D.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Particle.cpp
# End Source File
# Begin Source File

SOURCE=.\simulation\RungeKutta4Integrator.cpp
# End Source File
# Begin Source File

SOURCE=.\simulation\Simulation.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Spring.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\simulation\ViewSpace.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\EulerIntegrator.h
# End Source File
# Begin Source File

SOURCE=.\include\Face.h
# End Source File
# Begin Source File

SOURCE=.\include\global.h
# End Source File
# Begin Source File

SOURCE=.\include\Integrator.h
# End Source File
# Begin Source File

SOURCE=.\include\MidpointIntegrator.h
# End Source File
# Begin Source File

SOURCE=.\include\Object.h
# End Source File
# Begin Source File

SOURCE=.\include\Object1D.h
# End Source File
# Begin Source File

SOURCE=.\include\Object2D.h
# End Source File
# Begin Source File

SOURCE=.\include\Object3D.h
# End Source File
# Begin Source File

SOURCE=.\include\Particle.h
# End Source File
# Begin Source File

SOURCE=.\include\RungeKutta4Integrator.h
# End Source File
# Begin Source File

SOURCE=.\include\Simulation.h
# End Source File
# Begin Source File

SOURCE=.\include\Spring.h
# End Source File
# Begin Source File

SOURCE=.\include\Vector.h
# End Source File
# Begin Source File

SOURCE=.\include\ViewSpace.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
