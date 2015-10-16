OPENGLLIB= -lGL
GLEWLIB= -lGLEW
<<<<<<< HEAD
GLFWLIB = -lglfw
SOILLIB = -lSOIL
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(SOILLIB)
=======
GLFWLIB = `pkg-config glfw3 --libs --static`
# GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
>>>>>>> b275313de3036f6c05dd13fbe822bc5c0be5f06c
LDFLAGS=-L/usr/local/lib 
IN_DIR= include/
SRC_DIR = src/
CPPFLAGS=-I/usr/local/include -I$(IN_DIR) -std=c++11 -g
BIN1=build/assignment_O3
SRCS1=main.cpp gl_framework.cpp shader_util.cpp object.cpp utils.cpp humanoid.cpp
SRCS = $(SRCS1:%=$(SRC_DIR)%)
INCLUDES1= gl_framework.hpp object.hpp shader_util.hpp utils.hpp humanoid.hpp
INCLUDES = $(INCLUDES1:%=$(IN_DIR)%)

SRCTEST1 = test.cpp utils.cpp
SRCTEST = $(SRCTEST1:%=$(SRC_DIR)%)

BINTEST = build/test

all: $(BIN1) $(BINTEST) modelCreator 

$(BINTEST):$(SRCTEST) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCTEST) -o $(BINTEST) $(LDFLAGS) $(LIBS)

$(BIN1): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN1) $(LDFLAGS) $(LIBS)

modelCreator: src/modelCreator.cpp src/utils.cpp
	g++ $(CPPFLAGS) $(LIBS) src/modelCreator.cpp src/utils.cpp -o build/modelCreator

clean:
	rm -f build/*
