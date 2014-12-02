EXE			=	Interface.dll
LIBNAME 	= 	Interface.lib
OPTIONS		= 	/EHsc /TP /Ot /MD /Ox /W3
LIBPATHES	=	/LIBPATH:../../lib \
				/LIBPATH:../../Dependence/Lua/Lib
INCLUDES 	= 	/I ../../ \
				/I ../../Dependence\Lua\Include \
				/I ../../Dependence/Glew/Include/GL \
				/I ../../Dependence/Fbx/include \
				/I ../../Dependence/	\
				/I ../../Renderer \
				/I ../../VanCore
SYSTEMLIBS  = 	
LIBS		= 	VanCore.lib 
OBJS		= 	Interface.obj NetWorkAPI.obj SystemAPI.obj FileSystemAPI.obj WindowAPI.obj
all:	$(EXE) 

$(EXE): $(OBJS)
	link  $(LIBPATHES) /DLL /out:$(EXE) $(OBJS) $(SYSTEMLIBS) $(LIBS)
	copy $(EXE) ..\..\$(EXE)
	copy $(LIBNAME) ..\..\lib\$(LIBNAME)

$(OBJS):
	cl /c *.cpp $(OPTIONS) $(INCLUDES)
	
clean:
	del *.exp
	del *.obj
	del *.dll
	del *.lib