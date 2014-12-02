EXE			=	VanCore.dll
LIBNAME 	= 	VanCore.lib
OPTIONS		= 	/EHsc /TP /Ot /MD /Ox /W3
INCLUDES 	= 	/I ../ \
				/I ../Dependence/ \
				/I ../Dependence/Glew/Include/ \
				/I ../Dependence/Glew/Include/GL \
				/I ..\Renderer \
				/I ..\VanCore 
LIBPATHES	=	/LIBPATH:../lib \
				/LIBPATH:../Dependence/Glew/Lib 
SYSTEMLIBS	=	user32.lib gdi32.lib ws2_32.lib advapi32.lib 
LIBS		= 	Renderer.lib glew32.lib opengl32.lib
OBJS		= 	RenderWindow.obj Application.obj FileSystem.obj GameObject.obj IDManager.obj Camera.obj TCPSocket.obj \
				Log.obj Material.obj Mesh.obj SceneManager.obj SystemEventManager.obj Timer.obj VersionManager.obj WWW.obj \
				Directory.obj Utils.obj Hardware.obj
all:	$(EXE) 

$(EXE): $(OBJS)
	link  $(LIBPATHES) /DLL /out:$(EXE) $(OBJS) $(SYSTEMLIBS) $(LIBS)
	copy $(EXE) ..\$(EXE)
	copy $(LIBNAME) ..\lib\$(LIBNAME)

$(OBJS):
	cl /c *.cpp $(OPTIONS) $(INCLUDES)
	
clean:
	del *.exp
	del *.obj
	del *.dll
	del *.lib