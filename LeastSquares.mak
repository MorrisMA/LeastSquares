# Microsoft Developer Studio Generated NMAKE File, Based on LeastSquares.dsp
!IF "$(CFG)" == ""
CFG=LeastSquares - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LeastSquares - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LeastSquares - Win32 Release" && "$(CFG)" != "LeastSquares - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LeastSquares.mak" CFG="LeastSquares - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LeastSquares - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "LeastSquares - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LeastSquares - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LeastSquares.exe" "$(OUTDIR)\LeastSquares.bsc"


CLEAN :
	-@erase "$(INTDIR)\LeastSquares.pch"
	-@erase "$(INTDIR)\PolyLeastSquares.obj"
	-@erase "$(INTDIR)\PolyLeastSquares.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LeastSquares.bsc"
	-@erase "$(OUTDIR)\LeastSquares.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LeastSquares.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LeastSquares.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\PolyLeastSquares.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LeastSquares.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\LeastSquares.pdb" /machine:I386 /out:"$(OUTDIR)\LeastSquares.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PolyLeastSquares.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\LeastSquares.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LeastSquares - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LeastSquares.exe"


CLEAN :
	-@erase "$(INTDIR)\LeastSquares.pch"
	-@erase "$(INTDIR)\PolyLeastSquares.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LeastSquares.exe"
	-@erase "$(OUTDIR)\LeastSquares.ilk"
	-@erase "$(OUTDIR)\LeastSquares.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LeastSquares.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LeastSquares.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\LeastSquares.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LeastSquares.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\PolyLeastSquares.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\LeastSquares.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LeastSquares.dep")
!INCLUDE "LeastSquares.dep"
!ELSE 
!MESSAGE Warning: cannot find "LeastSquares.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LeastSquares - Win32 Release" || "$(CFG)" == "LeastSquares - Win32 Debug"
SOURCE=.\PolyLeastSquares.cpp

!IF  "$(CFG)" == "LeastSquares - Win32 Release"


"$(INTDIR)\PolyLeastSquares.obj"	"$(INTDIR)\PolyLeastSquares.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LeastSquares.pch"


!ELSEIF  "$(CFG)" == "LeastSquares - Win32 Debug"


"$(INTDIR)\PolyLeastSquares.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LeastSquares.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LeastSquares - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LeastSquares.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LeastSquares.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LeastSquares - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LeastSquares.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LeastSquares.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

