OBJS = gl3Test.cpp STTools/glew/src/glew.c STTools/stFrame.cpp STTools/stFrustum.cpp STTools/stMatrixStack.cpp STTools/stPrimitiveBatch.cpp STTools/stShader.cpp STTools/stTimer.cpp STTools/stTriangle.cpp STTools/stTriangleBatch.cpp STTools/stUniform.cpp STTools/stUtil.cpp STLinear/stVector.cpp STLinear/stMatrix.cpp STShape/stRect.cpp STShape/stCircle.cpp STShape/stSphere.cpp STShape/stTorus.cpp STShape/stCylinder.cpp

LIBDIRS = -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib
INCDIRS = -I/usr/include -I/usr/local/include -I/usr/include/GL
CC = g++
CXXFLAGS = -std=c++14
COMPILER_FLAGS = $(CXXFLAGS) -Wall -g $(INCDIRS)
LINKER_FLAGS = -lX11 -lGL -lGLU -lglut -lm


MAIN = gl3Test

prog : $(MAIN)

$(MAIN).o : gl3Test.cpp
glew.o : STTools/glew/src/glew.c

$(MAIN) : $(MAIN).o glew.o
	$(CC) $(COMPILER_FLAGS) -o $(MAIN) $(LIBDIRS) $(OBJS) $(LINKER_FLAGS) 
	
clean:
	rm -f *.o
