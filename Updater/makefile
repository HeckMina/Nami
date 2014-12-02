EXE			=	Van.exe
OPTIONS		= 	/EHsc /TP /Ot /MD /Ox /W3
LIBPATHES	=	
INCLUDES 	= 	
DEPS		=	Renderer VanCore Interface
SYSTEMLIBS  = 	kernel32.lib user32.lib Advapi32.lib shell32.lib
LIBS		=   
OBJS		=	main.obj

all: $(EXE) 

$(EXE): $(OBJS)
	link  /SUBSYSTEM:Windows $(LIBPATHES) /out:$(EXE) *.obj $(SYSTEMLIBS) $(LIBS)
	editbin /SUBSYSTEM:CONSOLE $(EXE)
$(OBJS):
	cl /c *.cpp $(OPTIONS) $(INCLUDES)

clean:
	del *.obj