# Project: Lab8
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = Lab8.o $(RES)
LINKOBJ  = Lab8.o $(RES)
LIBS =  -L"D:/study/c/DEV-CPP/Lib" -lglut32 -lglu32 -lopengl32 -lglaux -lgdi32 -lwinmm -glut.h  
INCS =  -I"D:/study/c/DEV-CPP/include" 
CXXINCS =  -I"D:/study/c/DEV-CPP/lib/gcc/mingw32/3.4.2/include"  -I"D:/study/c/DEV-CPP/include/c++/3.4.2/backward"  -I"D:/study/c/DEV-CPP/include/c++/3.4.2/mingw32"  -I"D:/study/c/DEV-CPP/include/c++/3.4.2"  -I"D:/study/c/DEV-CPP/include" 
BIN  = Lab8.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before Lab8.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Lab8.exe" $(LIBS)

Lab8.o: Lab8.c
	$(CPP) -c Lab8.c -o Lab8.o $(CXXFLAGS)
