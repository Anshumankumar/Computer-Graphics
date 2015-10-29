OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = `pkg-config glfw3 --libs --static`
SOILLIB = -lSOIL
YAMLLIB = -lyaml-cpp
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) $(SOILLIB) $(YAMLLIB)
LIBS_DIR = ./libs
LDFLAGS=-L/usr/local/lib -L$(LIBS_DIR)
IN_DIR= include/
SRC_DIR = src/
CPPFLAGS=-I/usr/local/include -I$(IN_DIR) -std=c++11  -w -g
BIN1=build/assignment_04
SRCS1= gl_framework.cpp shader_util.cpp object.cpp utils.cpp humanoid.cpp r2d2.cpp env.cpp assembly.cpp
SRCS = $(SRCS1:%=$(SRC_DIR)%)
INCLUDES1= gl_framework.hpp object.hpp shader_util.hpp utils.hpp humanoid.hpp env.hpp r2d2.hpp
INCLUDES = $(INCLUDES1:%=$(IN_DIR)%)
OBJ = $(addprefix build/, $(SRCS1:.cpp=.o))
SRCTEST = build/test.o build/utils.o

BINTEST = build/test

all: $(BIN1) $(BINTEST)

model: createR2D2 modelCreator

$(BINTEST):$(SRCTEST) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCTEST) -o $(BINTEST) $(LDFLAGS) $(LIBS)


build/%.o: src/%.cpp include/%.hpp
	   g++ $(CPPFLAGS) -c -o $@ $< $(LDFLAGS) $(LIBS) 


build/main.o: src/main.cpp 
	   g++ $(CPPFLAGS) -c -o $@ $< $(LDFLAGS) $(LIBS) 

$(BIN1): $(OBJ) build/main.o
	g++ $(CPPFLAGS) $(OBJ) src/main.cpp -o $(BIN1) $(LDFLAGS) $(LIBS)



modelCreator: build/modelCreator.o build/utils.o
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) build/modelCreator.o build/utils.o -o build/modelCreator
	(cd build; ./modelCreator);

createR2D2: build/createR2D2.o build/utils.o
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) build/createR2D2.o build/utils.o -o build/createR2D2
	(cd build; ./createR2D2); 

clean:
	rm -f build/*
