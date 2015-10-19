OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = `pkg-config glfw3 --libs --static`
SOILLIB = -lSOIL
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(SOILLIB)
LIBS_DIR = ./libs
LDFLAGS=-L/usr/local/lib -L$(LIBS_DIR)
IN_DIR= include/
SRC_DIR = src/
CPPFLAGS=-I/usr/local/include -I$(IN_DIR) -std=c++11 -g
BIN1=build/assignment_O3
SRCS1=main.cpp gl_framework.cpp shader_util.cpp object.cpp utils.cpp humanoid.cpp r2d2.cpp env.cpp
SRCS = $(SRCS1:%=$(SRC_DIR)%)
INCLUDES1= gl_framework.hpp object.hpp shader_util.hpp utils.hpp humanoid.hpp env.hpp r2d2.hpp
INCLUDES = $(INCLUDES1:%=$(IN_DIR)%)

SRCTEST1 = test.cpp utils.cpp
SRCTEST = $(SRCTEST1:%=$(SRC_DIR)%)

BINTEST = build/test

all: $(BIN1) $(BINTEST) modelCreator createR2D2

$(BINTEST):$(SRCTEST) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCTEST) -o $(BINTEST) $(LDFLAGS) $(LIBS)
	
$(BIN1): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) $(INCLUDES) -o $(BIN1) $(LDFLAGS) $(LIBS)

modelCreator: src/modelCreator.cpp src/utils.cpp
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) src/modelCreator.cpp src/utils.cpp -o build/modelCreator
	(cd build; ./modelCreator);

createR2D2: src/createR2D2.cpp src/utils.cpp
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) src/createR2D2.cpp src/utils.cpp -o build/createR2D2
	(cd build; ./createR2D2); 

clean:
	rm -f build/*
