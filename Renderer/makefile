EXE			=	Renderer.dll
LIBNAME 	= 	Renderer.lib
OPTIONS		= 	/EHsc /TP /Ot /MD /Ox /W3
LIBPATHES	=	/LIBPATH:../Dependence/Glew/Lib/
INCLUDES 	= 	/I ../ \
				/I ../Dependence/Glew/Include/ \
				/I ../Dependence/Glew/Include/GL \
				/I ../Dependence/	\
				/I ..\Renderer \
				/I ..\VanCore \
				/I ..\Interface 
SYSTEMLIBS  = 	kernel32.lib user32.lib gdi32.lib
LIBS		=	glew32.lib glew32s.lib opengl32.lib glu32.lib
OBJS		= 	GLRenderWindow.obj GLShaderProgram.obj GLResource.obj
all:	$(EXE) 

$(EXE): $(OBJS)
	link $(LIBPATHES) /DLL /out:$(EXE) $(OBJS) $(SYSTEMLIBS) $(LIBS) 
	copy $(EXE) ..\$(EXE)
	copy $(LIBNAME) ..\lib\$(LIBNAME)

$(OBJS):
	cl /c *.cpp $(OPTIONS) $(INCLUDES)
	
clean:
	del *.exp
	del *.obj
	del *.dll
	del *.lib