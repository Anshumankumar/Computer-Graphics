OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
IN_DIR= include/
SRC_DIR = src/
CPPFLAGS=-I/usr/local/include -I$(IN_DIR) -std=c++14 -g
BIN1=build/assignment_O2
SRCS1=main.cpp gl_framework.cpp shader_util.cpp object.cpp scene.cpp utils.cpp
SRCS = $(SRCS1:%=$(SRC_DIR)%)
INCLUDES1= gl_framework.hpp object.hpp shader_util.hpp scene.hpp utils.hpp
INCLUDES = $(INCLUDES1:%=$(IN_DIR)%)

SRC1 = $(SRC_DIR)pen.cpp
SRC2 = $(SRC_DIR)bat.cpp
SRC3 = $(SRC_DIR)headPhone.cpp

SRCTEST1 = test.cpp utils.cpp
SRCTEST = $(SRCTEST1:%=$(SRC_DIR)%)

BINTEST = build/test

all: $(BIN1) $(BINTEST) models/pen.raw models/bat.raw models/headPhone.raw modelCreator 

$(BINTEST):$(SRCTEST) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCTEST) -o $(BINTEST) $(LDFLAGS) $(LIBS)

$(BIN1): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN1) $(LDFLAGS) $(LIBS)

models/pen.raw: $(SRC1) 
	g++ -std=c++11 $(SRC1) -o build/pen
	(cd build; ./pen)

models/bat.raw: $(SRC2)
	g++ -std=c++11  $(SRC2) -o build/bat
	(cd build; ./bat)

models/headPhone.raw: $(SRC3)
	g++ -std=c++11 $(SRC3) -o build/headPhone
	(cd build; ./headPhone)

modelCreator: src/modelCreator.cpp src/utils.cpp
	g++ $(CPPFLAGS) $(LIBS) src/modelCreator.cpp src/utils.cpp -o build/modelCreator

clean:
	rm -f build/*
