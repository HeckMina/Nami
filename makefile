EXE			=	AOI.exe
OPTIONS		= 	/EHsc /TP /Ot /MD /Ox /W3
LIBPATHES	=	/LIBPATH:lib \
				/LIBPATH:Dependence/Lua/Lib
INCLUDES 	= 	/I ./ \
				/I .\Dependence\Lua\Include \
				/I ./Dependence/Glew/Include/GL \
				/I ./Dependence/Fbx/include \
				/I ./Dependence/ \
				/I .\Renderer \
				/I .\VanCore \
				/I .\Interface\LuaInterface 
DEPS		=	Renderer VanCore Interface
SYSTEMLIBS  = 	kernel32.lib user32.lib shell32.lib
LIBS		=   VanCore.lib	Renderer.lib Interface.lib
OBJS		=	main.obj

all:	deps $(EXE) 

$(EXE): $(OBJS)
	link  /SUBSYSTEM:Windows $(LIBPATHES) /out:$(EXE) $(OBJS) $(SYSTEMLIBS) $(LIBS)
	editbin /SUBSYSTEM:CONSOLE $(EXE)
	nmake install
	
$(OBJS):
	cl /c *.cpp $(OPTIONS) $(INCLUDES)
deps:
	cd .\Renderer
	nmake
	cd ..
	cd .\VanCore
	nmake
	cd ..
	cd .\Interface\LuaInterface
	nmake
	cd ..
	cd ..
cr:
	del Renderer.dll
	del lib\Renderer.lib
	cd .\Renderer
	nmake clean
	cd ..
cvc:
	cd .\VanCore
	nmake clean
	cd ..
ci:
	cd .\Interface\LuaInterface
	nmake clean
	cd ..
	cd ..
clean:
	cd .\Renderer
	nmake clean
	cd ..
	cd .\VanCore
	nmake clean
	cd ..
	cd .\Interface\LuaInterface
	nmake clean
	cd ..
	cd ..
	cd .\lib
	del *.lib
	cd ..
	del *.obj
	del $(EXE)
	del *.dll
updater:
	cd .\Updater
	nmake
	cd ..
install:
	copy $(EXE)  .\Bin
	copy *.dll	 .\Bin
	copy .\Dependence\Lua\Runtime\*.dll .\Bin
	copy .\Dependence\Glew\Bin\*.dll .\Bin
	copy .\Updater\*.exe .\Bin
renderer:
	cd .\Renderer
	nmake
	cd ..
interface:
	cd .\Interface\LuaInterface
	nmake
	cd ..
	cd ..
vancore:
	cd .\VanCore
	nmake
	cd ..